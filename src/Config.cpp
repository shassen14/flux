#include <Config.hpp>

#include <iostream>
#include <toml.hpp>

Config Config::Load(std::string_view file_path) {
  Config config;

  try {
    config.m_table = toml::parse_file(file_path);

    std::cout << "[Config] Successfully loaded: " << file_path << "\n";
  } catch (const toml::parse_error &error) {
    std::cerr << "[Error][Config] Failed to parse: " << file_path << "\n"
              << error.description() << "\n"
              << "Default values will be used\n";
  }

  return config;
}
