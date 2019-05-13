# -*- coding: utf-8 -*-

import sys
import socket
import re
from pickle import loads, dumps
from Vector import Vector
from threading import Thread
from string import ascii_lowercase

running = True
faulty = False
general = False
configs = []
my_id = 0


def broadcast(msg):
    print('msg {}'.format(msg))
    for i in range(len(configs)):
        if i + 1 == my_id:
            continue
        sock = socket.socket()
        sock.settimeout(5)
        if faulty:
            msg = ascii_lowercase[i]
        try:
            sock.connect(configs[i])
            sock.send(dumps({my_id: msg}))
        except (socket.timeout, ConnectionRefusedError):
            print('Impossível conectar com {}'.format(i + 1))
            continue
        except InterruptedError:
            print('Deu merda')
        sock.close()


def sender_general():
    while True:
        msg = input('-> ')
        if msg == 'sair':
            print('Saindo...')
            break
        broadcast(msg)


def receiver(my_config):
    sock = socket.socket()
    sock.bind(my_config)
    sock.settimeout(5)
    sock.listen(10)
    while running:
        try:
            conn, _ = sock.accept()
        except socket.timeout:
            continue
        data = loads(conn.recv(1024))
        data = data.popitem()
        print(data)
        if not general:
            broadcast(data[1])
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
    configs = [(i.split()[0], int(i.split()[1]))
               for i in f.readlines()]
    return configs[my_id - 1]


def start_threads():
    rec = Thread(target=receiver, name='receiver', args=(my_config, ))
    send = Thread(target=sender_general, name='sender')
    rec.start()
    send.start()
    send.join()
    global running
    running = False
    rec.join()


if __name__ == '__main__':
    try:
        my_id = int(sys.argv[1])
        # Se o id do processo é 1 ele é o general
        general = True if my_id == 1 else False
        # Se o segundo argumento for 'faulty' o processo é o mentiroso
        faulty = True if sys.argv[2] == 'faulty' else False
    except IndexError:
        faulty = False
    except:
        print('Execute o programa com o padrão {} <id>'.
              format(sys.argv[0]))
        sys.exit(0)

    print('Digite "sair" para encerrar')

    my_config = read_configs()
    print(configs)
    print(my_config)
    start_threads()
