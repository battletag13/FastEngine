//  FastEngine
//
//  Created by Matthew Lin.
//  Contact: matthewlinplusprogramming@gmail.com
//
//  Demo playerController header which allows the player to control a game
//  object.
//
//  Copyright © 2020 Matthew Lin. All rights reserved.
//
#ifndef FAST_ENGINE_DEMO_PLAYER_CONTROLLER_H_
#define FAST_ENGINE_DEMO_PLAYER_CONTROLLER_H_

#include "engineAPI.h"

class PlayerController : public Component {
public:
  PlayerController(double speed, double diagonalMoveModifier)
      : speed(speed), diagonalMoveModifier(diagonalMoveModifier){};

  void update() {
    velocity = Vector2D(0, 0);
    if (input::getButton(SDLK_s)) {
      velocity.y = 1;
    } else if (input::getButton(SDLK_w)) {
      velocity.y = -1;
    }

    if (input::getButton(SDLK_a)) {
      velocity.x = -1;
    } else if (input::getButton(SDLK_d)) {
      velocity.x = 1;
    }

    if (input::getMouseButtonDown(0))
      gameObject->instantiate(gameObject->getComponent<Transform>().position);

    if (velocity.x != 0 && velocity.y != 0) {
      velocity *= diagonalMoveModifier;
    }

    gameObject->getComponent<Transform>().translate(time::deltaTime * velocity *
                                                    speed);
  }

  double speed;
  double diagonalMoveModifier;

private:
  Vector2D velocity;
};

#endif
