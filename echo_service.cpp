#include "echo_service.h"

void EchoService::onPacketReceived(Packet* packet) {
  auto data = packet->data();

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