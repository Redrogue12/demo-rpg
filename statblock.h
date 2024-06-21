#pragma once

#include <cstdint>

typedef std::uint16_t stattype; // 0xFF 0-255

class StatBlock {
  stattype Strength;
  stattype Intellect;

public:
  StatBlock() {
    Strength = 1u;
    Intellect = 1u;
  }

  explicit StatBlock(stattype s, stattype i) {
    Strength = s;
    Intellect = i;
  }

  stattype getStrength() const {
    return Strength;
  }

  stattype getIntellect() const {
    return Intellect;
  }

  void increaseStats(stattype s, stattype i)
  {
    Strength += s;
    Intellect += i;
  }

protected:
  // void increaseStats(stattype s, stattype i) {
  //   Strength += s;
  //   Intellect += i;
  // }
};