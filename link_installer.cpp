#include "link_installer.h"
#include "link.h"

Link* LinkInstaller::install(Node* a, Node* b) {
  Link* link = new Link(a, b);
  a->link = link;
  b->link = link;
  link->nodeA_ = a;
  link->nodeB_ = b;
  return link;
}