#include "echo_service.h"

void EchoService::onPacketReceived(Packet* packet) {
  auto data = packet->data();
  this->log(
    std::string("received ") + std::string(data.begin(), data.end()) +
     " from " + packet->srcAddress().toString() +
     ":" + std::to_string(packet->srcPort()) + ", send replay with same data");

   this->host_->send(
      new Packet(
        this->host_->address(),
        packet->srcAddress(),
        this->port_,
        packet->srcPort(),
        data
      )
   );
}

EchoService::~EchoService() {}