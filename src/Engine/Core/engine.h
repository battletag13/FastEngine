//  FastEngine
//
//  Created by Matthew Lin.
//  Contact: matthewlinplusprogramming@gmail.com
//
//  Core engine class.
//
//  Copyright © 2020 Matthew Lin. All rights reserved.
//
#ifndef FASTENGINE_ENGINE_H_
#define FASTENGINE_ENGINE_H_

#include <array>

#include "../constants.h"
#include "SDL2/SDL.h"
#include "SDL2_Image/SDL_image.h"

class Engine {
public:
  static Engine *getInstance() {
    return engineInstance =
               (engineInstance == nullptr ? new Engine() : engineInstance);
  }

  bool init();
  bool cleanup();

  void update();
  void render();
  void events();

  inline bool isRunning() { return this->isRunning_; }
  inline SDL_Renderer *getRenderer() { return this->renderer; }

private:
  Engine() : rendererDrawColor(fe_config::DEFAULT_RENDERER_DRAW_COLOR) {}
  static Engine *engineInstance;

  // Core
  SDL_Window *window;
  SDL_Renderer *renderer;
  bool isRunning_;

  // Misc
  std::array<int, 4> rendererDrawColor;
};

#endif
