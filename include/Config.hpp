#pragma once

#include <iostream>
#include <string_view>
#include <toml.hpp>

class Config {
public:
  // return a stateless Config
  // call this function to construct the object
  static Config Load(std::string_view file_path);

  // don't have to pass by reference for string_view because
  // it's a non-owning string slice
  // basically a pointer and length is copied and no need
  // for indirection
  template <typename T>
  T Get(std::string_view section, std::string_view key, T default_value) const {

    // optional<node> -> Some(node) if section and key exists in m_table
    if (toml::node_view<const toml::node> node = m_table[section][key]) {
      // try to convert node's value to type T
      if (auto val = node.value<T>()) {
        return *val;
      }
    }

    std::cerr << "[Error] Config missing or wrong type for: [" << section
              << "][" << key << "] - Using default value: " << default_value
              << "\n";
    return default_value;
  }

private:
  toml::table m_table;
};
