#include <iostream>
#include "playercharacter.h"

int main() {
  PlayerCharacter pc1(new Cleric());

  pc1.printCharacterSheet();

  pc1.gainEXP(100u);

  pc1.printCharacterSheet();

  return 0;
}
