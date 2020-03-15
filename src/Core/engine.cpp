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
#include "../constants.h"

Engine *Engine::engineInstance = nullptr;

bool Engine::init() {
  int SDL_ImageFlags = (IMG_INIT_JPG | IMG_INIT_PNG);

  // Make sure SDL and SDL_Image both initialize properly
  if (SDL_Init(SDL_INIT_EVERYTHING) != 0 ||
      !(IMG_Init(SDL_ImageFlags) & SDL_ImageFlags)) {
    SDL_Log("Failed to initialize SDL: %s", SDL_GetError());
    return false;
  }

  // Create our window and check for errors
  window = SDL_CreateWindow(fe_config::WINDOW_TITLE, SDL_WINDOWPOS_CENTERED,
                            SDL_WINDOWPOS_CENTERED, fe_config::WINDOW_WIDTH,
                            fe_config::WINDOW_HEIGHT, 0);
  if (window == nullptr) {
    SDL_Log("Failed to create window: %s", SDL_GetError());
    return false;
  }

  // Create our renderer and check for errors
  renderer = SDL_CreateRenderer(window, -1, 0);
  if (renderer == nullptr) {
    SDL_Log("Failed to create renderer: %s", SDL_GetError());
    return false;
  }

  return isRunning_ = true;
}
bool Engine::cleanup() {
  // SDL cleanup
  SDL_DestroyWindow(window);
  SDL_DestroyRenderer(renderer);
  SDL_Quit();
  // Clearing pointers
  delete this->getInstance();
  return true;
}
void Engine::quit() { isRunning_ = false; }

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
    quit();
    break;
  default:
    break;
  }
}
