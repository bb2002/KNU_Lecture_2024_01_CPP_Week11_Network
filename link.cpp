#include "link.h"

void Link::send(Packet* packet, Node* sender) {
	auto node = this->other(sender);
	node->onPacketReceived(packet);
}