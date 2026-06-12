#pragma once

class ISimulation {
public:
  // destructor needs to be virtual because
  // non-virtual base destructor is undefined behavior
  virtual ~ISimulation() = default;

  // initialize any values for the simulator
  virtual void Init() = 0;

  // update physics model
  // pure virtual function
  virtual void Update(const float dt) = 0;

  // object rendering
  virtual void Render() = 0;

  // extra rendering for user
  virtual void RenderUI() = 0;
};
