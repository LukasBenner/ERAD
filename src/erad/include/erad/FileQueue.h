//
// Created by lukas on 25.10.2023.
//
#pragma once

#include "File.h"

#include <queue>
#include <mutex>

namespace erad {
class FileQueue {
 public:
  FileQueue() = default;

  void AddFile(File file);
  File GetFile();

  [[nodiscard]] inline bool HasFile() const { return !files_.empty(); }
  [[nodiscard]] inline size_t Size() const { return files_.size(); }

  std::mutex mtx_{};
  std::condition_variable not_empty_{};

 private:
  std::queue<File> files_{};
};
}