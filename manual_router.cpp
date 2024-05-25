#include "manual_router.h"

void ManualRouter::addRoutingEntry(const Address &destination, Link *nextLink) {
  this->routingTable.insert({ nextLink, destination });
}

void ManualRouter::onPacketReceived(Packet* packet) {
  for (auto iter = this->routingTable.begin(); iter != this->routingTable.end(); ++iter) {
    auto address = iter->second;
    if (address == packet->destAddress()) {
      auto link = iter->first;
      std::cout 
      << "Link: forwarding packet from node #" 
      << this->id() 
      << ", to node #" 
      << link->other(this)->id() << std::endl;

      link->send(packet, this);
      break;
    }
  }
}