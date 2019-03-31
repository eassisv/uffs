import socket

host = '127.0.0.1'
port = 25010

sock = socket.socket()
sock.bind((host, port))

sock.listen(1)

while True:

    try:
        conn, addr = sock.accept()
        data = conn.recv(512)

        print('Mensagem recebida: {}'.format(data.decode()))

        conn.send('Mensagem recebida.'.encode())
        conn.shutdown(socket.SHUT_RDWR)
    except KeyboardInterrupt:
        print('Finalizando')
        break

conn.close()
sock.close()

