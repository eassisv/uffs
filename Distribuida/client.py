# -*- coding: utf-8 -*-

import socket
from threading import Thread
from time import sleep

address = '127.0.0.1'
port = 25122


def sender():
    sock = socket.socket()
    sock.settimeout(5)
    while True:
        msg = input('--> ')
        if msg == 'quit':
            break
        try:
            sock.connect((address, port))
        except (socket.timeout, ConnectionRefusedError):
            print('Impossível conectar')
            continue
        sock.send(msg.encode())
        data = sock.recv(1024)
        print('sender: {}'.format(data.decode()))


def receiver(running):
    sock = socket.socket()
    sock.settimeout(5)
    sock.bind((address, port))
    sock.listen(10)
    while running:
        try:
            conn, addr = sock.accept()
        except socket.timeout:
            sock.close()
            continue
        data = conn.recv(1024)
        print('receiver: {}'.format(data.decode()))
        conn.send(data)


if __name__ == '__main__':
    running = True
    send = Thread(target=sender, name='sender')

    send.start()

    send.join()
