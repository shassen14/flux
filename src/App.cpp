#include "Window.hpp"
#include <App.hpp>

#include <ParticleSimulation.hpp>
#include <memory>
#include <raylib-cpp.hpp>

App::App(const int32_t width, const int32_t height)
    : m_window(static_cast<int>(width), static_cast<int>(height),
               "random title"),
      m_width(width), m_height(height) {
  // 60 fps, maybe change this to not harcoded? TODO
  m_window.SetTargetFPS(60);
}

// run
void App::run() {
  while (!m_window.ShouldClose()) {
    float dt = raylib::Window::GetFrameTime();

    m_simulation->update(dt);

    // start drawing
    m_window.BeginDrawing();

    // blank canvas, default to black
    m_window.ClearBackground();

    // some random textbox
    // m_window.DrawText("hello world", 10, 10, 20, raylib::Color::Green());
    // raylib::DrawText("hello world", 400, 300, 20, raylib::Color::Green());
    m_simulation->render();

    m_window.DrawFPS(10, 10);

    // ends the drawing stage
    m_window.EndDrawing();
  }
  // TODO
  //
}
