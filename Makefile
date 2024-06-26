CC = g++
CFLAGS = -g -Wall -Werror -std=c++11
OBJECTS = simulator.o firewall.o object.o service.o service_installer.o packet.o node.o message_service.o message_service_installer.o manual_router.o link.o link_installer.o host.o echo_service.o echo_service_installer.o bulk_send_service_installer.o bulk_send_service.o packet_sink_service_installer.o packet_sink_service.o

# All target
all: first second third forth fifth sixth

first: first.o $(OBJECTS)
	$(CC) $(CFLAGS) -o first first.o $(OBJECTS)

second: second.o $(OBJECTS)
	$(CC) $(CFLAGS) -o second second.o $(OBJECTS)

third: third.o $(OBJECTS)
	$(CC) $(CFLAGS) -o third third.o $(OBJECTS)

forth: forth.o $(OBJECTS)
	$(CC) $(CFLAGS) -o forth forth.o $(OBJECTS)

fifth: fifth.o $(OBJECTS)
	$(CC) $(CFLAGS) -o fifth fifth.o $(OBJECTS)

sixth: sixth.o $(OBJECTS)
	$(CC) $(CFLAGS) -o sixth sixth.o $(OBJECTS)

# Object files
first.o: scenarios/first.cpp
	$(CC) $(CFLAGS) -c scenarios/first.cpp -o first.o

second.o: scenarios/second.cpp
	$(CC) $(CFLAGS) -c scenarios/second.cpp -o second.o

third.o: scenarios/third.cpp
	$(CC) $(CFLAGS) -c scenarios/third.cpp

forth.o: scenarios/forth.cpp
	$(CC) $(CFLAGS) -c scenarios/forth.cpp

fifth.o: scenarios/fifth.cpp
	$(CC) $(CFLAGS) -c scenarios/fifth.cpp

sixth.o: scenarios/sixth.cpp
	$(CC) $(CFLAGS) -c scenarios/sixth.cpp

echo_service_installer.o: echo_service_installer.cpp echo_service_installer.h
	$(CC) $(CFLAGS) -c echo_service_installer.cpp -o echo_service_installer.o

echo_service.o: echo_service.cpp echo_service.h
	$(CC) $(CFLAGS) -c echo_service.cpp -o echo_service.o

simulator.o: simulator.cpp
	$(CC) $(CFLAGS) -c simulator.cpp

object.o: object.cpp
	$(CC) $(CFLAGS) -c object.cpp

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

firewall.o: firewall.cpp firewall.h
	$(CC) $(CFLAGS) -c firewall.cpp -o firewall.o

bulk_send_service_installer.o: bulk_send_service_installer.cpp bulk_send_service_installer.h
	$(CC) $(CFLAGS) -c bulk_send_service_installer.cpp -o bulk_send_service_installer.o

bulk_send_service.o: bulk_send_service.cpp bulk_send_service.h
	$(CC) $(CFLAGS) -c bulk_send_service.cpp -o bulk_send_service.o

packet_sink_service_installer.o: packet_sink_service_installer.cpp packet_sink_service_installer.h
	$(CC) $(CFLAGS) -c packet_sink_service_installer.cpp -o packet_sink_service_installer.o

packet_sink_service.o: packet_sink_service.cpp packet_sink_service.h
	$(CC) $(CFLAGS) -c packet_sink_service.cpp -o packet_sink_service.o


# Clean target
clean:
	del *.o first second third forth
