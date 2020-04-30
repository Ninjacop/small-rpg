// npc.cpp
// Teegan Lutze
#include "npc.h"
#include "character.h"

// NPC constructor -- set a name, dialogue, and item that they can give
// to the party.
NPC::NPC(std::string name, std::string dialogue, Item item) {
  this->name = name;
  this->dialogue = dialogue;
  this->has_given_item = false;
  this->givenItem = item;
}

// Give the NPC's item to the party if they haven't given them it 
// already
void NPC::giveItem(Character *player) {
  if (this->has_given_item == false) {
    player->inv.push_back(givenItem);
    this->has_given_item = true;

    std::cout << player->name << "You have received the " << givenItem.name << "!\n";
  } 
}

// Say the NPC's dialogue
void NPC::say() {
  std::cout << this->name << ": \"" << this->dialogue << "\"\n"; 
}