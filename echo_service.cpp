#include "echo_service.h"

void EchoService::onPacketReceived(Packet* packet) {
  auto data = packet->data();
  std::cout << "EchoService: received "
   << "\"" 
   << std::string(data.begin(), data.end()) 
   << "\"" 
   << " from " 
   << packet->srcAddress().toString() 
   << ":" 
   << packet->srcPort() 
   << ", send reply with same data" << std::endl;

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