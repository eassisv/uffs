# -*- coding: utf-8 -*-

import socket
from threading import Thread
from time import sleep

address = '127.0.0.1'
port = 25001
running = True


def sender():
    while True:
        msg = input('--> ')
        if msg == 'quit':
            print('Saindo...')
            break
        sock = socket.socket()
        sock.settimeout(5)
        try:
            sock.connect((address, port))
        except socket.timeout:
            print('Impossível connectar')
            continue
            sock.close()
        sock.send(msg.encode())
        response = sock.recv(1024)
        print('response: ', response.decode())
        sock.shutdown(socket.SHUT_RDWR)
        sock.close()


def receiver():
    sock = socket.socket()
    sock.settimeout(5)
    sock.bind((address, port))
    sock.listen(10)
    while running:
        try:
            conn, addr = sock.accept()
        except socket.timeout:
            continue
        data = conn.recv(1024)
        print('receiver: ', data.decode())
        conn.send(data)
        conn.shutdown(socket.SHUT_RDWR)
        conn.close()
    sock.shutdown(socket.SHUT_RDWR)
    sock.close()


if __name__ == '__main__':
    rec = Thread(target=receiver, name='receiver')
    send = Thread(target=sender, name='sender')

    rec.start()
    send.start()

    send.join()
    running = False
    rec.join()
