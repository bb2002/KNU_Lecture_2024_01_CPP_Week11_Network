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
  if (packet->destAddress() != this->address_) {
    return;
  }

  std::vector<Service *>::iterator service;
  bool isServiceExists = false;
  for (service = this->services_.begin(); service != this->services_.end(); service++) {
    if ((*service)->getPort() == packet->destPort()) {
      isServiceExists = true;
      break;
    }
  }

  if (isServiceExists) {
    std::cout << "Host #" 
      << this->id() 
      << ": received packet, destination port: "
      << packet->destPort() 
      << std::endl;
    (*service)->onPacketReceived(packet);
  } else {
    std::cout << "Host #" 
      << this->id() 
      << ": no service for packet (from: " 
      << packet->srcAddress().toString() 
      << ", to: " << packet->destAddress().toString() 
      << ", " 
      << packet->data().size() 
      << " bytes)" << std::endl;
  }
}

Host::~Host() {}