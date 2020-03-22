//  FastEngine
//
//  Created by Matthew Lin.
//  Contact: matthewlinplusprogramming@gmail.com
//
//  A simple game engine written in C++ using SDL.
//
//  Copyright © 2020 Matthew Lin. All rights reserved.
//
#include "../Scripts/start.h"
#include "Core/engine.h"
#include "SDL2/SDL.h"
#include "Utility/time.h"
#include <iostream>

long double total = 0;
long num = 0;
constexpr int FRAME_MOD = 1000;

int main() {
  fast_engine::Engine::getInstance()->init();

  start();

  // Start the frame clock
  MilisecondsTimer frameClock;

  while (fast_engine::Engine::getInstance()->isRunning()) {
    fast_engine::Engine::getInstance()->events();
    fast_engine::Engine::getInstance()->update();
    fast_engine::Engine::getInstance()->render();
    time::deltaTime = frameClock.reset();

    total += time::deltaTime;
    if (++num % FRAME_MOD == 0)
      std::cout << time::deltaTime << ", " << (total / num) << '\n';
  }

  fast_engine::Engine::getInstance()->cleanup();
}
