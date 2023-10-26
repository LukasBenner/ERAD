//
// Created by lukas on 25.10.2023.
//

#pragma once

#include <string>
#include <filesystem>

namespace erad {
class Drive {
 public:
  explicit Drive(std::string drive_name);

  std::string name_{};
  [[nodiscard]] std::filesystem::path Path() const { return name_ + ":\\\\"; }

 private:

};
}


