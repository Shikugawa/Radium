require "socket"

sock = TCPSocket.open("127.0.0.1", 5555)
while msg = gets
  p "sent: " + msg
  sock.write(msg)
  p "receive: " + sock.gets
end
sock.close
