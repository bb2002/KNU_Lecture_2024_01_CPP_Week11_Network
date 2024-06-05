#ifndef SIMULATOR_H
#define SIMULATOR_H

#define RANDOM_SEED 369369

#include <cstdlib>
#include <functional>
#include <queue>
#include <vector>
#include <iostream>

class Simulator;


class Schedule {
private:
  double time_;
  std::function<void()> function_;

public:
  double time() { return time_; }
  void call() { function_(); }

  Schedule(double time, std::function<void()> function)
      : time_(time), function_(function) {}

  bool operator<(const Schedule& e) const {
    return this->time_ > e.time_;
  }
};

class Simulator {
private:
  static double time_;
  static std::priority_queue<Schedule> queue;

public:
  static double now() { return time_; }

  static void setTime(double time) { Simulator::time_ = time; }

  static void prepare() { srand(RANDOM_SEED); }

  static void schedule(double time, std::function<void()> function) {
    Simulator::queue.push({ time, function });
  }

  static void run() {
    std::cout << "Simulation starting... " << Simulator::queue.size() << std::endl;
    while (!Simulator::queue.empty()) {
      auto schedule = Simulator::queue.top();
      Simulator::queue.pop();

      schedule.call();
    }
  }
};

#endif