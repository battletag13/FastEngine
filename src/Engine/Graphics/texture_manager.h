//  FastEngine
//
//  Created by Matthew Lin.
//  Contact: matthewlinplusprogramming@gmail.com
//
//  The texture manager module manages the loading of graphics into our engine.
//
//  Copyright © 2020 Matthew Lin. All rights reserved.
//
#ifndef FASTENGINE_TEXTURE_MANAGER_H_
#define FASTENGINE_TEXTURE_MANAGER_H_

#include <string>

#include "SDL2/SDL.h"

class TextureManager {
public:
  static TextureManager *getInstance() {
    return textureManagerInstance =
               (textureManagerInstance == nullptr ? new TextureManager()
                                                  : textureManagerInstance);
  }

  // General function for rendering an SDL Texture
  static void render(SDL_Texture *texture, SDL_Rect srcRect, SDL_Rect destRect,
                     const float rotationAngle = 0);

  // For loading a texture from a file
  static SDL_Texture *loadTexture(const std::string pathToTexture);

private:
  TextureManager() {}
  static TextureManager *textureManagerInstance;
};

#endif
