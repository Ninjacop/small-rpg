// loop.cpp
// Teegan Lutze
#include "loop.h"

// Handle input in the GameLoop State Machine
void GameLoop::handleInput(std::string input) {
    std::vector<std::string> tokens;
    std::string token = ""; 
    size_t ws_pos;

    // tokenize input and store each token in the `tokens` vector
    for (int i = 0; i < input.size(); i++) {
        if (input[i] != ' ') {
            token.append(1, input[i]);
        } else {
            tokens.push_back(token);
            token = "";
        }
    }

    tokens.push_back(token);

    // Parse tokens
    if (tokens.at(0) == "show") {
        // Show the current location, people near you, as well as 
        // other locations you can travel to.
        std::cout << "Current location: " + this->curr_world.curr_loc.name + "\n";

        std::cout << "People near you: \n";
        std::for_each(this->curr_world.curr_loc.townfolk.begin(), 
                      this->curr_world.curr_loc.townfolk.end(), [](NPC person) {
                        std::cout << "\t" << person.name << std::endl;
        });

        std::cout << "\nOther locations: \n"; 
        std::for_each(this->curr_world.curr_loc.dirs.begin(), 
                      this->curr_world.curr_loc.dirs.end(), [](Location* loc) {
                        std::cout << "\t" << loc->name << std::endl;
        });
    } else if (tokens.at(0) == "talk" && !(tokens.at(1).empty())) {
        // Select one of the NPCs in a certain location,
        // and say their dialogue
        std::string uppername = tokens.at(1);
        int pos = 0;
        uppername[0] = toupper(uppername[0]);

        std::for_each(this->curr_world.curr_loc.townfolk.begin(), 
                      this->curr_world.curr_loc.townfolk.end(), [this, &uppername, &pos](NPC person) {
                        if (uppername == person.name && person.givenItem.name != "UNBOUND") {
                            person.say();
                            person.giveItem(&this->curr_world.party.at(0));
                        } else if (uppername == person.name) {
                            person.say();
                        }
                        pos++;
                    });  

        // a little bit hacky, change later
        this->curr_world.curr_loc.townfolk.at(pos - 1).has_given_item = true;      
    } else if (tokens.at(0) == "move" && !tokens.at(1).empty()) {
        // Select one of the locations and move to that location
        std::string uppername = tokens.at(1);
        uppername[0] = toupper(uppername[0]);

        std::for_each(this->curr_world.curr_loc.dirs.begin(), 
                      this->curr_world.curr_loc.dirs.end(), [this, &uppername](Location* loc) {
                        if (uppername == loc->name) {
                            this->curr_world.curr_loc = *loc;
                        }
        });
    } else if (tokens.at(0) == "inv") {
        InventoryMenu i;

        i.enter(this->curr_world.party.at(0));

        this->curr_world.party.at(0) = *i.selected;
    } else if (tokens.at(0) == "help") {
        // Show all the options the player can do
        std::cout << "show -> show current location, NPCs and other locations\n";
        std::cout << "talk [to a person] -> talk to a NPC in your location\n";
        std::cout << "move [to a location] -> move to a different location\n";
        std::cout << "inv -> view your inventory\n";
        std::cout << "q -> quit the game\n";
    } else if (tokens.at(0) == "q") {
        // Exit the GameLoop State Machine
        GameLoop::exit();
    }
}

// Enter the GameLoop State Machine
void GameLoop::enter(World w) {
    // Bind the current world to the GameLoop
    this->curr_world = w;

    // update the GameLoop StateMachine
    GameLoop::update();
}

// Update GameLoop State Machine
void GameLoop::update() {
    std::string input;

    // Get input from the player
    std::cout << "\n> ";
    std::getline(std::cin, input);

    // Handle input and the update the GameLoop State Machine
    handleInput(input);
    GameLoop::update();
}

// Exit the GameLoop State Machine
void GameLoop::exit() {
    // TODO find way to save game
    
    // Exit the game
    std::exit(0);
}