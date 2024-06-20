#include "firewall.h"
#include "link.h"

void Firewall::onPacketReceived(Packet* packet) {
	for (auto& policy : this->policies_) {
		{
			AllowAnyPolicy* allowAnyPolicy = dynamic_cast<AllowAnyPolicy*>(policy);
			if (allowAnyPolicy != nullptr && allowAnyPolicy->destPort() == packet->destPort()) {
				// Allowed
				this->allow(packet);
				return;
			}
		}

		{
			AllowSpecificPolicy* allowSpecificPolicy = dynamic_cast<AllowSpecificPolicy*>(policy);
			if (allowSpecificPolicy != nullptr && 
					allowSpecificPolicy->destPort() == packet->destPort() && 
					allowSpecificPolicy->address() == packet->srcAddress()
			) {
				this->allow(packet);
			}
		}
	}

	this->log(std::string("Dropping ") + 
		packet->toString() + std::string(" with src address ") +
		packet->srcAddress().toString() + std::string(" and dest port ") +
		std::to_string(packet->destPort())
	);
}

void Firewall::addAllowAnyPolicy(short destPort) {
	this->policies_.push_back(new AllowAnyPolicy(destPort));
}

void Firewall::addAllowSpecificPolicy(Address srcAddress, short destPort) {
	this->policies_.push_back(new AllowSpecificPolicy(srcAddress, destPort));
}

void Firewall::allow(Packet* packet) {
	this->log(std::string("Allow Packet ") + packet->toString());
	for (auto link : this->getAllLinks()) {
		if (link != this->receiveLink_) {
			link->send(packet, this);
		}
	}
}