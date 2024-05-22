#include "host.h"

void Host::initialize() {

}

void Host::send(Packet* packet) {

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