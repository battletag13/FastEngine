//  FastEngine
//
//  Created by Matthew Lin.
//  Contact: matthewlinplusprogramming@gmail.com
//
//  SpriteRenderer is one of the core components of the ECS.
//
//  Copyright © 2020 Matthew Lin. All rights reserved.
//
#ifndef FASTENGINE_SPRITE_RENDERER_COMPONENT_H_
#define FASTENGINE_SPRITE_RENDERER_COMPONENT_H_

#include "../Graphics/texture_manager.h"
#include "../config.h"
#include "SDL2/SDL.h"
#include "ecs.h"
#include "transform.h"

namespace fast_engine {

class SpriteRenderer : public Component {
public:
  // Constructors
  SpriteRenderer(
      const std::string pathToTexture,
      Vector2D srcRectSize = fe_config::SPRITE_RENDERER_DEFAULT_SRC_RECT_SIZE) {

    setTexture(pathToTexture);

    srcRect.w = srcRectSize.x;
    srcRect.h = srcRectSize.y;
  }
  ~SpriteRenderer() { SDL_DestroyTexture(objectTexture); }

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

private:
  SDL_Texture *objectTexture;
  SDL_Rect srcRect, destRect;
};

} // namespace fast_engine
#endif
