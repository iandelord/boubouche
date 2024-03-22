import socket

HOST = "127.0.0.1"
PORT = 1666

sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
sock.bind((HOST, PORT))
sock.listen(1)
	
while True:
	print("ready and listening")
	connection, clientAddress = sock.accept()
	try:
		print('connected with client: ', clientAddress)
		while True:
			data = connection.recv(128)
			if not data:
				break
			print(data.decode("utf-8"))
			data = data+(b" sent back\n")
			connection.sendall(data)
			
	finally:
		connection.close()

#print("quelozed")
