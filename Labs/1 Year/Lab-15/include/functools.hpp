#pragma once

#include <stdexcept>
#include <sstream>
#include <string>
#include <cstdio>
#include <memory>
#include <array>
#include <mutex>

std::string exec(const std::string &cmd);

std::string hex(const std::string &num);

std::string to_upper(std::string str);

void tream(std::string &s);
