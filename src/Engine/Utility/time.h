//  FastEngine
//
//  Created by Matthew Lin.
//  Contact: matthewlinplusprogramming@gmail.com
//
//  Time module holds both the static 'deltaTime' variable and the Timer class
//  which is used for calculation of deltaTime and general timing activities.
//
//  Copyright © 2019 Matthew Lin. All rights reserved.
//
#ifndef FASTENGINE_TIME_H_
#define FASTENGINE_TIME_H_

#include <chrono>

// Holds static variable 'deltaTime'
struct Time {
  static double deltaTime;
};

// General timer class
class Timer {
public:
  Timer() { start(); };

  void start();
  void stop();

protected:
  std::chrono::high_resolution_clock::time_point startPoint, endPoint;
};

struct MicrosecondsTimer : public Timer {
  long double count();
  long double reset();
};
struct MilisecondsTimer : public Timer {
  long double count();
  long double reset();
};
struct SecondsTimer : public Timer {
  unsigned long long count();
  unsigned long long reset();
};

#endif
