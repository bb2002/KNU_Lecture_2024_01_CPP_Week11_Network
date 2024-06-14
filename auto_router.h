#ifndef AUTO_ROUTER_H
#define AUTO_ROUTER_H

#include "host.h"
#include "link.h"
#include "router.h"
#include "service.h"
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
        // 호스트 노드들만 주소 매핑
        std::unordered_map<Node*, Address> nodeToHostAddress;
        for (auto node : nodes) {
            if (Host* host = dynamic_cast<Host*>(node)) {
                nodeToHostAddress[node] = host->address();
            }
        }

        // 거리, 이전 노드, 최상의 링크 초기화
        std::unordered_map<Node*, int> distance;
        std::unordered_map<Node*, Node*> previous;
        std::unordered_map<Node*, Link*> bestLink;

        for (auto node : nodes) {
            distance[node] = INF;
            previous[node] = nullptr;
            bestLink[node] = nullptr;
        }

        auto cmp = [&distance](Node* left, Node* right) { return distance[left] > distance[right]; };
        std::priority_queue<Node*, std::vector<Node*>, decltype(cmp)> pq(cmp);

        // Assume the first node in the list is the source node
        Node* source = nodes.front();
        distance[source] = 0;
        pq.push(source);

        while (!pq.empty()) {
            Node* currentNode = pq.top();
            pq.pop();

            for (auto link : currentNode->getAllLinks()) {
                Node* neighbor = link->other(currentNode);
                int newDist = distance[currentNode] + link->delay();

                if (newDist < distance[neighbor]) {
                    distance[neighbor] = newDist;
                    previous[neighbor] = currentNode;
                    bestLink[neighbor] = link;
                    pq.push(neighbor);
                }
            }
        }

        // 라우팅 테이블 채우기 (호스트 노드 대상으로)
        routingTable_.clear();
        for (auto& entry : nodeToHostAddress) {
            Node* node = entry.first;
            Address address = entry.second;

            if (bestLink[node] != nullptr) {
                routingTable_.push_back({address, bestLink[node]});
            }
        }

        // std::cout << "ROUTING SIZE: " << this->routingTable_.size() << std::endl;
        // for (auto& m : this->routingTable_) {
        //     std::cout << m.first.toString() << std::endl;
        // }
    }

  virtual std::string name() {
    return "AutoRouter";
  }

  virtual void onPacketReceived(Packet* packet) {
    for (auto link : this->routingTable_) {
      if (link.first == packet->destAddress()) {
        this->log(std::string("forwarding packet: ") +
          packet->toString() +
          " to " +
          link.second->toString()
        );
        link.second->send(packet, this);
        break;
      }
    }
  }
};

#endif