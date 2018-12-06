import socket
import time

HOST = "66.75.249.176"        # The host
PORT = 50001         # The same port as used by the server

setup_total = 0
teardown_total = 0
for i in range(0, 100):
    skt = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    start = time.time()
    skt.connect((HOST, PORT))
    end = time.time()
    setup_total += end - start
    start = time.time()
    skt.close()
    # skt = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    end = time.time()
    teardown_total += end-start
print("setup is {}, teardown is {}".format(setup_total * 1000 / 100, teardown_total * 1000 / 100))