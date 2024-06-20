#ifndef FIREWALL_H
#define FIREWALL_H
#include "address.h"
#include "node.h"
#include "object.h"
#include "host.h"
#include <set>
#include <string>

class Link;
class FirewallPolicy : public Object {};

class Firewall : public Node {
private:
  class AllowAnyPolicy : public FirewallPolicy {
  private:
    short destPort_;

    virtual std::string name() {
      return "AllowAnyPolicy";
    }

  public:
    AllowAnyPolicy(short destPort) : destPort_(destPort) {}

    inline short destPort() { return this->destPort_; }
  };

  class AllowSpecificPolicy : public FirewallPolicy {
  private:
    Address srcAddress_;
    short destPort_;

    virtual std::string name() {
      return "AllowSpecificPolicy";
    }

  public:
    AllowSpecificPolicy(Address srcAddress, short destPort)
        : srcAddress_(srcAddress), destPort_(destPort) {}

    inline short destPort() { return this->destPort_; }

    inline Address address() { return this->srcAddress_; }
  };

  Link *receiveLink_ = nullptr;
  std::vector<FirewallPolicy*> policies_;

public:
  void setReceiveLink(Link *link) { this->receiveLink_ = link; }

  void addAllowAnyPolicy(short destPort);
  void addAllowSpecificPolicy(Address srcAddress, short destPort);

  void allow(Packet*);

  virtual std::string name() {
    return "Firewall";
  }

  virtual void onPacketReceived(Packet* packet);
};
#endif