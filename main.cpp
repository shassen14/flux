// TODO: mess with CMake to get rid of include
// and also "". I think there will be issue regarding linking
// include with src
#include <ISimulation.hpp>
#include <Objects.hpp>

#include <iostream>
#include <memory>
#include <print>
#include <vector>

// this must be before all to replace some headers
// interesting how ordering matters
#include <glad.h>

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <imgui/imgui.h>

int main(int argc, char *argv[]) {
  std::vector<std::unique_ptr<ISimulation>> objects;

  std::print("hello");

  Object::Particle bob;
  bob.position.x = 50.5;

  std::cout << "position: (" << bob.position.x << ", " << bob.position.y
            << ")\n";

  return 0;
}
