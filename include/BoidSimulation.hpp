#pragma once

#include "Vector2.hpp"
#include <Boid.hpp>
#include <ISimulation.hpp>

#include <vector>

class BoidSimulation : public ISimulation {
public:
  BoidSimulation(const size_t count);

  void Init() override;

  void Update(const float dt) override;

  void Render() override;

  void RenderUI() override;

private:
  raylib::Vector2 separation(const Boid &boid);

  raylib::Vector2 cohesion(const Boid &boid);

  raylib::Vector2 alignment(const Boid &boid);

  void draw_boid(const Boid &boid, const float size);

  // particle state
  std::vector<Boid> m_boids;

  // number of particles
  size_t m_count;
};
