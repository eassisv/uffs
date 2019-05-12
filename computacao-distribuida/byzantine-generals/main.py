# -*- coding: utf-8 -*-

import sys
import socket
import re
from Vector import Vector
from threading import Thread
from string import ascii_lowercase

running = True
faulty = False
general = False
configs = []
my_id = 0

def sender_general():
    sock = socket.socket()
    sock.settimeout(5)
    while True:
        msg = input()
        if msg == 'sair':
            print('Saindo...')
            break
        for i in range(len(configs)):
            if i == my_id: continue
            if faulty:
                msg = ascii_lowercase[i]
            try:
                sock.connect(configs[i])
                sock.send(Vector({my_id: msg}))
            except:
                continue
        print("sai")
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
        conn.send(data)
        print(data)
        conn.shutdown(socket.SHUT_RDWR)
        conn.close()
    sock.shutdown(socket.SHUT_RDWR)
    sock.close()


def read_configs():
    try:
        f = open('config.txt')
    except:
        print('Não foi possível abrir arquivo de configuração')
        sys.exit(0)
    global configs
    configs = [(i.split()[0], int(i.split()[1]))\
               for i in f.readlines()]
    return configs[my_id - 1]


if __name__ == '__main__':
    try:
        my_id = int(sys.argv[1])
        general = True if my_id == 1 else False
        faulty = True if sys.argv[2] == '1' else False
    except:
        print('Execute o programa com o padrão {} <id>'.\
                format(sys.argv[0]))
        sys.exit(0)

    print('Digite "sair" para encerrar')

    my_config = read_configs()
    rec = Thread(target=receiver, name='receiver', args=(my_config, ))
    send = Thread(target=sender_general, name='sender')

    rec.start()
    send.start()

    send.join()
    running = False
    rec.join()
