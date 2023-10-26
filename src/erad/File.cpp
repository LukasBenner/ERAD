//
// Created by lukas on 25.10.2023.
//

#include "erad/File.h"

#include <fstream>
#include <exception>
#include <utility>

namespace erad {
File::File(std::filesystem::path path, long long size)
    : path_(std::move(path)), size_(size) {
}

std::unique_ptr<File::Buffer> File::RemoveMemory() {
  if (!has_memory_) {
    throw std::bad_alloc{};
  }
  has_memory_ = false;
  return std::move(memory_);
}

void File::GrantMemory(std::unique_ptr<Buffer> mem) {
  if (mem->size() < size_)
    throw std::bad_alloc{};

  has_memory_ = true;
  memory_ = {std::move(mem)};
}

void File::WriteToDisk() const {
  std::ofstream file_stream{path_, std::ios::out | std::ios::binary | std::ios::ate};
  file_stream.seekp(0);
  file_stream.write((*memory_).data(), size_);
  file_stream.close();
}

void File::ReadFromDisk() {
  std::ifstream file_stream{path_, std::ios::in | std::ios::binary | std::ios::ate};

  const long long kFilesize = file_stream.tellg();
  if (kFilesize != size_)
    throw std::bad_alloc();

  file_stream.seekg(0, std::ios::beg);
  file_stream.read(memory_->data(), size_);
  file_stream.close();
}
}