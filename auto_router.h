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

class AutoRouter : public Router {
public:
  void calculate(const std::vector<Node*>& nodes, const std::vector<Link*>& links) {
      std::unordered_map<int, std::vector<std::pair<int, double>>> adjList;
      for (auto link : links) {
        adjList[link->nodeA()->id()].emplace_back(link->nodeB()->id(), link->delay());
        adjList[link->nodeB()->id()].emplace_back(link->nodeA()->id(), link->delay());
      }

      for (const auto& node : nodes) {
        int startId = node->id();
        std::unordered_map<int, double> distances;
        std::unordered_map<int, int> previous;
        std::unordered_map<int, Link*> previousLink;

        for (const auto& n : nodes) {
          distances[n->id()] = std::numeric_limits<double>::max();
          previous[n->id()] = -1;
          previousLink[n->id()] = nullptr;
        }
        distances[startId] = 0;

        auto compare = [&distances](int lhs, int rhs) {
          return distances[lhs] > distances[rhs];
        };
        std::priority_queue<int, std::vector<int>, decltype(compare)> pq(compare);
        pq.push(startId);

        while (!pq.empty()) {
          int current = pq.top();
          pq.pop();

          for (const auto& neighbor : adjList[current]) {
            int nextNode = neighbor.first;
            double weight = neighbor.second;
            double newDist = distances[current] + weight;
            if (newDist < distances[nextNode]) {
              distances[nextNode] = newDist;
              previous[nextNode] = current;

              for (auto link : links) {
                if ((link->nodeA()->id() == current && link->nodeB()->id() == nextNode) ||
                    (link->nodeB()->id() == current && link->nodeA()->id() == nextNode)) {
                    previousLink[nextNode] = link;
                    break;
                  }
                }
                pq.push(nextNode);
              }
          }
        }

        for (const auto& n : nodes) {
          if (n->id() != startId) {
            int nextNode = n->id();
            Link* nextLink = nullptr;

            while (previous[nextNode] != startId && previous[nextNode] != -1) {
                nextNode = previous[nextNode];
            }
            nextLink = previousLink[nextNode];
            routingTable2_.emplace_back(RoutingEntry2{n->id(), nextLink});
          }
        }
      }
    }

  virtual std::string name() {
    return "AutoRouter";
  }

  virtual void onPacketReceived(Packet* packet) {
    Simulator::schedule(Simulator::now(), [&, packet] {
      Link* link = this->routingTable2_[packet->destAddress().toString()];
      this.log(std::string("packet in: ") + packet->toString() + "<" + packet->name() + ">"  + "from " + link->toString() + "<" + link->name() + ">"));
    });
  }
};

#endif