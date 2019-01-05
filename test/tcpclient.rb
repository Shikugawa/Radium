require "socket"

sock = TCPSocket.open("127.0.0.1", 3334)
sock.write("HELLO")
sock.close
