import socket
import time

dst_IP = "172.21.209.231"
PORT_list = []

def PORT_Scan():

    for PORT in range(1, 65535):

        try:

            s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
            s.settimeout(1)
            result = s.connect_ex((dst_IP, PORT))

            if result == 0:

                if PORT <= 1024:
                    service_name = socket.getservbyport(PORT, 'tcp')
                    print("Port {} is open".format(PORT) + " | Service: %s"%(service_name))

                else:
                    print("Port {} is open".format(PORT))

                PORT_list.append(PORT)

        except:
            pass

if __name__ == "__main__":

    ip = input("Digite o IP destinatario do PORT SCAN (default: 172.21.209.231): ")

    if len(ip) > 1:
        dst_IP = ip

    PORT_Scan()
