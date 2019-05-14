# -*- coding: utf-8 -*-

import sys
import socket
import re
import random
from pickle import loads, dumps
from threading import Thread
from string import ascii_lowercase

running = True
faulty = False
general = False
configs = []
my_id = 0
vector = {}
neighbors = set()


def broadcast(msg):
    ng = []
    global my_id
    global faulty
    for i in range(1, len(configs)):
        sock = socket.socket()
        sock.settimeout(5)
        if faulty and (type(msg[my_id]) is str):
            msg = {my_id: random.choice(ascii_lowercase)}
        try:
            sock.connect(configs[i])
            sock.send(dumps(msg))
        except (socket.timeout, ConnectionRefusedError):
            # print('Impossível conectar com {}'.format(i + 1))
            continue
        sock.close()
        ng.append(i + 1)
    global neighbors
    neighbors |= set(ng)


def sender_general():
    global my_id
    while True:
        msg = input('-> ')
        if msg == 'sair':
            print('Saindo...')
            global running
            running = False
            break
        broadcast({my_id: msg})


def receiver(my_config):
    global neighbors
    global my_id
    global vector
    sock = socket.socket()
    sock.bind(my_config)
    sock.settimeout(5)
    sock.listen(10)
    vector[my_id] = {}
    ng = set()
    while running:
        try:
            conn, _ = sock.accept()
        except socket.timeout:
            continue
        data = loads(conn.recv(1024))
        v = data.copy().popitem()
        if v[0] == 1:
            # Recebendo do general
            vector[my_id] = data
            broadcast({my_id: data[1]})
        elif type(v[1]) is str:
            ng |= set(list(data.keys()))
            vector[my_id].update(data)
            if ng == neighbors:
                ng = set()
                broadcast(vector)
        elif type(v[1]) is dict:
            # Recebendo os vetores
            vector.update(data)
            ng |= set(list(data.keys()))
            if ng == neighbors:
                count = {}
                for key in vector.keys():
                    for value in vector[key].values():
                        if value in count:
                            count[value] += 1
                        else:
                            count[value] = 1
                count = sorted(
                    count.items(), key=lambda x: (x[1]), reverse=True)
                faulty_list = []
                for f in count[1::]:
                    for key in vector.keys():
                        for _key, value in vector[key].items():
                            if value == f[0]:
                                faulty_list.append(_key)
                print('Lista de defeituosos')
                for f in set(faulty_list):
                    print(f)
                vector = {}
                neighbors = set()
                ng = set()

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
    if my_id == 1:
        send = Thread(target=sender_general, name='sender')
        send.start()
        send.join()
    else:
        try:
            rec = Thread(target=receiver, name='receiver', args=(my_config, ))
            rec.start()
            rec.join()
        except KeyboardInterrupt:
            print('\r\rSaindo...')
            global running
            running = False


if __name__ == '__main__':
    try:
        my_id = int(sys.argv[1])
        neighbors |= set([my_id])
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
    if my_id == 1:
        print('Digite "sair" para encerrar')
    else:
        print('Aperte ^C para encerrar')
    my_config = read_configs()
    start_threads()
