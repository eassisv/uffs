# -*- coding: utf-8 -*-

import socket
from threading import Thread
from time import sleep, time
from secrets import randbits
from Cryto.Cipher import AES

address = '127.0.0.1'
port = 25001
running = True

g, n = [randbits(8 * 16), randbits(8 * 16)]
x = randbits(8 * 16)

def sender():
    while True:
        msg= input('--> ')
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
        my_key = pow(g, x, n)
        sock.send(bytes([g, n, my_key]))
        shared_key = sock.recv(1024)
        shared_key = pow(shared_key, x, n)
        print('Chave secreta compartilhada com ({}:{}): {}'.format(address, port, shared_key))
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
        _g, _n, other_key = list(data)
        y = randbits(8 * 16)
        my_key = pow(_g, y, _n)
        shared_key = pow(other_key, y, _n)
        print('Chave secreta compartilhada de ({}:{}): {}'.format(addr[0], addr[1], shared_key)
        conn.send(my_key)
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
