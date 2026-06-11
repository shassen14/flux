#include <App.hpp>
#include <Config.hpp>
#include <Particle.hpp>

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

  app.run();

  Particle p;
  p.position.x = 20;
  std::cout << p.position.x << " " << p.position.y << "\n";

  return 0;
}
