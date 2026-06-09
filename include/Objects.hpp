#pragma once

#include <glm/glm.hpp>

namespace Object {

struct Particle {
  // double vector of size 2;
  glm::dvec2 position;
  glm::dvec2 velocity;

  // rgba float
  glm::vec4 color;

  Particle() : position(0.0), velocity(0.0), color(1.0f) {};
};

} // namespace Object
