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

int main() {
  Engine::getInstance()->init();

  while (Engine::getInstance()->isRunning()) {
    Engine::getInstance()->events();
    Engine::getInstance()->update();
    Engine::getInstance()->render();
  }

  Engine::getInstance()->cleanup();
}
