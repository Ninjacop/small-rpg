// loop.h
// Teegan Lutze
#ifndef LOOP_H
#define LOOP_H

#include "../libs.h"
#include "../state_machine/world.h"
#include "../characters/character.h"
#include "../characters/npc.h"
#include "../state_machine/state.h"

class World;
class InventoryMenu;

class GameLoop {
	public:
    World curr_world;

    void handleInput(std::string);
    void enter(World);
    void update();
    void exit();
};

#endif