#include "message_service.h"

void MessageService::send(std::string message) {
  Packet* packet = new Packet(
		this->host_->address(),
		this->destAddress_,
		this->port_,
		this->destPort_,
		message
	);

	this->host_->send(packet);
}

void MessageService::onPacketReceived(Packet* packet) {
  auto data = packet->data();
  std::cout << "MessageService: received \"" 
		<< std::string(data.begin(), data.end()) 
		<< "\" from " 
		<< packet->srcAddress().toString() 
		<< ":" 
		<< packet->srcPort() 
		<< std::endl;
}