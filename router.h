#ifndef ROUTER_H
#define ROUTER_H

#include "node.h"
#include <iostream>

class Router : public Node {
protected:
  std::vector<std::pair<Address, Link*>> routingTable_;

public:
  virtual void onPacketReceived(Packet* packet) {};

  virtual std::string name() {
    return "Router";
  }
};

#endif