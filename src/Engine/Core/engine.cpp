//  FastEngine
//
//  Created by Matthew Lin.
//  Contact: matthewlinplusprogramming@gmail.com
//
//  Core engine implementation.
//
//  Copyright © 2020 Matthew Lin. All rights reserved.
//
#include "engine.h"
#include "../Logger/logger.h"
#include "../constants.h"

namespace fast_engine {

Engine *Engine::engineInstance = nullptr;

bool Engine::init() {
  int SDL_ImageFlags = (IMG_INIT_JPG | IMG_INIT_PNG);

  // Make sure SDL and SDL_Image both initialize properly
  if (SDL_Init(SDL_INIT_EVERYTHING) != 0 ||
      !(IMG_Init(SDL_ImageFlags) & SDL_ImageFlags)) {
    Logger::getInstance()->logError("Failed to initialize SDL!");
    Logger::getInstance()->logFatalError(SDL_GetError());
    return false;
  }
  Logger::getInstance()->log("SDL initialized!");

  // Create our window and check for errors
  window =
      SDL_CreateWindow(fe_config::DEFAULT_WINDOW_TITLE, SDL_WINDOWPOS_CENTERED,
                       SDL_WINDOWPOS_CENTERED, fe_config::DEFAULT_WINDOW_WIDTH,
                       fe_config::DEFAULT_WINDOW_HEIGHT, 0);
  if (window == nullptr) {
    Logger::getInstance()->logError("Failed to create window!");
    Logger::getInstance()->logFatalError(SDL_GetError());
    return false;
  }
  Logger::getInstance()->log("Window created!");

  // Create our renderer and check for errors
  renderer = SDL_CreateRenderer(window, -1, 0);
  if (renderer == nullptr) {
    Logger::getInstance()->logError("Failed to create renderer!");
    Logger::getInstance()->logFatalError(SDL_GetError());
    return false;
  }
  Logger::getInstance()->log("Renderer created!");

  Logger::getInstance()->log("Engine initialized!");
  return isRunning_ = true;
}
bool Engine::cleanup() {
  // SDL cleanup
  SDL_DestroyWindow(window);
  SDL_DestroyRenderer(renderer);
  IMG_Quit();
  SDL_Quit();
  // Clearing pointers
  delete this->getInstance();

  Logger::getInstance()->log("Engine cleaned!");

  delete Logger::getInstance();
  return true;
}

void Engine::update() {}
void Engine::render() {
  // Prepare the renderer
  SDL_RenderClear(renderer);
  SDL_SetRenderDrawColor(renderer, rendererDrawColor[0], rendererDrawColor[1],
                         rendererDrawColor[2], rendererDrawColor[3]);
  // Present the renderer
  SDL_RenderPresent(renderer);
}
void Engine::events() {
  SDL_Event event;
  SDL_PollEvent(&event);
  switch (event.type) {
  case SDL_QUIT:
    isRunning_ = false;
    break;
  default:
    break;
  }
}

} // namespace fast_engine
