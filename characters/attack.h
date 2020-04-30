// attack.h
// Teegan Lutze
#ifndef ATTACK_H
#define ATTACK_H

#include "../libs.h"

// Enum of all possible attack types
enum attackTypes {
	PHYSICAL = 0,
	MAGIC,
	ATTACK_UNBOUND
};

// The Attack class 
class Attack {
  public:
	// public variables, such as it's name and types of damage
	std::string name;
	attackTypes type;
	int phy_damage;
	int mag_damage;
	int crit;

	// class constructors
	Attack();
    Attack(std::string, attackTypes, int, int, int);
};

#endif