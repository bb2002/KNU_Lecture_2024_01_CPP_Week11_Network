#include "host.h"

void Host::initialize() {
  for (Service* service : this->services_) {
    service->initialize();
  }
}

void Host::send(Packet* packet) {
  Simulator::schedule(Simulator::now(), [&, packet]() {
    this->log(std::string("sending packet: ") + packet->toString());
    auto links = this->getAllLinks();
    for (auto iter : links) {
      iter->send(packet, this);
    }
  });
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

  // 서비스에 도착한 패킷은 더 이상 사용하지 않으니 폐기
  delete packet;
}

Host::~Host() {
  for (auto service : this->services_) {
    delete service;
  }
}