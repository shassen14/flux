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
  // template<typename SimType, typename... Args>
  void load();

  // updates, renders
  void run();

private:
  raylib::Window m_window;

  std::unique_ptr<ISimulation> m_simulation;

  size_t m_width;

  size_t m_height;
};
