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

  std::vector<int> ipToVector(const std::string& ip) {
    std::vector<int> result;
    std::stringstream ss(ip);
    std::string segment;
    
    while (std::getline(ss, segment, '.')) {
        result.push_back(std::stoi(segment));
    }
    
    return result;
  }

  bool isPrivateIP(Address addr) {
      std::vector<int> ipVec = ipToVector(addr.toString());
      
      if (ipVec.size() != 4) {
          return false;
      }
      
      if (ipVec[0] == 10) {
          return true; // 10.0.0.0 - 10.255.255.255
      } else if (ipVec[0] == 172 && ipVec[1] >= 16 && ipVec[1] <= 31) {
          return true; // 172.16.0.0 - 172.31.255.255
      } else if (ipVec[0] == 192 && ipVec[1] == 168) {
          return true; // 192.168.0.0 - 192.168.255.255
      }
      
      return false;
  }

public:
  Nat(Address address) : address_(address) {}
  void setWanLink(Link *link) { wanLink_ = link; }

  virtual void onPacketReceived(Packet* packet) {
    if (this->isPrivateIP(packet->srcAddress())) {
      // 내부망을 외부망으로 변경
      for (auto& nat : this->natTable_) {
        if (packet->srcPort() == nat.internalPort) {
          packet->srcPort_ = nat.externalPort;
          packet->srcAddress_ = this->address();
          this->wanLink_->send(packet, this);
          return;
        }
      }

      // 없다면 새로 생성
      short newPort = this->get_empty_port();
      this->natTable_.push_back({ packet->srcAddress(), packet->srcPort(), newPort });
      packet->srcPort_ = newPort;
      packet->srcAddress_ = this->address();
      this->wanLink_->send(packet, this);
    } else {
      for (auto& nat : this->natTable_) {
        if (packet->destPort() == nat.internalPort) {
          for (auto link : this->getAllLinks()) {
            Host* host = dynamic_cast<Host*>(link->other(this));
            if (host != nullptr && host->address() == nat.internalAddress) {
              link->send(packet, this);
              return;
            }
          }
        }
      }
    }
  }

  Address address() {
    return this->address_;
  }

  virtual std::string name() {
    return "Nat";
  }
};

#endif