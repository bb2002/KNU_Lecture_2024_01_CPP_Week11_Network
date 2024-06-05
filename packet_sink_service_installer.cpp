#include "packet_sink_service_installer.h"

PacketSinkService* PacketSinkServiceInstaller::install(Host *host, short port) {
  PacketSinkService* service = new PacketSinkService(host, port);
  ServiceInstaller::install(host, service);

  return service;
}