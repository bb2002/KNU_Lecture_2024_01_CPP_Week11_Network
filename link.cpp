#include "link.h"
#include "node.h"

void Link::send(Packet* packet, Node* sender) {
	auto node = this->other(sender);
	auto currentTime = Simulator::now() + this->delay();
	this->log(std::string("packet in: ") + packet->toString() + std::string(" from ") + node->toString());

	Simulator::schedule(currentTime, [&, sender, packet, node, currentTime](){
		Simulator::setTime(currentTime);
		this->log(std::string("packet out: ") + packet->toString() + std::string(" to ") + node->toString());
		node->onPacketReceived(packet);
	});
}

Link::~Link() {}