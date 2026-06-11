#include "Vector2.hpp"
#include <App.hpp>
#include <Config.hpp>
#include <Particle.hpp>
#include <ParticleSimulation.hpp>

#include <iostream>

int main(int argc, char *argv[]) {
  // TODO: hardcode kind of works. fragile
  // have to run from root i.e. ./build/main
  // TODO: Magic strings and values
  const Config config = Config::Load("settings.toml");

  const int32_t width = config.Get<int32_t>("window", "width", 800);
  const int32_t height = config.Get<int32_t>("window", "height", 600);

  std::cout << "W: " << width << " H: " << height << "\n";

  App app(width, height);

  app.load();

  app.run();

  // To delete
  ParticleSimulation foo(100uz);
  foo.init();

  Particle p;
  p.position.x = 2020.023;
  p.position.y = 100;
  p.velocity = raylib::Vector2(2.0f, 30.0f);
  std::cout << p;

  return 0;
}
