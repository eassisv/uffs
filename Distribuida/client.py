import socket

host = '127.0.0.1'
port = 25010

sock = socket.socket()

while True:
    message = input('Mensagem: ')
    if message == 'quit':
        break

    sock.connect((host, port))
    sock.send(message.encode())

    resp = sock.recv(512).decode()
    sock.shutdown(socket.SHUT_RDWR)

    print(resp)


