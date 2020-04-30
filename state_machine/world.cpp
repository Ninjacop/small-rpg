// world.cpp
// Teegan Lutze
#include "world.h"
#include "state.h"
#include "../characters/character.h"
#include "../characters/npc.h"

// Location constructor -- sets a unbound/placeholder location
Location::Location() {
  this->name = "UNBOUND";
}

// Location constructor -- name and location type
Location::Location(std::string name, LocationType loc_type) {
  this->name = name;
  this->loc_type = loc_type;
}

// Set the enemies in a certain location
void Location::setEnemies(std::vector<Character> enemies) {
  this->enemies = enemies;
}

// Set the townfolk/NPCs in a certain location
void Location::setTownfolk(std::vector<NPC> npcs) {
  this->townfolk = npcs;
}

// Initialize the possible locations to go to 
void Location::initNodes(Location l) {
  for (int i = 0; i < 3; i++) {
    this->dirs.push_back(&l);
  }
}

// Set a location to go to on one of the nodes
void Location::setNode(Directions dir, Location loc) {
  this->dirs.push_back(&loc);
}

// Placeholder World constructor
World::World() {
  // empty lol
}

// Add a character to the world
// push it to the party if it's a player
// push it to the enemies if it's an enemy
void World::addCharacter(Character c) {
  if (c.creature_type == PLAYER) {
    this->addToParty(c);
  } else {
    this->addToEnemies(c);
  }
}

// Add the character to the party and set its 
// character ID
void World::addToParty(Character character) {
  party.push_back(character);
  character.character_id = party.size();
}

// Add the character to the enemies and set its
// character ID
void World::addToEnemies(Character enemy) {
  enemies.push_back(enemy);
  enemy.character_id = enemies.size();
}

// TODO implement
// enter a random encounter with enemies in the current location
void World::randomEncounter(int amnt) {
  std::vector<Character> rand_enemies;

  // lol
}

// Clear the enemy party
void World::clearEnemies() {
  enemies.clear();
}

// Start a battle with given enemies and party
void World::startBattle(std::vector<Character> enemies) {
  this->enemies = enemies;

  Battle b(this->party, this->enemies);
  b.enter(this->party.at(0));

  // update teams
  this->party = b.player_team;
  this->enemies = b.enemy_team;
}