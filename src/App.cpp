#include "Window.hpp"
#include <App.hpp>

#include <ParticleSimulation.hpp>
#include <raylib-cpp.hpp>

App::App(const int32_t width, const int32_t height)
    : m_window(static_cast<int>(width), static_cast<int>(height),
               "random title"),
      m_width(width), m_height(height) {
  m_window.SetTargetFPS(0);
}

// run
void App::run() {
  while (!m_window.ShouldClose()) {
    float dt = raylib::Window::GetFrameTime();

    m_simulation->Update(dt);

    // start drawing
    m_window.BeginDrawing();

    // blank canvas, default to black
    m_window.ClearBackground();

    // render object
    m_simulation->Render();

    m_simulation->RenderUI();

    // ends the drawing stage
    m_window.EndDrawing();
  }
  // TODO
  //
}
