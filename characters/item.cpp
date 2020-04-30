// item.cpp
// item.h
#include "item.h"

// Item constructor -- used for unbound/placeholder items
Item::Item() {
  this->name = "UNBOUND";
}

// Item constructor -- initialize an item's name, type, and stat modifiers
Item::Item(std::string name, ItemType type, int hpmod, int atkmod, int defmod, int magmod, int mdefmod, int speedmod) {
  this->name = name;
  this->type = type;
  this->stats.hpmod = hpmod;
  this->stats.atkmod = atkmod;
  this->stats.defmod = defmod;
  this->stats.magmod = magmod;
  this->stats.mdefmod = mdefmod;
  this->stats.speedmod = speedmod;
}