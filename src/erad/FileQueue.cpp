//
// Created by lukas on 25.10.2023.
//

#include "erad/FileQueue.h"

#include <utility>

namespace erad {

void FileQueue::AddFile(File file) {
  std::unique_lock<std::mutex> unique_lock(mtx_);
  files_.push(std::move(file));
  unique_lock.unlock();
  not_empty_.notify_one();
}

File FileQueue::GetFile() {
  std::unique_lock<std::mutex> unique_lock(mtx_);

  not_empty_.wait(unique_lock, [this]() {
    return HasFile();
  });

  auto file{std::move(files_.front())};
  files_.pop();
  unique_lock.unlock();
  return file;
}

}
