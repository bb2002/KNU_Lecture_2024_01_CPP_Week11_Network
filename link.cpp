#include "link.h"
#include "node.h"

void Link::send(Packet* packet, Node* sender) {
	Simulator::schedule(Simulator::now(), [&, sender, packet](){
		auto node = this->other(sender);
    this->log(std::string("packet in: ") + packet->toString() + std::string(" from ") + node->toString());
		node->onPacketReceived(packet);
	});
}

Link::~Link() {}