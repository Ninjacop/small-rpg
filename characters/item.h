// item.h
// Teegan Lutze
#ifndef ITEM_H
#define ITEM_H

#include "../libs.h"

// Enum to store all the types of items
enum ItemType {
  HEAD = 0,
  CHEST, 
  LEGS,
  BOOTS,
  RING,
  WEAPON
};


class Item {
  public:
    // public variables -- name, type and stats
    std::string name;
    ItemType type;
    struct {
      int hpmod;
      int atkmod;
      int defmod;
      int magmod;
      int mdefmod;
      int speedmod;
    } stats;

    // Class constructors
    Item();
    Item(std::string, ItemType, int, int, int, int, int, int);
};

#endif