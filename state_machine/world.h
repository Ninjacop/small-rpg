#ifndef WORLD_H
#define WORLD_H

#include "../libs.h"
#include "../characters/player_enums.h"

class Character;
class NPC;

enum LocationType {
  TOWN = 0, 
  CAVE,
  PLAINS
};

enum Directions {
  NORTH = 0,
  SOUTH, 
  EAST,
  WEST
};

class Location {
  public:
    std::string name;
    LocationType loc_type;
    std::vector<Character> enemies;
    std::vector<NPC> townfolk;
    std::vector<Location*> dirs; 

    Location();
    Location(std::string, LocationType);
    void setEnemies(std::vector<Character>);
    void setTownfolk(std::vector<NPC>);
    void initNodes(Location);
    void setNode(Directions, Location);
};

class World {
  public:
    std::vector<Character> party;
    std::vector<Character> enemies;
    std::vector<Location> all_locations;
    Location curr_loc;
    // other special info put here

    World();
    void addCharacter(Character);
    void addToParty(Character);
    void addToEnemies(Character);
    void randomEncounter(int);
    void clearEnemies();

    void startBattle(std::vector<Character>);
};
#endif