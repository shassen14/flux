#pragma once

class ISimulation {
public:
  // destructor needs to be virtual because
  // non-virtual base destructor is undefined behavior
  virtual ~ISimulation() = default;

  // initialize any values for the simulator
  virtual void init() = 0;

  // update physics model
  // pure virtual function
  virtual void update(const double dt) = 0;

  virtual void render() = 0;
};
