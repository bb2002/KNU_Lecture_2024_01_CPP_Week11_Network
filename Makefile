CC = g++
CFLAGS = -g -Wall -Werror -std=c++11

# All target
#all: first
all: second

# Object files
first.o: scenarios/first.cpp
	$(CC) $(CFLAGS) -c scenarios/first.cpp -o first.o

second.o: scenarios/second.cpp
	$(CC) $(CFLAGS) -c scenarios/second.cpp -o second.o

echo_service_installer.o: echo_service_installer.cpp echo_service_installer.h
	$(CC) $(CFLAGS) -c echo_service_installer.cpp -o echo_service_installer.o

echo_service.o: echo_service.cpp echo_service.h
	$(CC) $(CFLAGS) -c echo_service.cpp -o echo_service.o

host.o: host.cpp host.h
	$(CC) $(CFLAGS) -c host.cpp -o host.o

link_installer.o: link_installer.cpp link_installer.h
	$(CC) $(CFLAGS) -c link_installer.cpp -o link_installer.o

link.o: link.cpp link.h
	$(CC) $(CFLAGS) -c link.cpp -o link.o

manual_router.o: manual_router.cpp manual_router.h
	$(CC) $(CFLAGS) -c manual_router.cpp -o manual_router.o

message_service_installer.o: message_service_installer.cpp message_service_installer.h
	$(CC) $(CFLAGS) -c message_service_installer.cpp -o message_service_installer.o

message_service.o: message_service.cpp message_service.h
	$(CC) $(CFLAGS) -c message_service.cpp -o message_service.o

node.o: node.cpp node.h
	$(CC) $(CFLAGS) -c node.cpp -o node.o

packet.o: packet.cpp packet.h
	$(CC) $(CFLAGS) -c packet.cpp -o packet.o

service_installer.o: service_installer.cpp service_installer.h
	$(CC) $(CFLAGS) -c service_installer.cpp -o service_installer.o

service.o: service.cpp service.h
	$(CC) $(CFLAGS) -c service.cpp -o service.o

# Targets
first: first.o service.o service_installer.o packet.o node.o message_service.o message_service_installer.o manual_router.o link.o link_installer.o host.o echo_service.o echo_service_installer.o
	$(CC) $(CFLAGS) -o first first.o service.o service_installer.o packet.o node.o message_service.o message_service_installer.o manual_router.o link.o link_installer.o host.o echo_service.o echo_service_installer.o

second: second.o service.o service_installer.o packet.o node.o message_service.o message_service_installer.o manual_router.o link.o link_installer.o host.o echo_service.o echo_service_installer.o
	$(CC) $(CFLAGS) -o second second.o service.o service_installer.o packet.o node.o message_service.o message_service_installer.o manual_router.o link.o link_installer.o host.o echo_service.o echo_service_installer.o

# Clean target
clean:
	del *.o first second
