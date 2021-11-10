import socket
import json
import os
import logging
import sys
HOST = "localhost"  # The server's hostname or IP address
PORT = 9091        # The port used by the server

class  Client():
	def __init__(self):
		self.sim_port = None

	def request_visu(self, first_shuffle, resolution_shuffle):
		with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as sock:
			msg = {"first_shuffle": first_shuffle, "resolution_shuffle": resolution_shuffle} # a real dict.
			data = json.dumps(msg)
			try:
				# Connect to server and send data
				sock.connect((HOST, PORT))
				sock.sendall(bytes(data,encoding="utf-8"))
				received = sock.recv(1024)
				received = received.decode("utf-8")
				received = json.loads(received)
			except:
				pass
		try:
			print('Received', received)
			return received
		except UnboundLocalError:
			print("Nothing recieved, is server started ?")
		except:
			return received

def parse_args(argv):
	first_shuffle = argv[1].split()
	resolution_shuffle = argv[2].split()
	return (first_shuffle, resolution_shuffle)

if __name__ == "__main__":

	if len(sys.argv) != 3:
		print("ERROR in parsing for visual")
		sys.exit()

	first_shuffle, resolution_shuffle = parse_args(sys.argv)

	c = Client()
	c.request_visu(first_shuffle, resolution_shuffle)

