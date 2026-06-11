#pragma once

#include <raylib-cpp.hpp>

struct Particle {
  // double vector of size 2;
  raylib::Vector2 position;
  raylib::Vector2 velocity;

  // rgba float
  raylib::Vector4 color;

  Particle()
      : position(0.0f, 0.0f), velocity(0.0f, 0.0f),
        color(1.0f, 1.0f, 1.0f, 1.0f) {};

  // TODO: friend ostream print statements
};
