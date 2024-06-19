#ifndef NAT_H
#define NAT_H

#include "address.h"
#include "host.h"
#include "link.h"
#include <set>
#include <vector>

struct NatEntry {
  Address internalAddress;
  short internalPort;
  short externalPort;
};

class Nat : public Node {
private:
  Address address_;

  Link *wanLink_;
  std::vector<NatEntry> natTable_;

  short get_empty_port() {
    for (int i = 10000; i < 32700; ++i) {
      bool available = true;
      for (auto& nat : this->natTable_) {
        if (nat.externalPort == i) {
          available = false;
          break;
        }
      }

      if (available) {
        return i;
      }
    }
    return -1;
  }

public:
  Nat(Address address) : address_(address) {}
  void setWanLink(Link *link) { wanLink_ = link; }

  virtual void onPacketReceived(Packet* packet) {
    for (auto& nat : this->natTable_) {
      if (nat.externalPort == packet->destPort()) {
        Address addr = nat.internalAddress;
        for (auto link : this->getAllLinks()) {
          Host* host = dynamic_cast<Host*>(link->other(this));
          if (host != nullptr && host->address() == addr) {
            link->send(packet, this);
            return;
          }
        }
      }
    }

    this->log("Nat device not foud"); 
  }

  virtual void send(Packet* packet) {
    packet->srcAddress_ = this->address_;

    for (auto& entry : this->natTable_) {
      if (entry.internalPort == packet->srcPort()) {
        packet->srcPort_ = entry.externalPort;
        this->wanLink_->send(packet, this);
        return;
      }
    }

    short newPort = this->get_empty_port();
    this->natTable_.push_back({ 
      packet->srcAddress(), 
      packet->srcPort(), 
      newPort 
    });

    packet->srcPort_ = newPort;
    this->wanLink_->send(packet, this);
    
  }
};

#endif