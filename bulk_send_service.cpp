#include "bulk_send_service.h"

void BulkSendService::initialize() {
  std::cout << this->startTime << ", " << this->delay << ", " << this->stopTime << std::endl;
  for (double i = this->startTime; i <= this->stopTime; i += this->delay) {
    Simulator::schedule(i, [&, i]() {
      Simulator::setTime(i);
      this->log("sending data");
      Host* host = this->host;
      host->send(
        new Packet(
          host->address(),
          this->destAddress,
          this->getPort(),
          this->destPort,
          "Welcome to the aperture"
        )
      );
    });
  }
}

void BulkSendService::onPacketReceived(Packet* pakcet) {
  std::cout << "BulkSendService::onPacketReceived" << std::endl;
}