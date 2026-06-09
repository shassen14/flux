#include <Config.hpp>

#include <iostream>

// this must be before all to replace some headers
// interesting how ordering matters
#include <glad.h>

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <imgui/imgui.h>

int main(int argc, char *argv[]) {
  // TODO: hardcode kind of works. fragile
  // have to run from root i.e. ./build/main
  // TODO: Magic strings and values
  const Config config = Config::Load("settings.toml");

  const int width = config.Get("window", "width", 123);
  const int height = config.Get("window", "height", 123);

  std::cout << "W: " << width << " H: " << height << "\n";

  return 0;
}
