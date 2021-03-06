//  FastEngine
//
//  Created by Matthew Lin.
//  Contact: matthewlinplusprogramming@gmail.com
//
//  SpritesheetRenderer is one of the core components of the ECS.
//
//  Copyright © 2020 Matthew Lin. All rights reserved.
//
#ifndef FASTENGINE_SPRITESHEET_RENDERER_COMPONENT_H_
#define FASTENGINE_SPRITESHEET_RENDERER_COMPONENT_H_

#include "../Graphics/texture_manager.h"
#include "../config.h"
#include "SDL2/SDL.h"
#include "ecs.h"
#include "transform.h"

namespace fast_engine {

class SpritesheetRenderer : public Component {
public:
  // Constructors
  SpritesheetRenderer(
      const std::string pathToSpritesheet,
      Vector2D srcRectSize = fe_config::SPRITE_RENDERER_DEFAULT_SRC_RECT_SIZE,
      Vector2D sliceSize = fe_config::SPRITE_RENDERER_DEFAULT_SRC_RECT_SIZE,
      Vector2D offset = fe_config::SPRITESHEET_RENDERER_DEFAULT_OFFSET_SIZE,
      Vector2D padding = fe_config::SPRITESHEET_RENDERER_DEFAULT_PADDING_SIZE)
      : sliceSize(sliceSize), offset(offset), padding(padding) {

    setTexture(pathToSpritesheet);

    SDL_Surface *surface =
        TextureManager::getInstance()->loadSurface(pathToSpritesheet);

    srcRect.w = srcRectSize.x;
    srcRect.h = srcRectSize.y;
    srcRect.x = offset.x;
    srcRect.y = offset.y;

    spritesheetDimensions.x = surface->w;
    spritesheetDimensions.y = surface->h;

    spriteCount = 0;
    currentIndex = 0;
    for (int y = offset.y; y < spritesheetDimensions.y;
         y += sliceSize.y + padding.y) {
      for (int x = offset.x; x < spritesheetDimensions.x;
           x += sliceSize.x + padding.x) {
        // This is where we start counting tiles
        ++spriteCount;
      }
    }

    SDL_FreeSurface(surface);
  }
  ~SpritesheetRenderer() { SDL_DestroyTexture(objectTexture); }

  // Utility
  virtual void start() override {
    srcRect.x = 0;
    srcRect.y = 0;

    destRect.w = srcRect.w;
    destRect.h = srcRect.h;
  }
  virtual void render() override {
    TextureManager::getInstance()->render(
        objectTexture, srcRect, destRect,
        gameObject->getComponent<Transform>().angleOfRotation);
  }
  void setSrcRectSize(Vector2D srcRectSize) {
    srcRect.w = srcRectSize.x;
    srcRect.h = srcRectSize.y;
  }
  // Set the sprite this renderer is going to display
  void setSprite(int index) {
    currentIndex = 0;
    for (int y = offset.y; y < spritesheetDimensions.y;
         y += sliceSize.y + padding.y) {
      for (int x = offset.x; x < spritesheetDimensions.x;
           x += sliceSize.x + padding.x) {
        // This is where we start counting tiles
        if (currentIndex == index) {
          srcRect.x = x;
          srcRect.y = y;
          return;
        }
        ++currentIndex;
      }
    }
  }
  // Set the sprite this renderer is going to display to the next sprite
  void nextSprite() {
    if (++currentIndex >= spriteCount)
      currentIndex = 0;

    setSprite(currentIndex);
  }
  void setTexture(const std::string pathToTexture) {
    objectTexture = TextureManager::getInstance()->loadTexture(pathToTexture);
  }
  virtual void update() override {
    Transform &transform = gameObject->getComponent<Transform>();
    // Update position
    destRect.x = transform.position.x;
    destRect.y = transform.position.y;

    // Update scale
    destRect.w = srcRect.w * transform.scale.x;
    destRect.h = srcRect.h * transform.scale.y;
  }

  int spriteCount;
  int currentIndex;

private:
  SDL_Texture *objectTexture;
  SDL_Rect srcRect, destRect;

  Vector2D sliceSize;
  Vector2D offset;
  Vector2D padding;
  Vector2D spritesheetDimensions;
};

} // namespace fast_engine
#endif
