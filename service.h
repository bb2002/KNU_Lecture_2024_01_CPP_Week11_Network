#ifndef SERVICE_H
#define SERVICE_H

#include "node.h"
#include "object.h"

class Host;

class Service : Object {
  friend class ServiceInstaller;

protected:
  // 서비스가 설치된 호스트
  Host *host_;

  // 서비스가 사용하는 포트
  short port_;

  Service(Host *host, int port) : host_(host), port_(port) {}

public:
  short getPort() { return this->port_; }

  virtual void onPacketReceived(Packet* packet) = 0;

  virtual void initialize() {};

  virtual std::string name() {
    return "Service";
  };

  void log(std::string message) {
    Object::log(message);
  }

  virtual ~Service();
};

#endif