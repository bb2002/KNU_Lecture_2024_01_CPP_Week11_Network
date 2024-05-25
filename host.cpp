#include "host.h"

void Host::initialize() {

}

void Host::send(Packet* packet) {
  auto links = this->getAllLinks();
  for (auto iter : links) {
    iter->send(packet, this);
  }
}

short Host::get_empty_port() {
  for (int i = 1024; i < 32700; ++i) {
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
}

void Host::onPacketReceived(Packet* packet) {
  if (packet->destAddress() != this->address_) {
    return;
  }

  for (auto service : this->services_) {
    if (service->getPort() == packet->destPort()) {
      service->onPacketReceived(packet);
    }
  }
}