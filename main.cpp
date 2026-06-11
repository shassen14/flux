#include <App.hpp>
#include <Config.hpp>
#include <ParticleSimulation.hpp>

#include <iostream>

int main(int argc, char *argv[]) {
  // TODO: hardcode kind of works. fragile
  // have to run from root i.e. ./build/main
  // TODO: Magic strings and values
  const Config config = Config::Load("settings.toml");

  // window
  const int32_t width = config.Get<int32_t>("window", "width", 800);
  const int32_t height = config.Get<int32_t>("window", "height", 600);

  // simulation
  const size_t count = config.Get<size_t>("simulation", "total", 10);

  std::cout << "W: " << width << " H: " << height << "\n";

  App app(width, height);

  app.load<ParticleSimulation>(count);

  app.run();

  return 0;
}
