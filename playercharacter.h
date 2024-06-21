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

  PlayerCharacterDelegate() : StatBlock(0u, 0u) {
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

#define PCCONSTRUCT : PlayerCharacterDelegate() {\
  HP->setMaxWell(BASEHP);\
  HP->increaseCurrent(BASEHP);\
  increaseStats(BASESTR, BASEINT);\
}

#define LEVELUP void LevelUp() override {\
  HP->setMaxWell((welltype)(BASEHP/2.f) + (HP->getMaxWell()));\
  HP->increaseCurrent(BASEHP/2.f);\
  increaseStats((stattype)((BASESTR+1u)/2.f), (stattype)((BASEINT+1u)/2.f));\
}

class Cleric : public PlayerCharacterDelegate
{
public:
  static const welltype BASEHP = 14u;
  static const stattype BASESTR = 2u;
  static const stattype BASEINT = 3u;

  Cleric() PCCONSTRUCT;

  std::string getClassName() override {
    return std::string("Cleric");
  }

private:
  LEVELUP;
  
};

class Rogue : public PlayerCharacterDelegate {
public:
  static const welltype BASEHP = 12u;
  static const stattype BASESTR = 3u;
  static const stattype BASEINT = 2u;

  Rogue() PCCONSTRUCT;

  std::string getClassName() override {
    return std::string("Rogue");
  }

private:
  LEVELUP;
};

class Warrior : public PlayerCharacterDelegate {
public:
  static const welltype BASEHP = 18u;
  static const stattype BASESTR = 4u;
  static const stattype BASEINT = 1u;

  Warrior() PCCONSTRUCT;

  std::string getClassName() override {
    return std::string("Warrior");
  }

private:
  LEVELUP;
};

class Wizard : public PlayerCharacterDelegate {
public:
  static const welltype BASEHP = 10u;
  static const stattype BASESTR = 1u;
  static const stattype BASEINT = 4u;

  Wizard() PCCONSTRUCT;

  std::string getClassName() override {
    return std::string("Wizard");
  }

private:
  LEVELUP;
};


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

  void printCharacterSheet() {return pcclass->printCharacterSheet();}
  void gainEXP(exptype amt) { return pcclass->gainEXP(amt);} 
  void takeDamage(welltype amt) { return pcclass->HP->reduceCurrent(amt);}
  void heal(welltype amt) { return pcclass->HP->increaseCurrent(amt);}
};