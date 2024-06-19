#include "link_installer.h"
#include "link.h"

Link* LinkInstaller::install(Node* a, Node* b, double delay) {
  Link* link = new Link(a, b, delay);
  link->nodeA_ = a;
  link->nodeB_ = b;
  a->links.push_back(link);
  b->links.push_back(link);
  return link;
}

Link* LinkInstaller::install(Host* host, Nat* nat, double delay) {
  Link* link = new Link(host, nat, delay);
  host->links.push_back(link);
  nat->links.push_back(link);
  return link;
}

Link* LinkInstaller::install(Router* router, Nat* nat, double delay) {
  Link* link = new Link(router, nat, delay);
  router->links.push_back(link);
  nat->setWanLink(link);
  return link;
}