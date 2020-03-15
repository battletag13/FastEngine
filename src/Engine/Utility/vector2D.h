//  FastEngine
//
//  Created by Matthew Lin.
//  Contact: matthewlinplusprogramming@gmail.com
//
//  A simple class which holds an x and y variable. Supports basic operations
//  like +, -, *, / & their compount assignment counterparts.
//
//  Copyright © 2020 Matthew Lin. All rights reserved.
//
#ifndef FASTENGINE_VECTOR2D_H_
#define FASTENGINE_VECTOR2D_H_

struct Vector2D {
  // Constructors
  Vector2D();
  Vector2D(float x, float y);

  // Utility
  friend Vector2D operator+(const Vector2D &v1, const Vector2D &v2);
  friend Vector2D operator-(const Vector2D &v1, const Vector2D &v2);
  friend Vector2D operator*(const Vector2D &v1, const Vector2D &v2);
  friend Vector2D operator/(const Vector2D &v1, const Vector2D &v2);

  Vector2D &operator+=(const Vector2D &other);
  Vector2D &operator-=(const Vector2D &other);
  Vector2D &operator*=(const Vector2D &other);
  Vector2D &operator/=(const Vector2D &other);

  Vector2D &operator+=(const float scaler);
  Vector2D &operator-=(const float scaler);
  Vector2D &operator*=(const float scaler);
  Vector2D &operator/=(const float scaler);

  // Members
  float x;
  float y;
};

Vector2D operator+(const Vector2D &v1, const Vector2D &v2);
Vector2D operator-(const Vector2D &v1, const Vector2D &v2);
Vector2D operator*(const Vector2D &v1, const Vector2D &v2);
Vector2D operator/(const Vector2D &v1, const Vector2D &v2);

#endif
