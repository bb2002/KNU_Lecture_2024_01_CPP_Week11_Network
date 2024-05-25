#include "message_service_installer.h"
#include "message_service.h"

MessageService* MessageServiceInstaller::install(Host* host) {
  short port = host->get_empty_port();
  MessageService* messageService = new MessageService(
    host,
    port,
    this->destAddress_,
    this->destPort_
  );

  ServiceInstaller::install(host, messageService);
  return messageService;
}