#pragma once

#include <ostream>
#include <raylib-cpp.hpp>

// everything is pixel units?
struct Particle {
public:
  // float vector of size 2;
  // TOOD: should these by integers or floats?
  // state be float and then rendering floors it rounds?
  raylib::Vector2 position;
  raylib::Vector2 velocity;

  // rgba float
  raylib::Color color;

  Particle()
      : position(0.0f, 0.0f), velocity(0.0f, 0.0f),
        color(255, 255, 255, 255) {};

  // TODO: friend ostream print statements
  friend std::ostream &operator<<(std::ostream &out, const Particle &p) {
    return out << "Position (" << p.position.x << ", " << p.position.y << ")\n"
               << "Velocity (" << p.velocity.x << ", " << p.velocity.y << ")\n";
  }
};
