#include "bulk_send_service.h"
#include "string.h"

void BulkSendService::initialize() {
  for (double i = this->startTime; i <= this->stopTime; i += this->delay) {
    Simulator::schedule(i, [&, i]() {
      Simulator::setTime(i);
      this->log("sending data");
      
      // 메시지 생성
      int size = rand() % 16384;
      char* msg = new char[size];
      memset(msg, 'A', size);
      msg[size - 1] = '\0';

      // 패킷 송신
      Host* host = this->host;
      host->send(
        new Packet(
          host->address(),
          this->destAddress,
          this->getPort(),
          this->destPort,
          msg
        )
      );
    });
  }
}

void BulkSendService::onPacketReceived(Packet* packet) {}