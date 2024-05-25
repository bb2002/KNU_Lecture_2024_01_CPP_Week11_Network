#include "link_installer.h"
#include "link.h"

Link* LinkInstaller::install(Node* a, Node* b) {
  Link* link = new Link(a, b);
  link->nodeA_ = a;
  link->nodeB_ = b;
  a->links.push_back(link);
  b->links.push_back(link);
  return link;
}