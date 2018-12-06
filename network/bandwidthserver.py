import socket

HOST = '0.0.0.0'
PORT = 8080
skt = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
skt.bind((HOST, PORT))
skt.listen(1)
while True:
    conn, addr = skt.accept()
    print('Connected by ', addr)
    while True:
        data = conn.recv(4096)
        if not data:
            break
    conn.close()
print('connect closed')