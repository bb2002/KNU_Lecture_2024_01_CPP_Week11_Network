#include "simulator.h"
#include "object.h"

double Simulator::time_ = 0.0;
std::priority_queue<Schedule> Simulator::queue;

void Simulator::run() {
  Object::initializeAll();

  while(!Simulator::queue.empty()) {
    auto schedule = Simulator::queue.top();
    Simulator::queue.pop();
    schedule.call();
  }

  Object::cleanup();
}
