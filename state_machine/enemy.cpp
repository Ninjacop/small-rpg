// enemy.cpp
// Teegan Lutze
#include "state.h"
#include "../characters/character.h"

// Enter the EnemyAI State Machine
void EnemyAI::enter(Character enemy, std::vector<Character> players) {
  selected = &enemy;
  selected_players = players;

  // Update the EnemyAI State Machine
  EnemyAI::update();
}

// Update the EnemyAI State Machine
void EnemyAI::update() {
  // Precautionary check to see if the player team has more than 1 player
  if (selected_players.size() > 0) {
    selected_player = &selected_players.at(rand() % selected_players.size());
  } else { 
    // Otherwise grab the firs player
    selected_player = &selected_players.at(0);
  }

  // TODO implement effectiveness
  // Choose a random attack 
  selected_atk = &selected->attacks.at(rand() % selected->attacks.size());

  // Exit the EnemyAI State Machine
  EnemyAI::exit();
}

// Exit the EnemyAI State Machine
// Do damage to the selected player 
void EnemyAI::exit() {
  // Calculate damage
  int damage = selected->attack_with(*selected_atk, *selected_player);

	std::cout << "The " << selected->name << " did " << damage << " damage to " << selected_player->name << "!\n";

  // Set the selected player's HP in the `selected_players` vector and the player themselves
	for (int i = 0; i < selected_players.size(); i++)	{
		if (selected_player->character_id == selected_players.at(i).character_id) {
			selected_players.at(i).stats.hp -= damage;

      if (selected_players.at(i).stats.hp < 0) {
        selected_players.at(i).stats.hp = 0;
      } 

			selected_player = &selected_players.at(i);
		}
	}

  // If the player dies, announce that they died
	if (selected_player->is_alive() == 0) {
		std::cout << selected_player->name << " fell!\n";
	}
}