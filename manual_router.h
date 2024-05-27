#ifndef MANUAL_ROUTER_H
#define MANUAL_ROUTER_H

#include "address.h"
#include "router.h"
#include "link.h"
#include <map>
#include <iostream>
#include <string>

class ManualRouter : public Router {
private:
  std::map<std::string, Link*> routingTable;
public:
  // 목적지 주소에 따른 다음 링크를 설정한다.
  void addRoutingEntry(const Address &destination, Link *nextLink);

  // 라우터로 패킷이 들어온 경우
  virtual void onPacketReceived(Packet* packet);
};

#endif