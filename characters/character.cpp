// character.cpp
// character.h
#include "character.h"
#include "../state_machine/state.h"
#include "../libs.h"

// Character constructor for an unbound/placeholder character
Character::Character() {
	name = "UNBOUND";
	type = ELEMENT_UNBOUND;
}

// Character constructor that sets the character's name, element type and creature type
// stats are automatically generated, TODO and make it better
Character::Character(std::string Charname, Elements Elementtype, Creatures creature) {
	name = Charname;
	type = Elementtype;
	creature_type = creature;

	stats.level = 1;
	stats.exp = 5;
	stats.maxhp = 5;
	stats.hp = 5;
	stats.atk = 5;
	stats.def = 1; 
	stats.mag = 5;
	stats.mdef = 5;
	stats.speed = 5;

	// push an attack just to have one for now
	Attack fireball("Fireball", MAGIC, 0, 2, 10);
	attacks.push_back(fireball);
}

// Check if the current character is alive, with an HP stat of above 0
bool Character::is_alive() {
	return stats.hp > 0 ? true : false;
}

// Use an attack against an enemy and calculate damage
int Character::attack_with(Attack atk, Character enemy) {
	int atk_stat, def_stat; 

	// if the attack is physical, use physical atk/def
	// if the attack is magical, use magic atk/def
	// if it's unbound, return 0 to signify no damage
	switch (atk.type) {
		case PHYSICAL:
			atk_stat = stats.atk + atk.phy_damage;
			def_stat = enemy.stats.def;
			break; 

		case MAGIC:
			atk_stat = stats.mag + atk.mag_damage;
			def_stat = enemy.stats.mdef;
			break;
		default:
			return 0;
	}

	// if the attack does more than 0 damage, 
	// roll for crit chance and calculate damage
	if (atk_stat - def_stat > 0) {
		if (rand() % 100 <= atk.crit) {
			std::cout << "You landed a critical hit!\n";
			return atk_stat * 3 - def_stat;
		} else {
			return atk_stat - def_stat;
		}
	} 
	
	// if the attack doesn't do more than 0 damage, do 1 damage
	return 1;
}

int Character::is_effective(Attack atk, Character enemy) {
	// TODO implement
	return 1;
}

void Character::level_up() {
	if (rand() % 100 > 50) {
		this->stats.maxhp += 5;
		this->stats.atk += 5;
		this->stats.def += 5;
		this->stats.mag += 5;
		this->stats.mdef += 5;
		this->stats.speed += 5;

		std::cout << "All stats boosted!\n";	
	} else {
		this->stats.maxhp += 2;
		this->stats.atk += 3;
		this->stats.def += 5;
		this->stats.mag += 2;
		this->stats.mdef += 5;
		this->stats.speed += 1;

		std::cout << "All stats boosted a little!\n";
	}

	// implement type level ups
}

// Equip an item to a given character
void Character::equipItem(Item item) {
	// if the current slot for armor/ring/weapon is unbound,
	// put the current item in the equipped struct and 
	// add the item modifiers. If it isn't, don't do anything.
	switch (item.type) {
		case HEAD:
			if (this->equipped.headgear.name == "UNBOUND") {
				this->equipped.headgear = item;
			}
			break;
		case CHEST:
			if (this->equipped.chestgear.name == "UNBOUND") {
				this->equipped.chestgear = item;
			}
			break;
		case LEGS:
			if (this->equipped.leggear.name == "UNBOUND") {
				this->equipped.leggear = item;
			}
			break;
		case BOOTS:
			if (this->equipped.bootgear.name == "UNBOUND") {
				this->equipped.bootgear = item;
			}
			break;
		case RING:
			if (this->equipped.ring.name == "UNBOUND") {
				this->equipped.ring = item;
			}
			break;
		case WEAPON:
			if (this->equipped.weapon.name == "UNBOUND") {
				this->equipped.weapon = item;
			}
			break;
		default:
			std::cout << "Something is currently equipped!\n";
			return;
	}

	this->stats.maxhp += item.stats.hpmod;
	this->stats.hp += item.stats.hpmod;
	this->stats.atk += item.stats.atkmod;
	this->stats.def += item.stats.defmod;
	this->stats.mag += item.stats.magmod;
	this->stats.mdef += item.stats.mdefmod;
	this->stats.speed += item.stats.speedmod;
}

// Unequip an item to a give character
void Character::unequipItem(Item item) {
	Item unbound;

	// if the current slot for armor/ring/weapon is bound,
	// remove the current item in the equipped struct and 
	// remove the item modifiers. If it isn't, don't do anything.
	switch (item.type) {
		case HEAD:
			if (this->equipped.headgear.name != "UNBOUND") {
				this->equipped.headgear = unbound;
			}
			break;
		case CHEST:
			if (this->equipped.chestgear.name != "UNBOUND") {
				this->equipped.chestgear = unbound;
			}
			break;
		case LEGS:
			if (this->equipped.leggear.name != "UNBOUND") {
				this->equipped.leggear = unbound;
			}
			break;
		case BOOTS:
			if (this->equipped.bootgear.name != "UNBOUND") {
				this->equipped.bootgear = unbound;
			}
			break;
		case RING:
			if (this->equipped.ring.name != "UNBOUND") {
				this->equipped.ring = unbound;
			}
			break;
		case WEAPON:
			if (this->equipped.weapon.name != "UNBOUND") {
				this->equipped.weapon = unbound;
			}
			break;
		default:
			std::cout << "Nothing is currently equipped!\n";
			return;
	}

	this->stats.maxhp -= item.stats.hpmod;
	this->stats.hp -= item.stats.hpmod;
	this->stats.atk -= item.stats.atkmod;
	this->stats.def -= item.stats.defmod;
	this->stats.mag -= item.stats.magmod;
	this->stats.mdef -= item.stats.mdefmod;
	this->stats.speed -= item.stats.speedmod;
}
