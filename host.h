#ifndef HOST_H
#define HOST_H

#include "address.h"
#include "packet.h"
#include "service.h"
#include "link.h"
#include "node.h"
#include <vector>
#include <iostream>

class Host : public Node {
  friend class ServiceInstaller;

private:
  // 호스트의 주소
  Address address_;

  // 설치된 서비스 목록
  std::vector<Service *> services_;

public:
  Address address() { return address_; }

  Host(Address address) : address_(address) {}

  Host(const char* address) {
    this->address_ = Address(address);
  }

  Host(int address) {
    this->address_ = Address(std::to_string(address));
  }
  
  // 호스트와 설치된 서비스를 전부 초기화한다.
  void initialize();

  // 링크를 랜덤으로 하나 선택하여 패킷을 전송한다.
  void send(Packet *packet);

  // 빈 포트를 한 개 탐색한다.
  short get_empty_port();

  virtual std::string name() {
    return "Host";
  }

  // 링크로부터 패킷을 받았을 경우
  virtual void onPacketReceived(Packet* packet);

  virtual ~Host();
};

#endif