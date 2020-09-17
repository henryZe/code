#!/usr/bin/python
#-*- coding: utf-8 -*-
from socket import *
from time import ctime

HOST=''
PORT=12345
BUFSIZ=123456

CRYPTO_ALI_TA="ali_ta"

ADDR=(HOST, PORT)
sock=socket(AF_INET, SOCK_STREAM)
sock.setsockopt(SOL_SOCKET, SO_REUSEADDR, 1)
sock.bind(ADDR)

sock.listen(5)
while True:
	print('waiting for connection...')
	tcpClientSock, addr=sock.accept()
	print 'connect from ', addr
	while True:
		try:
			data=tcpClientSock.recv(BUFSIZ)
			if data != CRYPTO_ALI_TA:
				print 'error type: ', data, CRYPTO_ALI_TA
				tcpClientSock.close()
				break
		except Exception, e:
			print Exception, ":", e
			tcpClientSock.close()
			break

		if not data:
			break
		
		print data
		break

	tcpClientSock.close()

sock.close()
