#include "host.h"

void Host::initialize() {

}

void Host::send(Packet* packet) {
  auto links = this->getAllLinks();
  for (auto iter : links) {
    std::cout << "Host #" 
    << this->id() 
    << ": sending packet (from: " 
    << this->address().toString() 
    << ", to: " 
    << packet->destAddress().toString() 
    << ", "
    << packet->data().size() 
    << " bytes)" 
    << std::endl;
    iter->send(packet, this);
  }
}

short Host::get_empty_port() {
  for (int i = 1000; i < 32700; ++i) {
    bool available = true;
    for (Service* service : this->services_) {
      if (service->getPort() == i) {
        available = false;
        break;
      }
    }

    if (available) {
      return i;
    }
  }

  return -1;
}

void Host::onPacketReceived(Packet* packet) {
  std::cout << "Host #" 
      << this->id() 
      << ": received packet, destination port: "
      << packet->destPort() 
      << std::endl;
      
  if (packet->destAddress() != this->address_) {
    return;
  }

  for (auto service : this->services_) {
    if (service->getPort() == packet->destPort()) {
      
      service->onPacketReceived(packet);
    }
  }
}