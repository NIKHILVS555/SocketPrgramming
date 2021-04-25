all: Server Client
Server: Servermain.o
	g++  -pthread Servermain.o -o Server
Client: Clientmain.o
	g++ -pthread Clientmain.o -o Client
Servermain.o: Servermain.cpp
	g++ -pthread -c Servermain.cpp
Clientmain.o:Clientmain.cpp
	g++ -pthread -c Clientmain.cpp
clean:
	-rm *.o *~ core paper
	rm  Server
	rm  Client
