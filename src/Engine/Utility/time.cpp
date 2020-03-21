//  FastEngine
//
//  Created by Matthew Lin.
//  Contact: matthewlinplusprogramming@gmail.com
//
//  Time module implementation.
//
//  Copyright © 2019 Matthew Lin. All rights reserved.
//
#include "time.h"

double time::deltaTime;

// Set the start point to the current time
void Timer::start() { startPoint = std::chrono::high_resolution_clock::now(); }
// Set the end point to the current time
void Timer::stop() { endPoint = std::chrono::high_resolution_clock::now(); }

// Count doesn't actually stop timer,
// just updates the endPoint variable with stop()
long double MicrosecondsTimer::count() {
  stop();
  return std::chrono::duration_cast<std::chrono::microseconds>(endPoint -
                                                               startPoint)
      .count();
}
long double MicrosecondsTimer::reset() {
  stop();
  long double duration = std::chrono::duration_cast<std::chrono::microseconds>(
                             endPoint - startPoint)
                             .count();
  start();
  return duration;
}

long double MilisecondsTimer::count() {
  stop();
  return std::chrono::duration_cast<std::chrono::microseconds>(endPoint -
                                                               startPoint)
             .count() /
         1000.;
}
long double MilisecondsTimer::reset() {
  stop();
  long double duration = std::chrono::duration_cast<std::chrono::microseconds>(
                             endPoint - startPoint)
                             .count() /
                         1000.;
  start();
  return duration;
}

unsigned long long SecondsTimer::count() {
  stop();
  return std::chrono::duration_cast<std::chrono::seconds>(endPoint - startPoint)
      .count();
}
unsigned long long SecondsTimer::reset() {
  stop();
  unsigned long long duration =
      std::chrono::duration_cast<std::chrono::seconds>(endPoint - startPoint)
          .count();
  start();
  return duration;
}
