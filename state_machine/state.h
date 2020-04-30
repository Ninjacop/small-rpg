// state.h
// Teegan Lutze
#ifndef STATE_H
#define STATE_H

#include "../libs.h"
#include "../characters/player_enums.h"

// Forward declaration of Character and Attack so it can be used
// for all the State Machines below
class Character;
class Attack;

// Battle State Machine
class Battle {
  public:
    // public variables -- turn order, and teams
    std::vector<Character> charorder;
		std::vector<Character> player_team;
		std::vector<Character> enemy_team;

    // Class constructor 
		Battle(std::vector<Character>, std::vector<Character>);

    // Helper functions
		bool isTeamAlive(std::vector<Character>);
		bool isInTeam(std::vector<Character>, Character);

    // Main State Machine functions
    void handleInput(Character);
    void enter(Character);
    void update(Character);
    void exit(int);
};

// EnemyAI State Machine
class EnemyAI {
  public: 
    // public variables -- selected enemy, player, player team and attack
    Character *selected;
    Character *selected_player;
    std::vector<Character> selected_players;
    Attack *selected_atk;

    // Main State Machine functions
    void enter(Character, std::vector<Character>);
    void update();
    void exit();
};

// Attack Menu State Machine
class AttackMenu {
  public:
    // public variables -- selected player, enemies, enemy, and attack
    Character *selected;
    std::vector<Character> selected_enemies;
    Character *selected_enemy;
    Attack *selected_atk;

    // Main State Machine functions
    void handleInput();
    void enter(Character, std::vector<Character>);
    void update();
    void select_enemy();
    void exit();
};

// TODO FULLY IMPLEMENT
class InventoryMenu {
  public:
    Character *selected;

    void enter(Character);
    void update();
    void handleInput();
    void exit();
};

// TODO IMPLEMENT
class ItemMenu {
  public:
  // public variable -- selected character for item menu
  Character *selected;
  
  // Main State Machine functions
  void handleInput();
  void enter(Character);
  void update();
  void exit();
};
#endif