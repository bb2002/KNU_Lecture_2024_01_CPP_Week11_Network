#include "packet_sink_service.h"
#include "packet_sink_service_installer.h"

void PacketSinkService::onPacketReceived(Packet* packet) {
  this->log(std::string("received total ") + std::to_string(packet->dataString().length()) + " bytes");
}