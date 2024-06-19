#ifndef LINK_INSTALLER_H
#define LINK_INSTALLER_H

#include "link.h"
#include "service.h"
#include "nat.h"
#include "host.h"
#include "router.h"

class LinkInstaller {
public:
  // 노드 a, b 사이에 링크를 설치하고 반환한다.
  Link *install(Node *a, Node *b, double delay = 0.0);

  Link* LinkInstaller::install(Host*, Nat*, double delay = 0.0);

  LinkInstaller::install(Router*, Nat*, double delay = 0.0);
};

#endif