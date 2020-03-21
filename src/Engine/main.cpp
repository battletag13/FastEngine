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
  }

  fast_engine::Engine::getInstance()->cleanup();
}
