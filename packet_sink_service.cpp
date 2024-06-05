#include "packet_sink_service.h"
#include "packet_sink_service_installer.h"

void PacketSinkService::onPacketReceived(Packet* packet) {
  std::cout << "PacketSinkService::onPacketReceived" << std::endl;
}