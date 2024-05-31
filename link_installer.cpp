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