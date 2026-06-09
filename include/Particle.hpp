#pragma once

#include <glm/glm.hpp>

struct Particle {
  // double vector of size 2;
  glm::vec2 position;
  glm::vec2 velocity;

  // rgba float
  glm::vec4 color;

  Particle() : position(0.0f), velocity(0.0f), color(1.0f) {};
};
