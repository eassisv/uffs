# -*- coding: utf-8 -*-

import sys
import socket
import re
from threading import Thread
from time import sleep, time
from secrets import randbits

my_id = 0
running = True
vector_clock = []

def calculate_vc(vci):
    global vector_clock
    vector_clock = list(max(x, y) for x, y in \
            zip(vector_clock, list(map(int, vci.split()))))


def calculate_mykey(g, n):
    y = randbits(16)
    return y, pow(g, y, n)


def data_processing(*args):
    data = ''
    for i in re.split(r'\D+', str(args)):
        data += i + ' '
    return data.encode()


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
        g, n = [randbits(16) for i in range(2)]
        vector_clock[my_id - 1] += 1
        x, my_key = calculate_mykey(g, n)
        vector_clock[my_id - 1] += 1
        data = data_processing(g, n, my_key, vector_clock)
        sock.send(data)
        data = sock.recv(1024).decode()
        vector_clock[my_id - 1] += 1
        other_key, vci = data.split(maxsplit=1)
        calculate_vc(vci)
        shared_key = pow(int(other_key), x, n)
        print('\nChave secreta compartilhada com ({}:{}): {}'.format(addr, port, shared_key))
        print('Relógio vetorial {}\n'.format(vector_clock))
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
        vector_clock[my_id - 1] += 1
        _g, _n, other_key, vci = list(data.decode().split(maxsplit=3))
        calculate_vc(vci)
        vector_clock[my_id - 1] += 1
        y, mykey = calculate_mykey(int(_g), int(_n))
        shared_key = pow(int(other_key), y, int(_n))
        print('\n\nChave secreta compartilhada de ({}:{}): {}' \
            .format(addr[0], addr[1], shared_key))
        vector_clock[my_id - 1] += 1
        data = data_processing(mykey, vector_clock)
        conn.send(data)
        print('Relógio vetorial: {}\n\nID do destino: '.format(vector_clock), end='')
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
    vector_clock = [0] * len(configs)
    my_config = configs[my_id - 1]

    rec = Thread(target=receiver, name='receiver', args=(my_config, ))
    send = Thread(target=sender, name='sender')

    rec.start()
    send.start()

    send.join()
    running = False
    rec.join()
