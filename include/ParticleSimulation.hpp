#pragma once

#include <ISimulation.hpp>
#include <Particle.hpp>
#include <State.hpp>

#include <vector>

class ParticleSimulation : public ISimulation {
public:
  ParticleSimulation(const size_t count);

  void Init() override;

  void Update(const float dt) override;

  void Render() override;

  void RenderUI() override;

private:
  void update_single_threaded(const float dt, const int32_t width,
                              const int32_t height);

  void update_multi_threaded(const float dt, const int32_t width,
                             const int32_t height);

  // particle state
  std::vector<Particle> m_particles;

  // number of particles
  size_t m_count;

  ComputeMode m_mode;
};
