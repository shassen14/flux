
#include "Color.hpp"
#include "Window.hpp"
#include "raylib.h"
#include <ParticleSimulation.hpp>
#include <raylib-cpp-utils.hpp>

// TODO: Hardcoded values / strings need to be not that
ParticleSimulation::ParticleSimulation(const size_t count) : m_count(count) {
  m_particles.reserve(m_count);
}

void ParticleSimulation::init() {
  // get width and height of window
  // spawn particles within here
  const int32_t width = raylib::Window::GetWidth();
  const int32_t height = raylib::Window::GetHeight();

  for (size_t i = 0; i < m_count; i++) {
    Particle p;
    p.position.x = GetRandomValue(0, width);
    p.position.y = GetRandomValue(0, height);

    p.velocity.x = GetRandomValue(-255, 255);
    p.velocity.y = GetRandomValue(-255, 255);

    p.color = raylib::Color(GetRandomValue(0, 255), GetRandomValue(0, 255),
                            GetRandomValue(0, 255), 255);

    m_particles.push_back(p);
  }
}

void ParticleSimulation::update(const float dt) {
  // get width and height of window
  // spawn particles within here
  const int32_t width = raylib::Window::GetWidth();
  const int32_t height = raylib::Window::GetHeight();

  // loop through all particles
  // apply velocity via euler
  // check window edges
  // bounce off
  for (auto &p : m_particles) {

    // euler
    p.position += p.velocity * dt;

    // collision check of window edges
    // check ceiling and floor
    if (p.position.y <= 0) {
      p.position.y = 0;
      p.velocity.y *= -1;
    } else if (p.position.y >= height) {
      p.position.y = height;
      p.velocity.y *= -1;
    }

    // check for window sides walls
    if (p.position.x <= 0) {
      p.position.x = 0;
      p.velocity.x *= -1;
    } else if (p.position.x >= width) {
      p.position.x = width;
      p.velocity.x *= -1;
    }
  }
}

void ParticleSimulation::render() {
  // check if auto works for raylib
  // do we multithread this?
  for (const auto &p : m_particles) {
    p.position.DrawCircle(1, p.color);
  }
}
