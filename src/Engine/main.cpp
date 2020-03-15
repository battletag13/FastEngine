//  FastEngine
//
//  Created by Matthew Lin.
//  Contact: matthewlinplusprogramming@gmail.com
//
//  A simple game engine written in C++ using SDL.
//
//  Copyright © 2020 Matthew Lin. All rights reserved.
//
#include "Core/engine.h"
#include "SDL2/SDL.h"
#include "Utility/time.h"

int main() {
  Engine::getInstance()->init();
  // Start the frame clock
  MilisecondsTimer frameClock;

  while (Engine::getInstance()->isRunning()) {
    Engine::getInstance()->events();
    Engine::getInstance()->update();
    Engine::getInstance()->render();
    Time::deltaTime = frameClock.reset();
  }

  Engine::getInstance()->cleanup();
}
