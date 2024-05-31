#ifndef BULK_SEND_SERVICE_H
#define BULK_SEND_SERVICE_H

#include "host.h"
#include "service.h"
#include "simulator.h"

#define PACKET_SIZE 512

class BulkSendService : Service {
  friend class BulkSendServiceInstaller;

private:
  Host* host;
  Address destAddress;
  short destPort;
  double delay;
  double startTime;
  double stopTime;

  BulkSendService(Host *host, Address destAddress, short destPort,
                  double delay = 1, double startTime = 0,
                  double stopTime = 10.0) : Service(host, host->get_empty_port()), host(host), destAddress(destAddress), destPort(destPort), delay(delay), startTime(startTime), stopTime(stopTime) {};
};

#endif