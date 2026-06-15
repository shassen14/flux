#include <ParticleSimulation.hpp>

#include "Color.hpp"
#include "Functions.hpp"
#include "State.hpp"
#include "Window.hpp"
#include "raylib.h"
#include <format>
#include <raylib-cpp.hpp>
#include <thread>

///////////// Public /////////////////

// TODO: Hardcoded values / strings need to be not that
ParticleSimulation::ParticleSimulation(const size_t count)
    : m_count(count), m_mode(ComputeMode::SingleThreaded) {
  m_particles.reserve(m_count);
}

void ParticleSimulation::Init() {
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

void ParticleSimulation::Update(const float dt) {
  // TODO Enum select
  // get width and height of window
  // spawn particles within here
  const int32_t width = raylib::Window::GetWidth();
  const int32_t height = raylib::Window::GetHeight();

  if (m_mode == ComputeMode::SingleThreaded) {
    update_single_threaded(dt, width, height);

  } else {
    update_multi_threaded(dt, width, height);
  }
}

// single threaded
void ParticleSimulation::update_single_threaded(const float dt,
                                                const int32_t width,
                                                const int32_t height) {
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

// multi-threaded
void ParticleSimulation::update_multi_threaded(const float dt,
                                               const int32_t width,
                                               const int32_t height) {
  // get number of threads
  int32_t num_threads =
      std::min(static_cast<int32_t>(std::thread::hardware_concurrency()),
               static_cast<int32_t>(m_particles.size()));

  // each thread is responsible for chunk of particles
  size_t chunk_size = m_particles.size() / num_threads;

  std::vector<std::thread> threads;

  // what does each thread work on in terms of part of the vector
  auto worker = [&](const size_t begin, const size_t end) -> void {
    for (size_t i = begin; i < end; i++) {
      Particle &p = m_particles[i];
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
  };

  // spawn
  for (int32_t i = 0; i < num_threads; i++) {
    size_t begin = i * chunk_size;
    size_t end = i + 1 == num_threads ? m_count : begin + chunk_size;
    // give a function and then variadic templating for the arguments go
    // into the function signature
    threads.emplace_back(worker, begin, end);
  }

  // join
  for (auto &thread : threads) {
    thread.join();
  }
}

void ParticleSimulation::Render() {
  // check if auto works for raylib
  // do we multithread this?
  for (const auto &p : m_particles) {
    p.position.DrawPixel(p.color);
  }
}

void ParticleSimulation::RenderUI() {

  // fps
  raylib::Window::DrawFPS(10, 10);

  // num particles
  std::string particle_string = std::format("{} particles", m_count);
  raylib::DrawText(particle_string, 10, 30, 15, raylib::Color::White());

  // mode
  std::string mode_string = std::format(
      "{}", m_mode == ComputeMode::SingleThreaded ? "Mode: Single Threaded"
                                                  : "Mode: Multi-Threaded");
  raylib::DrawText(mode_string, 10, 50, 15, raylib::Color::White());

  // toggling
  if (::IsKeyPressed(::KEY_SPACE)) {
    m_mode = m_mode == ComputeMode::SingleThreaded
                 ? ComputeMode::MultiThreaded
                 : ComputeMode::SingleThreaded;
  }
}
