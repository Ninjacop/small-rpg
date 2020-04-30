// menu.cpp
// Teegan Lutze
#include "state.h"
#include "../characters/character.h"

// Handle input in the Attack Menu State Machine
void AttackMenu::handleInput() {
  std::vector<Attack> atks;
  std::string input;

  // Choose an attack from all possible attacks
  std::cout << "Choose an attack: [ ";

    std::for_each(selected->attacks.begin(), selected->attacks.end(), [&atks, this](Attack atk) {
      atk.name[0] = tolower(atk.name[0]);

      std::cout << atk.name;

      if (selected->attacks.size() > 1) {
        std::cout << " | ";
      }

      atks.push_back(atk);
    });

    std::cout << " ]\t";
    std::cin >> input;

    // If its a valid attack, then use that attack
    for (int i = 0; i < selected->attacks.size(); i++) {
      if (input == selected->attacks.at(i).name) {
        selected_atk = &selected->attacks.at(i);
      }
    }
}

// Enter the Attack Menu State Machine, with the selected player and enemeis
void AttackMenu::enter(Character player, std::vector<Character> enemies)  {
  selected = &player;
  selected_enemies = enemies;
  
  // Update the Attack Menu State Machine
  AttackMenu::update();
}

// Update the Attack Menu State Machine
void AttackMenu::update() {
  // Handle input from the player, then select an enemy
  AttackMenu::handleInput();
  AttackMenu::select_enemy();
}

// Select an enemy to attack
void AttackMenu::select_enemy() {
  std::vector<std::string> enemy_names;
  std::vector<int> enemy_ids;
  std::string input;
  std::string lowername;
  
  // Choose an enemy
  std::cout << "Choose an enemy: \n";

  // Show all possible enemies to attack
  for (int i = 0; i < selected_enemies.size(); i++) { 
    lowername = selected_enemies.at(i).name;
    lowername[0] = tolower(lowername[0]);

    std::cout << lowername << " (" << i << ")\n";
    enemy_ids.push_back(i);
    enemy_names.push_back(lowername);
  }

  // Get input from the player
  std::cin >> input;

  // Check if the input was an enemy, then set it to the current enemy
  for (int i = 0; i < enemy_names.size(); i++) {
    if (input == enemy_names.at(i) || stoi(input, nullptr, 10) == enemy_ids.at(i)) {
      selected_enemy = &selected_enemies.at(i);
    }
  }

  // Exit the Attack Menu State Machine
  AttackMenu::exit();
}

// Exit the Attack Menu State Machine
void AttackMenu::exit() {
  int damage; 

  // Redo attack input if the enemy or attack was invalid
  if (selected_atk->type == ATTACK_UNBOUND) {
    std::cout << "Unknown attack! Please re-enter.\n";
    update();
  } else if (selected_enemy->type == ELEMENT_UNBOUND) {
    std::cout << "Unknown enemy! Please re-enter.\n";
    select_enemy();
  }

  // Calculate damage
	damage = selected->attack_with(*selected_atk, *selected_enemy);

	std::cout << "You did " << damage << " damage to the " << this->selected_enemy->name << "!\n";

  // Set the enemies HP to -= the damage, then update the enemy team as well
	for (int i = 0; i < selected_enemies.size(); i++)	{
		if (selected_enemy->character_id == selected_enemies.at(i).character_id) {
			selected_enemies.at(i).stats.hp -= damage;

      if (selected_enemies.at(i).stats.hp < 0) {
        selected_enemies.at(i).stats.hp = 0;
      } 

			selected_enemy = &selected_enemies.at(i);
		}
	}

  // Announce if the enemy died
	if (selected_enemy->is_alive() == 0) {
		std::cout << "The " << selected_enemy->name << " fell!\n";
	}
}

void InventoryMenu::handleInput() {
  std::string input;
  std::cout << "What would you like to do? [ equip | unequip ]\n";

  std::cin >> input;

  if (input == "equip") {
    // todo
  } else if (input == "unequip") {
    // todo
  } else {
    Inventory::handleInput();
  }

  InventoryMenu::exit();
}

void InventoryMenu::enter(Character player) {
  selected = &player;

  InventoryMenu::update();
}

void InventoryMenu::update() {
  std::for_each(selected->inv.begin(), selected->inv.end(), [](Item i) {
    std::cout << "\t" << i.name << std::endl;
  });

  handleInput();
}

void InventoryMenu::exit() {
  // TODO
}

/* HAVE YET TO IMPLEMENT ITEM MENU STATE MACHINE */

void ItemMenu::handleInput() {
  // TODO
}

void ItemMenu::enter(Character player) {
  selected = &player;
}

void ItemMenu::update() {
 // TODO
}

void ItemMenu::exit() {
  // TODO
}