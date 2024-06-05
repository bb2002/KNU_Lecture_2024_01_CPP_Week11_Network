#include "bulk_send_service_installer.h"

BulkSendService* BulkSendServiceInstaller::install(Host *host, Address destination, short destPort,
                           double delay, double startTime,
                           double stopTime) {
  BulkSendService* bulkSendService = new BulkSendService(host, destination, destPort, delay, startTime, stopTime);
  ServiceInstaller::install(host, bulkSendService);

  return bulkSendService;
}