// character.h
// Teegan Lutze
#ifndef CHARACTER_H
#define CHARACTER_H

#include "attack.h"
#include "item.h"
#include "player_enums.h"

// declare Item and World classesforward so the Character class
// can use it
class World;
class Item;

class Character {
  public:
    // public variables -- name, element type, creature types, attacks,
    // stats, equipped items and inventory
    std::string name;
    Elements type;
    Creatures creature_type;
    struct {
      int level;
      int exp;
      int maxhp;
      int hp;
      int atk;
      int def; 
      int mag;
      int mdef;
      int speed;
    } stats;
    
    std::vector<Attack> attacks;
    
    std::vector<Item> inv;
    
    struct {
      Item headgear;
      Item chestgear;
      Item leggear;
      Item bootgear;
      Item ring;
      Item weapon;
    } equipped;

    // unique character id to use later 
    // to tell multiple of the same enemies from
    // each other
    int character_id;

    // Character constructors
    Character();
    Character(std::string, Elements, Creatures);

    // Functions that a Character can use
    bool is_alive();
    int attack_with(Attack, Character);
    int is_effective(Attack, Character);
    void level_up();
    void equipItem(Item);
    void unequipItem(Item);
};
#endif