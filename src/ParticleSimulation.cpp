
#include "Color.hpp"
#include "Window.hpp"
#include "raylib.h"
#include <ParticleSimulation.hpp>
#include <raylib-cpp-utils.hpp>

#include <iostream>

ParticleSimulation::ParticleSimulation(const size_t count) : m_count(count) {
  m_particles.reserve(m_count);
}

void ParticleSimulation::init() {
  // get width and height of window
  // spawn particles within here
  const int32_t width = raylib::Window::GetWidth();
  const int32_t height = raylib::Window::GetHeight();
  std::cout << "this is a width: " << width << "\n";

  for (size_t i = 0; i < m_count; i++) {
    Particle p;
    p.position.x = GetRandomValue(0, width);
    p.position.y = GetRandomValue(0, height);
    // TODO: velocity next

    p.color = raylib::Color(GetRandomValue(0, 255), GetRandomValue(0, 255),
                            GetRandomValue(0, 255), 255);

    m_particles.push_back(p);
  }
}

void ParticleSimulation::update(const double dt) {
  //
  //
}

void ParticleSimulation::render() {
  // check if auto works for raylib
  // do we multithread this?
  for (const auto &p : m_particles) {
    p.position.DrawCircle(1, p.color);
  }
}
