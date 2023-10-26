//
// Created by lukas on 25.10.2023.
//
#include "erad/Drive.h"

#include <utility>

erad::Drive::Drive(std::string drive_name)
    : name_(std::move(drive_name)) {
}
