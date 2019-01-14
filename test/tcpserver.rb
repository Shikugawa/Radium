require "socket"

s0 = TCPServer.open(5001)
while true
	sock = s0.accept
 	msg = sock.gets
	p "sent: " + msg
	sock.write(msg)
	sock.close
end
