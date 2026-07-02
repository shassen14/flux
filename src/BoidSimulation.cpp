#include <Boid.hpp>
#include <BoidSimulation.hpp>

#include "Vector2.hpp"
#include "raylib.h"
#include <cmath>
#include <raylib-cpp.hpp>

BoidSimulation::BoidSimulation(const size_t count) : m_count(count) {
  m_boids.reserve(m_count);

  // hardcoded for now. TODO: change
  m_separation_weight = 1.0;
  m_cohesion_weight = 1.0;
  m_alignment_weight = 1.0;
  m_neighbor_distance = 20.0;
}

void BoidSimulation::Init() {
  const int32_t width = raylib::Window::GetWidth();
  const int32_t height = raylib::Window::GetHeight();

  for (size_t i = 0; i < m_count; i++) {
    Boid b;
    b.position.x = GetRandomValue(0, width);
    b.position.y = GetRandomValue(0, height);

    b.velocity.x = GetRandomValue(-255, 255);
    b.velocity.y = GetRandomValue(-255, 255);

    b.acceleration.x = GetRandomValue(-128, 128);
    b.acceleration.y = GetRandomValue(-128, 128);

    b.color = raylib::Color(GetRandomValue(0, 255), GetRandomValue(0, 255),
                            GetRandomValue(0, 255), 255);

    m_boids.push_back(b);
  }
}

void BoidSimulation::Update(const float dt) {
  //
  //
  const int32_t width = raylib::Window::GetWidth();
  const int32_t height = raylib::Window::GetHeight();

  // calculate acceleration
  for (Boid &boid : m_boids) {
    raylib::Vector2 sep = separation(boid) * m_separation_weight;
    raylib::Vector2 align = alignment(boid) * m_alignment_weight;
    raylib::Vector2 coh = cohesion(boid) * m_cohesion_weight;

    boid.acceleration += sep + align + coh;
  }

  // update
  for (Boid &boid : m_boids) {
    // velocity. TODO: clamp velocity
    boid.velocity += boid.acceleration * dt;

    // position update
    boid.position += boid.velocity * dt;

    // boundary checks
    if (boid.position.x < 0) {
      boid.position.x = 0;
    }
    if (boid.position.y < 0) {
      boid.position.y = 0;
    }
    if (boid.position.x > width) {
      boid.position.x = width;
    }
    if (boid.position.y > height) {
      boid.position.y = height;
    }
  }
}

// render
void BoidSimulation::Render() {
  for (const Boid &boid : m_boids) {
    draw_boid(boid, 15.0f);
  }
}

void BoidSimulation::RenderUI() {
  ///
  ///
  ///
  raylib::Window::DrawFPS(10, 10);
}

///////// private //////////

raylib::Vector2 BoidSimulation::separation(const Boid &boid) {
  return raylib::Vector2(0, 0);
}

raylib::Vector2 BoidSimulation::cohesion(const Boid &boid) {
  return raylib::Vector2(0, 0);
}

raylib::Vector2 BoidSimulation::alignment(const Boid &boid) {
  return raylib::Vector2(0, 0);
}

void BoidSimulation::draw_boid(const Boid &boid, const float size) {
  // heading angle
  const float heading = std::atan2(boid.velocity.y, boid.velocity.x);

  // size will be the length
  // width will be the half length
  const float width = size * 0.5f;

  // 4 points, local, facing "east"
  const raylib::Vector2 local_tip(size, 0.0f);
  const raylib::Vector2 local_left(0.0f, width);
  const raylib::Vector2 local_right(0.0f, -width);
  const raylib::Vector2 local_indent(size * 0.5f, 0.0f);

  // transform function
  auto local_to_global_transform =
      [&](const raylib::Vector2 &point) -> raylib::Vector2 {
    const float global_x =
        point.x * std::cos(heading) - point.y * std::sin(heading);
    const float global_y =
        point.x * std::sin(heading) + point.y * std::cos(heading);

    return raylib::Vector2(global_x, global_y) + boid.position;
  };

  // transform to global
  const raylib::Vector2 global_tip = local_to_global_transform(local_tip);
  const raylib::Vector2 global_left = local_to_global_transform(local_left);
  const raylib::Vector2 global_right = local_to_global_transform(local_right);
  const raylib::Vector2 global_indent = local_to_global_transform(local_indent);

  // draw the 2 triangles
  // TODO: check how this works. the ordering matters, I don't know why
  DrawTriangle(global_left, global_tip, global_indent, boid.color);
  DrawTriangle(global_tip, global_right, global_indent, boid.color);
}
