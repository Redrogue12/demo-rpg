#pragma once

#include <cstdint>
#include <stdexcept>

typedef std::uint16_t stattype; // 0xFF 0-255

class StatBlock {
  stattype Strength;
  stattype Intellect;
  stattype Agility;
  stattype Armor;
  stattype Resistance;

public:
  StatBlock() {
    Strength = Intellect = Agility = (stattype)1u;
    Armor = Resistance = (stattype)0u;
  }

  explicit StatBlock(stattype s = 1u, stattype i = 1u, stattype a = 1u, stattype arm = 0u, stattype res = 0u) {
    Strength = s;
    Intellect = i;
    Agility = a;
    Armor = arm;
    Resistance = res;
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

  stattype getArmor() const {
    return Armor;
  }

  stattype getResistance() const {
    return Resistance;
  }

  void increaseStats(stattype s, stattype i, stattype a, stattype arm, stattype res) {
    if (s < 0 || i < 0 || a < 0) {
      throw std::invalid_argument("increaseStats called with a negative value.");
    }
    Strength += s;
    Intellect += i;
    Agility += a;
    Armor += arm;
    Resistance += res;
  }

protected:
  // void increaseStats(stattype s, stattype i) {
  //   Strength += s;
  //   Intellect += i;
  // }
};