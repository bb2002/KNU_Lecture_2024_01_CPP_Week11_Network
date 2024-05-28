#include "link.h"

void Link::send(Packet* packet, Node* sender) {
	auto node = this->other(sender);
	std::cout 
      << "Link: forwarding packet from node #" 
      << sender->id() 
      << ", to node #" 
      << node->id() << std::endl;
	node->onPacketReceived(packet);
}