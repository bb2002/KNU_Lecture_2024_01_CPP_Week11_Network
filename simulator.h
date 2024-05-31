#ifndef SIMULATOR_H
#define SIMULATOR_H

#define RANDOM_SEED 369369

#include <cstdlib>
#include <functional>
#include <queue>
#include <vector>

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

public:
  static double now() { return time_; }

  static void prepare() { srand(RANDOM_SEED); }

  static void schedule(double time, std::function<void()> function) {
    
  }

  static void run() {
    // 모든 스케줄을 실행한다.
    // TODO: 구현
  }
};

#endif