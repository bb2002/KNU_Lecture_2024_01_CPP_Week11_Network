#ifndef PACKET_SINK_SERVICE_H
#define PACKET_SINK_SERVICE_H

#include "service.h"
#include <string>

class PacketSinkServiceInstaller;

class PacketSinkService : public Service {
  friend PacketSinkServiceInstaller;

private:
  Host* host;
  short port;

  PacketSinkService(Host *host, short port) : Service(host, port), host(host), port(port) {};

public:
  virtual void onPacketReceived(Packet* packet);
  
  virtual std::string name() {
    return "PacketSinkService";
  };
};

#endif