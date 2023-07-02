from config import utils

import traceback
import socket
import threading

import tkinter
import tkinter.scrolledtext
from tkinter import simpledialog

PORT = 3000

class Client:

    def format_nickname(self, nickname):
        ## Replace whitespace for underline and remove newline
        return nickname.replace(" ", "_").strip()

    def use_pkey(self):
        ## User request to use public key
        self.using_key = "Public"
        self.key_label.config(text="PUBLIC")

    def use_skey(self):
        ## User request to use secret key
        self.using_key = "Secret"
        self.key_label.config(text="SECRET")

    def get_send_to(self):
        ## User request to send Direct Messages
        self.sendTo = self.send_to_entry.get()
        self.chat_label.config(text="DM")

    def get_secret_key_SDES(self):
        ## User request to use SDES secret key
        key = self.secret_key_entry.get()
        self.secret_key_SDES = utils.get_SDES_key(key)
        self.using_algorithm = "SDES"
        self.algorithm_label.config(text="SDES")

    def get_secret_key_RC4(self):
        ## User request to use RC4 secret key
        key = self.secret_key_entry.get()
        self.secret_key_RC4 = key
        self.using_algorithm = "RC4"
        self.algorithm_label.config(text="RC4")

    def decrypt_message_SDES(self, message, key):
        crypt_message = message.replace("DECRYPT ", "")
        decrypt_message, user_nickname = utils.SDES(crypt_message, key, "D")
        decrypt_message = f"{user_nickname}: {decrypt_message}"
        return decrypt_message

    def write(self):
        message = f"{self.input_area.get('1.0', 'end')}"

        ## Check if requested nickname (message via DM) exists in server
        self.sock.send(f"GET NICKNAME {self.nickname} {self.sendTo}".encode('utf-8'))
        request = self.sock.recv(1024).decode('utf-8').split()

        ## Requested nickname not found
        if (request[0] == "400"):
            self.sendTo = "Broadcast"
            self.send_to_entry.delete(0, tkinter.END)

        ## Requested nickname found
        elif (request[0] == "200"):
            self.sendTo = request[1]

        ## Broadcast uses public key and SDES encryption as default
        if (self.sendTo == "Broadcast"):
            self.chat_label.config(text="BROADCAST")
            self.key_label.config(text="PUBLIC")
            crypt_message = f'{self.nickname}: {utils.SDES(message, self.public_key, "C")}'
            self.sock.send(f"BROADCAST{crypt_message}".encode('utf-8'))

        ## DM messages handler
        elif (self.sendTo != "Broadcast"):

            ## Client using public key
            if (self.using_key == "Public"):

                key = self.public_key

                if (self.using_algorithm == "SDES"):
                    crypt_message = f'{self.nickname} to {self.sendTo}: {utils.SDES(message, key, "C")}'

                elif (self.using_algorithm == "RC4"):
                    crypt_message = f'{self.nickname} to {self.sendTo}: {utils.RC4_crypt(message, key)}'

                self.sock.send(f"DM {crypt_message} {self.using_algorithm}".encode('utf-8'))

            ## Client using secret key
            elif (self.using_key == "Secret"):

                if (self.using_algorithm == "SDES"):
                    key = self.secret_key_SDES
                    crypt_message = f'{self.nickname} to {self.sendTo}: {utils.SDES(message, key, "C")}'
                    crypted_key = utils.SDES(key, self.public_key, "C")
                    self.sock.send(f'SKEY {crypt_message} {crypted_key} SDES'.encode('utf-8'))

                elif (self.using_algorithm == "RC4"):
                    key = self.secret_key_RC4
                    crypt_message = f'{self.nickname} to {self.sendTo}: {utils.RC4_crypt(message, key)}'
                    crypted_key = utils.RC4_crypt(key, self.public_key)
                    self.sock.send(f'SKEY {crypt_message} {key} RC4'.encode('utf-8'))

        self.input_area.delete('1.0', 'end')

    def receive(self):

        self.public_key = self.sock.recv(1024).decode('utf-8')
        self.sock.send("KEY RECEIVED".encode('utf-8'))

        while self.running:

            try:
                message = self.sock.recv(1024).decode('utf-8')
                ## Message from server
                ## print(message)

                ## Empty string after removing client from server
                if not message:
                    print("Leaving the server...")
                    break
                
                ## Server request to get user nickname
                if message == "NICKNAME":
                    self.sock.send(self.nickname.encode('utf-8'))

                ## Decrypt messages using Public Key (Broadcast)
                elif "DECRYPT" in message:
                    
                    ## Encrypted BROADCAST message
                    decrypt_message = self.decrypt_message_SDES(message, self.public_key)
                    self.text_area.config(state='normal')
                    self.text_area.insert('end', decrypt_message)
                    self.text_area.yview('end')
                    self.text_area.config(state='disabled')

                elif "PKEY" in message:

                    ## Encrypted DM message (Public Key)
                    if "SDES" in message:
                        crypted_message = f"{message.split()[1]} {message.split()[2]} {message.split()[3]} {message.split()[4]}"
                        decrypt_message = self.decrypt_message_SDES(crypted_message, self.public_key)

                    elif "RC4" in message:
                        nicknames = f"{message.split()[1]} {message.split()[2]} {message.split()[3]}"
                        content = message.split()[4]
                        decrypt_message = utils.RC4_decrypt(content, self.public_key)
                        decrypt_message = f"{nicknames} {decrypt_message}"

                    self.text_area.config(state='normal')
                    self.text_area.insert('end', decrypt_message)
                    self.text_area.yview('end')
                    self.text_area.config(state='disabled')

                ## Decrypt messages using Secret Key (DM messages)
                elif "SKEY" in message:

                    ## Encrypted DM message (Secret Key)
                    if "SDES" in message:
                        crypted_key = message.split()[1]
                        self.secret_key_SDES, _ = utils.SDES(crypted_key, self.public_key, "D", send_nickname=False)
                        crypted_message = f"{message.split()[2]} {message.split()[3]} {message.split()[4]} {message.split()[5]}"
                        decrypt_message = self.decrypt_message_SDES(crypted_message, self.secret_key_SDES)

                    elif "RC4" in message:
                        self.secret_key_RC4 = message.split()[1]
                        nicknames = f"{message.split()[2]} {message.split()[3]} {message.split()[4]}"
                        crypted_message = message.split()[5]
                        decrypt_message = utils.RC4_decrypt(crypted_message, self.secret_key_RC4)
                        decrypt_message = f"{nicknames} {decrypt_message}"

                    self.text_area.config(state='normal')
                    self.text_area.insert('end', decrypt_message)
                    self.text_area.yview('end')
                    self.text_area.config(state='disabled')

                ## Server messages
                else:
                    if self.gui_done:
                        self.text_area.config(state='normal')
                        self.text_area.insert('end', message)
                        self.text_area.yview('end')
                        self.text_area.config(state='disabled')

            except (ConnectionAbortedError, Exception):
                traceback.print_exc()
                self.stop()

    def stop(self):
        
        ## STOP GUI (close socket and exit the program)
        self.sock.send("/q".encode("utf-8"))
        self.sock.close()
        self.running = False
        self.window.destroy()
        exit(0)

    def gui_loop(self):

        ## Build GUI
        self.window = tkinter.Tk()
        self.window.title(f"NICKNAME {self.nickname}")
        self.window.configure(bg="lightgray")

        self.text_label = tkinter.Label(self.window, text="CHAT", bg="lightgray")
        self.text_label.config(font=("Arial", 12))
        self.text_label.pack(padx=20, pady=5)

        self.text_area = tkinter.scrolledtext.ScrolledText(self.window)
        self.text_area.pack(padx=20, pady=5)
        self.text_area.config(state="disabled")

        self.msg_label = tkinter.Label(self.window, text="Message:", bg="lightgray")
        self.msg_label.config(font=("Arial", 12))
        self.msg_label.pack(padx=20, pady=5)

        self.input_area = tkinter.Text(self.window, height=3)
        self.input_area.pack(padx=20, pady=5)

        self.send_button = tkinter.Button(self.window, text="Send", command=self.write)
        self.send_button.config(font=("Arial", 12))
        self.send_button.pack(padx=20, pady=5)

        self.send_to_label = tkinter.Label(self.window, text="Send DM (nickname or IP): ", bg="lightgray")
        self.send_to_label.config(font=("Arial", 12))
        self.send_to_label.pack(padx=10, pady=10, side=tkinter.LEFT)

        self.send_to_entry = tkinter.Entry(self.window)
        self.send_to_entry.pack(padx=10, pady=10, side=tkinter.LEFT)

        self.send_to_button = tkinter.Button(self.window, text="Send DM", command=self.get_send_to)
        self.send_to_button.config(font=("Arial", 12))
        self.send_to_button.pack(padx=10, pady=10, side=tkinter.LEFT)

        self.secret_key_label = tkinter.Label(self.window, text="Secret Key: ", bg="lightgray")
        self.secret_key_label.config(font=("Arial", 12))
        self.secret_key_label.pack(padx=10, pady=10, side=tkinter.LEFT)

        self.secret_key_entry = tkinter.Entry(self.window)
        self.secret_key_entry.pack(padx=10, pady=10, side=tkinter.LEFT)

        self.secret_key_button_SDES = tkinter.Button(self.window, text="SDES", command=self.get_secret_key_SDES)
        self.secret_key_button_SDES.config(font=("Arial", 12))
        self.secret_key_button_SDES.pack(padx=10, pady=10, side=tkinter.LEFT)

        self.secret_key_button_RC4 = tkinter.Button(self.window, text="RC4", command=self.get_secret_key_RC4)
        self.secret_key_button_RC4.config(font=("Arial", 12))
        self.secret_key_button_RC4.pack(padx=10, pady=10, side=tkinter.LEFT)

        self.select_key_label = tkinter.Label(self.window, text="Select Key: ", bg="lightgray")
        self.select_key_label.config(font=("Arial", 16))
        self.select_key_label.pack(padx=20, pady=5)

        self.use_pkey_button = tkinter.Button(self.window, text="Use PUBLIC KEY", command=self.use_pkey)
        self.use_pkey_button.config(font=("Arial", 12))
        self.use_pkey_button.pack(padx=20, pady=5)

        self.use_skey_button = tkinter.Button(self.window, text="Use SECRET KEY", command=self.use_skey)
        self.use_skey_button.config(font=("Arial", 12))
        self.use_skey_button.pack(padx=20, pady=5)

        self.chat_label = tkinter.Label(self.window, text="BROADCAST", bg="lightgray")
        self.chat_label.config(font=("Arial", 12))
        self.chat_label.pack(padx=20, pady=5, side=tkinter.LEFT)

        self.key_label = tkinter.Label(self.window, text="PUBLIC", bg="lightgray")
        self.key_label.config(font=("Arial", 12))
        self.key_label.pack(padx=20, pady=5, side=tkinter.LEFT)

        self.algorithm_label = tkinter.Label(self.window, text="SDES", bg="lightgray")
        self.algorithm_label.config(font=("Arial", 12))
        self.algorithm_label.pack(padx=20, pady=5, side=tkinter.LEFT)

        self.gui_done = True
        self.window.wm_protocol("WM_DELETE_WINDOW", self.stop)
        self.window.mainloop()

    def __init__(self):

        IP_window = tkinter.Tk()
        IP_window.withdraw()

        self.HOST_IP = simpledialog.askstring("IP", "IP:", parent=IP_window)

        try:
            self.sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
            self.sock.connect((self.HOST_IP, PORT))
        except:
            print(f"Connection refused to the server.")
            print(f"Requested IP: {self.HOST_IP} | Requested PORT: {PORT}")
            exit(-1)

        nickname_window = tkinter.Tk()
        nickname_window.withdraw()

        # TODO: fix bug related to user pressing enter
        self.nickname = simpledialog.askstring("Nickname", "Please, choose a Nickname:", parent=nickname_window)

        self.nickname = self.format_nickname(self.nickname)
        self.gui_done = False
        self.running = True

        self.using_key = "Public"
        self.sendTo = "Broadcast"
        self.using_algorithm = "SDES"
        self.secret_key_SDES = ""
        self.secret_key_RC4 = ""

        gui_thread = threading.Thread(target=self.gui_loop)
        receive_thread = threading.Thread(target=self.receive)

        gui_thread.start()
        receive_thread.start()

client = Client()