import time
import socket

HOST = "127.0.0.1"
PORT = 1666

print("got started")

sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
sock.connect((HOST, PORT))

print("got past connected")

messages = ["RECORDING"]

for i in messages:
	#print("donnée n°%s: " % i)
	data = str("Couleur: %s\n" % i).encode("utf-8")
	sock.sendall(data)
	#time.sleep(2)

data = sock.recv(512).decode("utf-8")
print(len(data))
print("données: \n%s" % data)

sock.close()