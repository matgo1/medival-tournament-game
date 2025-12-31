#include "entities.h"
#include <iostream>
#include <random>
#include <fstream>
#include <vector>
#include <algorithm>
#include <memory>

const std::string FILENAME = "names.txt";

const std::string WELCOME_MESSAGE = "Hello! You are welcom on the tournament for the heart of the pincess!\n\
You need to win other 3 knights to win the tournamen. Good Luck!";

const std::string CONTROLS = "Choose your move: \n\
1. Attack by sword\n\
2. Defence by shield\n\
3. Through poison potion\n\
Your choose: ";

int craeateRandomNumber(int start, int end) {
    // Creation of random number
    std::random_device rd;
    std::mt19937 eng(rd());
    std::uniform_int_distribution<int> dist(start, end);
    return dist(eng);
}

std::string chooseRandomName() {
    // From the .txt file of names choose one
    std::vector<std::string> names; // Vector that will contain all names
    std::ifstream file(FILENAME);
    if(!file) {
        std::cerr << "There is no this file!" << std::endl;
    }
    
    std::string line; // Variable where we write lines
    while(std::getline(file, line)) {
        names.push_back(line); // Add each name in our vector
    }
    file.close();

    if (names.empty()) {
        std::cerr << "There was founed no names in the list" << std::endl;
    }

    return names[craeateRandomNumber(0, names.size() - 1)];
}

std::unique_ptr<Character> chooseHeroType(const std::string& name) {
    int type;
    // Player choose his type
    std::cout << "Choose your type!\n"
              << "1. Knight\n"
              << "2. Alchemist\n"
              << "Your choice: ";
    
    std::cin >> type;
    switch (type)
    {
    case (1):
        return std::make_unique<Knight>(name);
        break;
    
    case (2):
        return std::make_unique<Alchemist>(name);
        break;
    
    default:
        return std::make_unique<Knight>(name);
        break;
    }
}

bool startGame(Character& hero, Character& enemy) {
    std::string en_name = chooseRandomName();
    if (en_name.empty()) {
        std::cerr << "Name may not be empty" << std::endl;
        return 0;
    }
    
    // Set user health to 100
    hero.setHealth(100);

    while(true) {
        // User make his move
        int usr_choice;
        std::cout << CONTROLS;
        std::cin >> usr_choice;
        std::cout << "\n";

        // Bot make his choice
        int bot_choice = craeateRandomNumber(1, 3);

        // Reactions on user move
        switch (usr_choice) {
            case (1):
                if(bot_choice == 1 || bot_choice == 3) {
                    enemy.takeDamage(hero.hitSword());
                    std::cout << "You hitted " << enemy.getName() << " successfully!" << std::endl;
                } else {
                    std::cout << enemy.getName() << " blocked your attack" << std::endl;
                }
                break;
            
            case (2):
                break;
            
            case (3):
                enemy.takeDamage(hero.throughPotion());
                std::cout << enemy.getName() << " got poison in his face" << std::endl;
                break;

            default:
                std::cout << "There is no this choice in the list!" << std::endl;
                continue;
                break;
        }

        // Reaction on bot move
        switch (bot_choice) {
            case (1):
                if (usr_choice == 1 || usr_choice == 3) {
                    hero.takeDamage(enemy.hitSword());
                    std::cout << enemy.getName() << " has hitted you by his weapon" << std::endl;
                }
                break;
            
            case (2):
                break;

            case (3): 
                hero.takeDamage(enemy.throughPotion());
                std::cout << "You got potion in your head!" << std::endl;
                break;

            default:
                break;
        }
        
        // Show info about competitoes
        std::cout << "\n";
        hero.showInfo();
        std::cout << "\n";
        enemy.showInfo();
        std::cout << "\n";

        // If hero dead
        if (hero.getHealth() == 0) {
            std::cout << "You have lost!" << std::endl;
            return false; // Return lost
        }
        else if (enemy.getHealth() == 0) {
            std::cout << "You have won!!!" << std::endl;
            return true;
        } else continue;
    }
} 

int main() {
    std::string username;
    // Ask for user's name
    std::cout << "Choose your name (with 'Sir' in the start), stranger: ";
    std::getline(std::cin, username); // Name our hero by player's choice

    std::unique_ptr<Character> hero = chooseHeroType(username);

    unsigned short lives = 3;
    unsigned short wins = 0;

    while (true) {
        // Choose name for our enemy
        std::string en_name = chooseRandomName();
        if (en_name.empty()) {
            std::cerr << "Name may not be empty" << std::endl;
            return 1;
        }

        std::unique_ptr<Character> enemy = std::make_unique<Character>(en_name); // Object of our enemy

        // Check for result
        bool result = startGame(*hero, *enemy);
        if (result) {
            wins++;
        } else {
            lives -= 1;
        }

        if (wins == 3) {
            std::cout << "You have won princess heart!" << std::endl;
            break;
        } else if (lives == 0) {
            std::cout << "You have lost the tournament. Good luck next time" << std::endl;
            break;
        } else continue;
    }

    return 0;
}