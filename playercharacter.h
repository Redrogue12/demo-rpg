#pragma once

#include <cstdint>
#include <memory>
#include <string>
#include "statblock.h"
#include "pointwell.h"

typedef std::uint64_t exptype;
typedef std::uint16_t leveltype;

class PlayerCharacterDelegate : public StatBlock {
public:
  static const exptype LEVEL2AT = 100u;

  PlayerCharacterDelegate() : StatBlock(0u, 0u, 0u) {
    CurrentLevel = 1u;
    CurrentEXP = 0u;
    EXPToNextLevel = LEVEL2AT;
    HP = std::make_unique<PointWell>();
  }

  void gainEXP(exptype gained_exp) {
    CurrentEXP += gained_exp;
    while (check_if_leveled()) {}
  }

  leveltype getLevel() {
    return CurrentLevel;
  }

  exptype getEXP() {
    return CurrentEXP;
  }

  exptype getEXPToNextLevel() {
    return EXPToNextLevel;
  }

  void printCharacterSheet() {
    std::cout << getClassName() << " Level " << getLevel() << '\n'
              << "-EXP: " << getEXP() << "/" << getEXPToNextLevel() << '\n'
              << "-HP: " << HP->getCurrentFullness() << "/" << HP->getMaxWell() << '\n'
              << "-Stength: " << getStrength() << '\n'
              << "-Intellect: " << getIntellect() << '\n'
              << "-Agility: " << getAgility() << '\n'
              << '\n';
  }

  virtual void LevelUp() = 0;
  virtual std::string getClassName() = 0;

  std::unique_ptr<PointWell> HP;

protected:
  leveltype CurrentLevel;
  exptype CurrentEXP;
  exptype EXPToNextLevel;
  
  bool check_if_leveled() {
    static const leveltype LEVELSCALAR = 2u;
    if (CurrentEXP >= EXPToNextLevel) {
      CurrentLevel++;
      LevelUp();
      EXPToNextLevel *= LEVELSCALAR;
      return true;
    }
    return false;
  }
};

#define PCCONSTRUCT : PlayerCharacterDelegate() { \
  HP->setMaxWell(BASEHP); \
  HP->increaseCurrent(BASEHP); \
  increaseStats(BASESTR, BASEINT, BASEAGI); \
}

#define LEVELUP                                                                                                          \
  void LevelUp() override                                                                                                \
  {                                                                                                                      \
    HP->setMaxWell((welltype)(BASEHP / 2.f) + (HP->getMaxWell()));                                                       \
    HP->increaseCurrent(BASEHP / 2.f);                                                                                   \
    increaseStats((stattype)((BASESTR + 1u) / 2.f), (stattype)((BASEINT + 1u) / 2.f), (stattype)((BASEAGI + 1u) / 2.f)); \
  }

#define CHARACTERCLASS(classname, basehp, basestr, baseint, baseagi) class classname : public PlayerCharacterDelegate { \
public: \
  static const welltype BASEHP = (welltype) basehp; \
  static const stattype BASESTR = (stattype) basestr; \
  static const stattype BASEINT = (stattype) baseint; \
  static const stattype BASEAGI = (stattype) baseagi; \
  std::string getClassName() override { \
    return std::string(#classname); \
  } \
  classname() PCCONSTRUCT \
private: \
  LEVELUP \
};

//             Class      HP, STR, INT, AGI  
CHARACTERCLASS(Cleric,    14,   3,   5,   1)
CHARACTERCLASS(Wizard,    10,   1,   8,   1)
CHARACTERCLASS(Warrior,   20,   5,   2,   2)
CHARACTERCLASS(Rogue,     14,   3,   3,   5)

class PlayerCharacter {
private:
  PlayerCharacterDelegate* pcclass;

public:
  PlayerCharacter() = delete;
  PlayerCharacter(PlayerCharacterDelegate* pc) : pcclass(pc) {}
  ~PlayerCharacter() {delete pcclass; pcclass = nullptr;}

  std::string getClassName() {return pcclass->getClassName();}
  exptype getEXP() {return pcclass->getEXP();}
  exptype getEXPToNextLevel() {return pcclass->getEXPToNextLevel();}
  leveltype getLevel() {return pcclass->getLevel();}
  welltype getCurrentHP() {return pcclass->HP->getCurrentFullness();}
  welltype getMaxHP() {return pcclass->HP->getMaxWell();}
  welltype getStrength() {return pcclass->getStrength();}
  welltype getIntellect() {return pcclass->getIntellect();}
  welltype getAgility() {return pcclass->getAgility();}

  void printCharacterSheet() {return pcclass->printCharacterSheet();}
  void gainEXP(exptype amt) { return pcclass->gainEXP(amt);} 
  void takeDamage(welltype amt) { return pcclass->HP->reduceCurrent(amt);}
  void heal(welltype amt) { return pcclass->HP->increaseCurrent(amt);}
};