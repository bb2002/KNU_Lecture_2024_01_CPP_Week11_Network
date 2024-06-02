#include "bulk_send_service.h"

void BulkSendService::initialize() {
  for (double i = this->startTime; i <= this->stopTime; i += this->delay) {
    Simulator::schedule(i, [&]() {
      this->log("sending packet");

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