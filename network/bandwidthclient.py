import socket
import time

HOST = "66.75.249.176"
FILE_SIZE = 1024
PORT = 50001

skt = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
skt.connect((HOST, PORT))
fileData = '1' * int(FILE_SIZE) * 1024 * 1024
fileData = fileData.encode()
print('start to send %d bytes data' % len(fileData))
start = time.time()
skt.sendall(fileData)
end = time.time()
result = (end - start) * 1000
print("sending 32M data costs {} ms".format(result))
skt.close()