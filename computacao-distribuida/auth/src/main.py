# -*- coding: utf-8 -*-

import socket
from threading import Thread
from time import sleep, time
from secrets import randbits
import sys

running = True

def sender():
    while True:
        idx = input('ID do destino: ')
        if idx == 'sair':
            print('Saindo...')
            break
        sock = socket.socket()
        sock.settimeout(5)
        addr, port = configs[int(idx) - 1]
        try:
            sock.connect((addr, port))
        except socket.timeout:
            print('Impossível connectar')
            continue
            sock.close()
        g, n, x = [randbits(16) for i in range(3)]
        my_key = pow(g, x, n)
        data = '{} {} {}'.format(g, n, my_key)
        sock.send(data.encode())
        shared_key = int(sock.recv(1024).decode())
        shared_key = pow(shared_key, x, n)
        print('\nChave secreta compartilhada com ({}:{}): {}\n'.format(addr, port, shared_key))
        sock.shutdown(socket.SHUT_RDWR)
        sock.close()


def receiver(my_config):
    sock = socket.socket()
    sock.settimeout(5)
    sock.bind(my_config)
    sock.listen(10)
    while running:
        try:
            conn, addr = sock.accept()
        except socket.timeout:
            continue
        data = conn.recv(1024)
        _g, _n, other_key = list(map(int, data.decode().split(' ')))
        y = randbits(16)
        my_key = pow(_g, y, _n)
        shared_key = pow(other_key, y, _n)
        print('\n\nChave secreta compartilhada de ({}:{}): {}\n\nID do destino: '.format(addr[0], addr[1], shared_key), end='')
        conn.send(str(my_key).encode())
        conn.shutdown(socket.SHUT_RDWR)
        conn.close()
    sock.shutdown(socket.SHUT_RDWR)
    sock.close()


if __name__ == '__main__':
    try:
        my_id = int(sys.argv[1])
    except:
        print('Execute o programa com o padrão {} <id>'.format(sys.argv[0]))
        sys.exit(0)

    try:
        f = open('config.txt')
    except:
        print('Não foi possível abrir arquivo de configuração')
        sys.exit(0)
    
    print('Digite "sair" para encerrar')

    configs = [(i.split()[0], int(i.split()[1])) for i in f.readlines()]
    my_config = configs[my_id - 1]
    
    rec = Thread(target=receiver, name='receiver', args=(my_config, ))
    send = Thread(target=sender, name='sender')

    rec.start()
    send.start()

    send.join()
    running = False
    rec.join()
