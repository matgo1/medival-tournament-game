#include "entities.h"
#include <iostream>

// Implementation of Character
// Constructor
Character::Character(const std::string& n) : name_(n) {
    std::cout << "Hello " << name_ << std::endl;
} 

// Getters
std::string Character::getName() const {
    return name_;
}

int Character::getHealth() const {
    return health_;
}

// Setters
void Character::setName(const std::string& name) {
    this->name_ = name;
}

void Character::setHealth(int health) {
    this->health_ = health;
}

// Methods
void Character::showInfo() const {
    std::cout << getName() << "\n"
    << "Health: " << getHealth() << std::endl;
}

int Character::hitSword() {
    return 25;
}

int Character::throughPotion() {
    return 15;
}

void Character::takeDamage(int damage) {
    setHealth(std::max(0, (getHealth() - damage)));
}

// Alchemic implementation
// Change sword damage for alc
int Alchemist::hitSword() {
    return 15;
}

// Make different potion damage for alc
int Alchemist::throughPotion() {
    return 20;
}