#!/usr/bin/env python
#python telnet
import socket, select

open_sockets = []
listening_socket = socket.socket( socket.AF_INET, socket.SOCK_STREAM )
listening_socket.bind( ("", 21) )
listening_socket.listen(5)

while True:
    # Waits for I/O being available for reading from any socket object.
    rlist, wlist, xlist = select.select( [listening_socket] + open_sockets, [], [] )
    for i in rlist:
        if i is listening_socket:
            new_socket, addr = listening_socket.accept()
            open_sockets.append(new_socket)
        else:
            data = i.recv(1024)
            if data == "":
                open_sockets.remove(i)
                print "Connection closed"
            else:
                print repr(data)
