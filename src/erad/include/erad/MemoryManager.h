//
// Created by lukas on 25.10.2023.
//

#pragma once

#include "File.h"

#include <mutex>
#include <queue>

namespace erad {

class MemoryManager {
 public:

  MemoryManager() = delete;
  explicit MemoryManager(int number_buffers, size_t max_file_size);

  void RemoveMemory(File &file);
  void GrantMemory(File &file);

  inline bool HasMemory() { return !buffers_.empty(); }

  std::mutex mtx_{};
  std::condition_variable not_empty_{};

 private:
  std::queue<std::unique_ptr<File::Buffer>> buffers_{};
};

}
