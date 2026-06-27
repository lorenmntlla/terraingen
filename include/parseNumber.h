#pragma once
#include <string_view>
#include <charconv>

template <typename T> T parseNumber(std::string_view sv, int base = 10) {
  T number{};
  std::from_chars(sv.data(), sv.data() + sv.size(), number, base);

  return number;
}
