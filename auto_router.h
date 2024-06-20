#ifndef AUTO_ROUTER_H
#define AUTO_ROUTER_H

#include "host.h"
#include "link.h"
#include "router.h"
#include "service.h"
#include "nat.h"
#include <algorithm>
#include <limits>
#include <map>
#include <queue>
#include <set>
#include <vector>
#include <unordered_map>
#include <unordered_set>

#define INF 2147483646.0

class AutoRouter : public Router {
public:
  void calculate(const std::vector<Node*>& nodes, const std::vector<Link*>& links) {
    std::vector<Nat*> nats;
    std::vector<Host*> hosts;
    std::unordered_map<int, Node*> nodeMap;
    std::unordered_map<int, double> distances;
    std::unordered_map<int, Node*> previous;

    // 초기화
    for (Node* node : nodes) {
      nodeMap[node->id()] = node;
      if (Nat* nat = dynamic_cast<Nat*>(node)) {
          nats.push_back(nat);
      }
      if (Host* host = dynamic_cast<Host*>(node)) {
        hosts.push_back(host);
      }
      distances[node->id()] = INF;
    }

    typedef std::pair<double, int> PQElement;
    typedef std::priority_queue<PQElement, std::vector<PQElement>, std::greater<PQElement>> MinHeap;
    MinHeap pq;

    pq.push({ 0.0, this->id() });
    distances[this->id()] = 0;

    // 다익스트라 알고리즘
    while (!pq.empty()) {
      auto w = pq.top().first;
      auto current = pq.top().second;
      pq.pop();

      if (distances[current] < w) {
        continue;
      }

      Node* currentNode = nodeMap[current];
      if (currentNode == NULL) {
        continue;
      }

      for (auto link : currentNode->getAllLinks()) {
        int next = link->other(currentNode)->id();
        double weight = link->delay();

        if (distances[current] + weight < distances[next]) {
          distances[next] = distances[current] + weight;
          pq.push({ distances[next], next });
          previous[next] = currentNode;
        }
      }
    }

  // 라우팅 테이블 설정
  for (Nat* nat : nats) {
    std::queue<Node*> q;
    q.push(nat);
    Node* prev = this;
    Node* nxt = NULL;

    while (!q.empty()) {
      Node* current = q.front();
      q.pop();

      if (previous.find(current->id()) != previous.end()) {
        nxt = previous[current->id()];
        q.push(nxt);
        prev = current;
      } else {
        break;
      }
    }

    for (Link* lnk : getAllLinks()) {
      if (lnk->other(this) == prev) {
        this->routingTable_.push_back({ nat->address(), lnk });
      }
    }
  }

  // Host 용
  for (Host* host : hosts) {
    std::queue<Node*> q;
    q.push(host);
    Node* prev = this;
    Node* nxt = NULL;

    while (!q.empty()) {
      Node* current = q.front();
      q.pop();

      if (previous.find(current->id()) != previous.end()) {
        nxt = previous[current->id()];
        q.push(nxt);
        prev = current;
      } else {
        break;
      }
    }

    for (Link* lnk : getAllLinks()) {
      if (lnk->other(this) == prev) {
        this->routingTable_.push_back({ host->address(), lnk });
      }
    }
  }
}


  virtual std::string name() {
    return "AutoRouter";
  }

  virtual void onPacketReceived(Packet* packet) {
    bool isPacketSend = false;
    for (auto link : this->routingTable_) {
      if (link.first == packet->destAddress()) {
        this->log(std::string("forwarding packet: ") +
          packet->toString() +
          " to " +
          link.second->toString()
        );
        link.second->send(packet, this);
        isPacketSend = true;
        break;
      }
    }

    if (!isPacketSend) {
      this->log("no route for packet: " + packet->toString());
      delete packet;
    }
  }
};

#endif