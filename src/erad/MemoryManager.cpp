//
// Created by lukas on 25.10.2023.
//

#include "erad/MemoryManager.h"

namespace erad {

MemoryManager::MemoryManager(int number_buffers, size_t max_file_size) {
  for (int it = 0; it < number_buffers; ++it) {
    auto buf = std::make_unique<File::Buffer>();
    buf->resize(max_file_size);
    buffers_.push(std::move(buf));
  }
}

void MemoryManager::RemoveMemory(File &file) {
  std::unique_lock<std::mutex> unique_lock(mtx_);
  buffers_.emplace(file.RemoveMemory());
  unique_lock.unlock();
  not_empty_.notify_one();
}

void MemoryManager::GrantMemory(File &file) {
  std::unique_lock<std::mutex> unique_lock(mtx_);

  not_empty_.wait(unique_lock, [this]() {
    return HasMemory();
  });

  auto ptr{std::move(buffers_.front())};
  buffers_.pop();
  file.GrantMemory(std::move(ptr));
  unique_lock.unlock();
}

}
