//
// Created by lukas on 25.10.2023.
//

#pragma once

#include <vector>
#include <memory>
#include <filesystem>

namespace erad {
class File {
 public:
  using Buffer = std::vector<char>;

  File(std::filesystem::path path, long long size);

  void GrantMemory(std::unique_ptr<Buffer> mem);
  [[nodiscard]] std::unique_ptr<Buffer> RemoveMemory();

  void WriteToDisk() const;
  void ReadFromDisk();

  std::filesystem::path path_{};
  long long size_{};
  unsigned long long offset_{};

  std::unique_ptr<Buffer> memory_{nullptr};
 private:
  bool has_memory_{false};

};
}
