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
    std::cout << "어디로가야하오" << std::endl;
  }

  // for (auto iter = this->routingTable.begin(); iter != this->routingTable.end(); ++iter) {
  //   auto address = iter->second;
  //   if (address == packet->destAddress()) {
  //     auto link = iter->first;
  //     std::cout 
  //     << "Router #" 
  //     << this->id() 
  //     << ": forwarding packet (from: " 
  //     << packet->srcAddress().toString() 
  //     << ", to: " 
  //     << packet->destAddress().toString() 
  //     << ", " 
  //     << packet->data().size() 
  //     << " bytes)" 
  //     << std::endl;
      

  //     link->send(packet, this);
  //     break;
  //   }
  // }
}