#include "link_installer.h"
#include "link.h"

Link* LinkInstaller::install(Node* a, Node* b, double delay) {
  Link* link = new Link(a, b, delay);

  {
    Nat* nat = dynamic_cast<Nat*>(a);
    Router* router = dynamic_cast<Router*>(b);
    if (nat != NULL && router != NULL) {
      nat->setWanLink(link);
    }
  }

  link->nodeA_ = a;
  link->nodeB_ = b;
  a->links.push_back(link);
  b->links.push_back(link);
  return link;
}