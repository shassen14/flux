#pragma once

#include <ISimulation.hpp>
#include <Particle.hpp>

#include <vector>

class ParticleSimulation : public ISimulation {
public:
  ParticleSimulation(const size_t count);

  void init() override;

  void update(const double dt) override;

  void render() override;

private:
  // particle state
  std::vector<Particle> m_particles;

  // number of particles
  size_t m_count;
};
