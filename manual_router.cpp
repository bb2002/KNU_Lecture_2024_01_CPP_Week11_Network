#include "manual_router.h"

void ManualRouter::addRoutingEntry(const Address &destination, Link *nextLink) {
  this->routingTable.insert({ destination.toString(), nextLink });
}

void ManualRouter::onPacketReceived(Packet* packet) {
  Link* link = this->routingTable[packet->destAddress().toString()];
  if (link != nullptr) {
    std::cout 
      << "Router #" 
      << this->id() 
      << ": forwarding packet (from: " 
      << packet->srcAddress().toString() 
      << ", to: " 
      << packet->destAddress().toString() 
      << ", " 
      << packet->data().size() 
      << " bytes)" 
      << std::endl;
    link->send(packet, this);
  } else {
    std::cout 
      << "Router #" 
      << this->id() 
      << ": no route for packet (from: " 
      << packet->srcAddress().toString() 
      << ", to: " 
      << packet->destAddress().toString() 
      << ", " << packet->data().size() 
      << " bytes)" << std::endl;
  }
}