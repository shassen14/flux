#pragma once

#include <raylib-cpp.hpp>

struct Boid {
  raylib::Vector2 position;
  raylib::Vector2 velocity;
  raylib::Vector2 acceleration;

  raylib::Color color;

  Boid()
      : position(0.0f, 0.0f), velocity(0.0f, 0.0f), acceleration(0.0f, 0.0f),
        color(255, 255, 255, 255) {};
};
