#pragma once

#include <ISimulation.hpp>

#include <memory>
#include <raylib-cpp.hpp>

class App {
public:
  App(const int32_t width, const int32_t height);

  ~App() = default;

  // load simulation function?
  // I'm thinking templated with known SimType
  // and then variadic args for the simulator
  template <typename SimType, typename... Args> void Load(Args &&...args) {
    // check if sim type is derived from ISimulation
    static_assert(std::is_base_of_v<ISimulation, SimType>);

    // perfect forwarding for variadic args in order to support
    // different simulation that take in different args and ensure
    // that they are inputted correctly via value type lval and rval
    m_simulation = std::make_unique<SimType>(std::forward<Args>(args)...);

    m_simulation->Init();
  }

  // updates, renders
  void run();

private:
  raylib::Window m_window;

  std::unique_ptr<ISimulation> m_simulation;

  size_t m_width;

  size_t m_height;
};
