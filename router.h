#ifndef ROUTER_H
#define ROUTER_H

#include "node.h"
#include <iostream>

struct RoutingEntry {
public:
  Address destination;
  Link *nextLink;
};

struct RoutingEntry2 {
public:
  int nodeId;
  Link* nextLink;
};

class Router : public Node {
protected:
  std::vector<RoutingEntry> routingTable_;
  std::vector<RoutingEntry2> routingTable2_;

public:
  virtual void onPacketReceived(Packet* packet) {};

  virtual std::string name() {
    return "Router";
  }
};

#endif