#ifndef PACKET_SINK_SERVICE_H
#define PACKET_SINK_SERVICE_H

#include "service.h"
#include <string>

class PacketSinkService : public Service {
private:
  Host* host;
  short port;

  PacketSinkService(Host *host, short port) : Service(host, port), host(host), port(port) {};
};

#endif