// npc.h
// Teegan Lutze
#ifndef NPC_H
#define NPC_H

#include "../libs.h"
#include "item.h"

// forward declaration of Character and Item so
// the NPC class can use them
class Character;
class Item; 

class NPC {
  public:
    // public variables -- name, dialogue and an item
    std::string name;
    std::string dialogue;
    Item givenItem;

    // flag to check if NPC has given their item
    bool has_given_item;

    // Class constructor
    NPC(std::string, std::string, Item);

    // Functions
    void giveItem(Character*);
    void say();
};

#endif