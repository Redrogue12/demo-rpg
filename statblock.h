#pragma once

#include <cstdint>

typedef std::uint16_t stattype; // 0xFF 0-255

class StatBlock {
  stattype Strength;
  stattype Intellect;
  stattype Agility;

public:
  StatBlock() {
    Strength = Intellect = Agility = (stattype)1u;
  }

  explicit StatBlock(stattype s, stattype i, stattype a) {
    Strength = s;
    Intellect = i;
    Agility = a;
  }

  stattype getStrength() const {
    return Strength;
  }

  stattype getIntellect() const {
    return Intellect;
  }

  stattype getAgility() const {
    return Agility;
  }

  void increaseStats(stattype s, stattype i, stattype a)
  {
    Strength += s;
    Intellect += i;
    Agility += a;
  }

protected:
  // void increaseStats(stattype s, stattype i) {
  //   Strength += s;
  //   Intellect += i;
  // }
};