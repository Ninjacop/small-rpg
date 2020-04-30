#include "libs.h"
#include "state_machine/state.h"
#include "characters/character.h"
#include "characters/npc.h"
#include "state_machine/world.h"
#include "loop_machine/loop.h"

// OVERWORLD
// start in Town1 -> move East -> Plains
// start in Plains -> move East -> Port1
// start in Port1 -> moveNorth -> Cave
int main() {
  // Create the game loop and world
  GameLoop gl;
  World world;

  // Create locations
  Location davusch("Davusch", TOWN);
  Location plains("Plains", PLAINS);
  Location cave("Cave", CAVE);
  Location feniport("Feniport", TOWN);
  Location empty_loc;

  // Create townfolk and enemies vectors for locations
  std::vector<NPC> davusch_npcs;
  std::vector<NPC> feniport_npcs;
  std::vector<Character> plains_mobs;
  std::vector<Character> cave_mobs;

  // Create Items
  Item unboundItem;
                                  // hp atk def mag mdef speed
  Item ironSword("Iron Sword", WEAPON, 0, 5, 0, 0, 0, 0);
  Item demonSword("Demon Sword", WEAPON, 10, 10, 10, 10, 10, 10);


  // Create players
  Character teegan("Teegan", WATER, PLAYER);
  Character michael("Michael", FIRE, PLAYER);

  // Create enemies
  Character goon("Goon", NONE, ENEMY);
  Character slime("Slime", NONE, ENEMY);
  Character skeleton("Skeleton", NONE, ENEMY);
  Character treant("Treant", NONE, ENEMY);

  // Create NPCs - Davusch
  NPC duskin("Duskin", "Beware of enemies outside the town.", unboundItem);
  NPC paltria("Paltria", "Take care!", unboundItem);
  NPC qqq("???", "It's dangerous to go alone. Take this.", ironSword);

  // Create NPCs - Feniport
  NPC bruce("Bruce", "My boat has sunk! Could you please find some parts?", unboundItem);
  NPC lennox("Lennox", "I pity you.", unboundItem);
  NPC shopkeeper("Shopkeeper", "What would you like today?", unboundItem);

  // Set NPCs, enemies
  davusch_npcs.push_back(duskin);
  davusch_npcs.push_back(paltria);
  davusch_npcs.push_back(qqq);

  feniport_npcs.push_back(bruce);
  feniport_npcs.push_back(lennox);
  feniport_npcs.push_back(shopkeeper);

  plains_mobs.push_back(goon);
  plains_mobs.push_back(treant);

  cave_mobs.push_back(slime);
  cave_mobs.push_back(skeleton);

  // Set townfolk and enemies
  davusch.setTownfolk(davusch_npcs);
  feniport.setTownfolk(feniport_npcs);
  plains.setEnemies(plains_mobs);
  cave.setEnemies(cave_mobs);

  /* Init nodes
  davusch.initNodes(empty_loc);
  feniport.initNodes(empty_loc);
  plains.initNodes(empty_loc);
  cave.initNodes(empty_loc);
  */

  // Set nodes
  plains.dirs.push_back(&davusch);
  plains.dirs.push_back(&feniport);
  davusch.dirs.push_back(&plains);
  cave.dirs.push_back(&feniport);
  feniport.dirs.push_back(&plains);
  feniport.dirs.push_back(&cave);

  // Add the main party member to the world
  // Set the current location to Davusch
  world.addCharacter(teegan);
  world.curr_loc = davusch;

  // Enter the game loop
  gl.enter(world);

  return 0;
}