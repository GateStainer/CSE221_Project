import socket
import time

HOST = "127.0.0.1"        # The host
PORT = 8080            # The same port as used by the server

setup_total = 0
teardown_total = 0

skt = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
start = time.time()
skt.connect((HOST, PORT))
end = time.time()
setup_total += end - start
start = time.time()
skt.close()
end = time.time()
teardown_total += end-start
print("setup is {}, teardown is {}".format(setup_total * 1000, teardown_total * 1000))