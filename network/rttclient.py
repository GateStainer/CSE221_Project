# Benchmarking RTT

import socket
import time
import sys

HOST = "66.75.249.176"  # The host
PORT = 50001  # The same port as used by the server
skt = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
skt.connect((HOST, PORT))

data = "1" * 64
data = data.encode()
print(sys.getsizeof(data))
for k in range(0, 5):
    total = 0

    for i in range(0, 100):
        start = time.time()
        skt.send(data)
        data = skt.recv(64)
        end = time.time()
        total += (end - start)

    result = total * 1000 / 100
    print("The round trip time is {} ms".format(result))
skt.close()