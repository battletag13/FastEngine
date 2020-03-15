//  FastEngine
//
//  Created by Matthew Lin.
//  Contact: matthewlinplusprogramming@gmail.com
//
//  Texture manager implementation.
//
//  Copyright © 2020 Matthew Lin. All rights reserved.
//
#include "texture_manager.h"
#include "../Core/engine.h"
#include "SDL2/SDL.h"
#include "SDL2_Image/SDL_image.h"

TextureManager *TextureManager::textureManagerInstance = nullptr;

void TextureManager::render(SDL_Texture *texture, SDL_Rect srcRect,
                            SDL_Rect destRect, const float rotationAngle) {
  SDL_RenderCopyEx(Engine::getInstance()->getRenderer, texture, &srcRect,
                   &destRect, rotationAngle, NULL, SDL_FLIP_NONE);
}

SDL_Texture *TextureManager::loadTexture(const std::string pathToTexture) {
  SDL_Surface *tempSurface = IMG_Load(pathToTexture.c_str());
  SDL_Texture *texture = SDL_CreateTextureFromSurface(
      Engine::getInstance()->getRenderer(), tempSurface);
  SDL_FreeSurface(tempSurface);

  return texture;
}
