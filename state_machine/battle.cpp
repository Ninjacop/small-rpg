// battle.cpp
// Teegan Lutze
#include "state.h"
#include "../characters/character.h"

// Sort characters by decreasing speed
bool sortSpeedDecreasing(Character x, Character y) {
	return x.stats.speed > y.stats.speed;
}

// Check if a selected player is in a selected team
// (and compare them by ID)
bool Battle::isInTeam(std::vector<Character> team, Character character) {
	bool in_team = false;
	std::for_each(team.begin(), team.end(), [&in_team, &character](Character curr_char) mutable {
		if (curr_char.character_id == character.character_id) {
			in_team = true;
		}
	});

	return in_team;
}

// Check if the entire selected team is alive
bool Battle::isTeamAlive(std::vector<Character> team) {
	bool alive = false;

	std::for_each(team.begin(), team.end(), [&alive](Character character) mutable {
		if (character.is_alive()) {
			alive = true;
		}});

	return alive;
}

// Battle State Machine constructor -- set the player and enemy team
Battle::Battle(std::vector<Character> players, std::vector<Character> enemies) {
	player_team = players;
	enemy_team = enemies;
}

// Handle input from the player 
void Battle::handleInput(Character player) {
	std::string input;
	AttackMenu atkmenu;
	Character selected_enemy;

	// Get input from the player
	std::cout << "What would you like to do?\t";
	std::cin >> input;

	// Parse input
	if (input == "attack") {
		// If the player wants to attack, then enter the 
		// Attack Menu State Machine
		std::for_each(player.attacks.begin(), player.attacks.end(), 
		[&atkmenu, &player, this](Attack atk) mutable {
			atkmenu.enter(player, enemy_team);
			
			// Update the enemy team after doing damage and update 
			// character attack order (if speed was modified)
			enemy_team = atkmenu.selected_enemies;
			charorder = enemy_team;
			charorder.insert(charorder.end(), enemy_team.begin(), enemy_team.end());
		});
	} else if (input == "item") {
		// enter Item Menu State Machine
	} else if (input == "show") {
		// Show the current HP of all the enemies in the enemy team
		std::for_each(enemy_team.begin(), enemy_team.end(), [](Character enemy) {
			std::cout << enemy.name << "\t HP: " << enemy.stats.hp << "\n";
		});

		// Show the current HP of all the players in the player team
		std::for_each(player_team.begin(), player_team.end(), [](Character player) {
			std::cout  << player.name << "\t HP: " << player.stats.hp << "\n";
		});

		// Keep it in the player's turn
		handleInput(player);
	} // more else ifs 
	else {
		// if invalid input, keep it in the player's turn
		handleInput(player);
	}
}

// Enter the Battle State Machine 
void Battle::enter(Character player) {
	// Set the current turn order of all the teams and characters
	charorder = player_team;
	charorder.insert(charorder.end(), enemy_team.begin(), enemy_team.end());

	// Update the Battle State Machine
	Battle::update(player);
}

// Update the Battle State Machine
void Battle::update(Character player) {
	EnemyAI enemyai;

	// Update the current turn order, if it was ever changed 
	charorder = player_team;
	charorder.insert(charorder.end(), enemy_team.begin(), enemy_team.end());

	// sort here so at the beginning of each turn, speed rules are updated
	std::sort(charorder.begin(), charorder.end(), sortSpeedDecreasing);

	// first player goes first
	// does stuff, if alive
	// ai goes second
	// does stuff, if alive
	// if one team is dead, die and exit the Battle State Machined
	for (int i = 0; i < charorder.size(); i++) {
		if (isInTeam(player_team, charorder.at(i)) && charorder.at(i).is_alive()) {
			handleInput(player_team.at(i));
		} else if (charorder.at(i).stats.hp > 0) {
			enemyai.enter(charorder.at(i), player_team);

			player_team = enemyai.selected_players;
		} 
	}

	if (isTeamAlive(player_team) && isTeamAlive(enemy_team)) {
		Battle::update(player);
	} else {
		Battle::exit(1);
	}
}

void Battle::exit(int status) {
	// award exp to player and party
	// status, 0 = party died (game over), 1 = enemies died (success!)
	// call Character::level_up if exp = 100, and then roll over exp if > 100
	if (status == 1) {
		for (int i = 0; i < player_team.size(); i++) {
			if (player_team.at(i).is_alive() == 1) {
				for (int j = 0; j < enemy_team.size(); j++) {
					player_team.at(i).stats.exp += enemy_team.at(j).stats.exp;
				}

				if (player_team.at(i).stats.exp >= 100) {
					player_team.at(i).stats.exp = 0;
					player_team.at(i).level_up();
				}
			}
		}
	} else {
		std::cout << "Game over!\n"; 
	}
}