# -*- coding: utf-8 -*-

import socket
from threading import Thread
from time import sleep

address = '127.0.0.1'
port = 25122    


def sender():
    while True:
        sock = socket.socket()
        sock.settimeout(5)
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
        sock.shutdown(socket.SHUT_RDWR)
        sock.close()


def receiver(running):
    while running:
        sock = socket.socket()
        sock.settimeout(5)
        sock.bind((address, port))
        sock.listen(10)
        try:
            conn, addr = sock.accept()
        except socket.timeout:
            sock.close()
            continue
        data = conn.recv(1024)
        print('receiver: {}'.format(data.decode()))
        conn.send(data)
        sock.shutdown(socket.SHUT_RDWR)
        sock.close()
        sleep(10)


if __name__ == '__main__':
    running = True
    rec = Thread(target=receiver, name='receiver', args=(running,))
    send = Thread(target=sender, name='sender')

    rec.start()
    send.start()

    send.join()
    running = False
    rec.join()
