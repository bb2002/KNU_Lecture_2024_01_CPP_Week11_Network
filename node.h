#ifndef NODE_H
#define NODE_H

#include "link.h"
#include "packet.h"
#include <map>
#include <vector>

class Link;

class Node {
  friend class LinkInstaller;

private:
  int id_;
  static int nextId_;
  std::vector<Link*> links;

public:
  Node() : id_(nextId_++) {}
  int id() const { return id_; }

  std::vector<Link*> getAllLinks() {
    return this->links;
  }

  Link* getLink(int idx) {
    return this->links[idx];
  }

  virtual void onPacketReceived(Packet* packet) = 0;
};

#endif