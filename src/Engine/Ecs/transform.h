//  FastEngine
//
//  Created by Matthew Lin.
//  Contact: matthewlinplusprogramming@gmail.com
//
//  Transform is one of the core components of the ECS.
//
//  Copyright © 2020 Matthew Lin. All rights reserved.
//
#ifndef FASTENGINE_TRANSFORM_COMPONENT_H_
#define FASTENGINE_TRANSFORM_COMPONENT_H_

#include <cmath>

#include "../Utility/vector2D.h"
#include "ecs.h"

struct Transform : public Component {
  Transform() : position(0, 0), scale(1, 1), angleOfRotation(0) {}

  // Basic transform operations
  void translate(Vector2D vector) { this->position += vector; }
  void rotate(double angle) {
    this->angleOfRotation += angle;
    if (angleOfRotation < 0) {
      angleOfRotation = -angleOfRotation;
      angleOfRotation = std::fmod(angleOfRotation, 360);
      angleOfRotation = -angleOfRotation;
    } else {
      angleOfRotation = std::fmod(angleOfRotation, 360);
    }
  }
  void scaleBy(Vector2D scalar) { this->scale *= scalar; }

  // Members
  Vector2D position;
  Vector2D scale;

  double angleOfRotation;
};

#endif
