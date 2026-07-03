#include <App.hpp>
#include <Config.hpp>
#include <SimulationRegistry.hpp>

int main(int argc, char *argv[]) {
  // TODO: hardcode kind of works. fragile
  // have to run from root i.e. ./build/main
  // TODO: Magic strings and values
  const Config config = Config::Load("settings.toml");

  // window
  const int32_t width = config.Get<int32_t>("window", "width", 800);
  const int32_t height = config.Get<int32_t>("window", "height", 600);
  App app(width, height);

  const std::string sim_type =
      config.Get<std::string>("simulation", "type", "particle");

  if (!DispatchSimulation(sim_type, config, app)) {
    return -1;
  }

  app.run();

  return 0;
}
