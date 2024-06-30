#pragma once

#include <cstdint>

typedef std::uint16_t welltype;

class PointWell {
public:
  welltype getMaxWell() {
    return MaxWell;
  }

  welltype getCurrentFullness() {
    return CurrentFullness;
  }

  PointWell() {
    CurrentFullness = 1;
    MaxWell = 1;
  }

   PointWell(welltype c, welltype m) {
    CurrentFullness = c;
    MaxWell = m;
    if (CurrentFullness > MaxWell)
      CurrentFullness = MaxWell;
  }

  // returns true if set successfully
  bool setMaxWell(welltype new_max) {
    if (new_max < 1)
      return false;

    MaxWell = new_max;

    if (CurrentFullness > MaxWell)
      CurrentFullness = MaxWell;

    return true;
  }

  void reduceCurrent(welltype damage) {
    if (damage > CurrentFullness) {
      CurrentFullness = 0;
      return;
    }
    
    CurrentFullness -= damage;
  }

  void increaseCurrent(welltype amount) {
    if ((amount + CurrentFullness) > MaxWell)
      CurrentFullness = MaxWell;
      return;

    CurrentFullness += amount;
  }

private:
  welltype CurrentFullness;
  welltype MaxWell;
};