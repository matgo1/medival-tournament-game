#ifndef ENTITIES_H
#define ENTITIES_H

#include <string>

class Character {
    private:
    int health_ = 100;
    std::string name_;

    public:
    // Constractor
    Character(const std::string& n);

    // Getter
    std::string getName() const;
    int getHealth() const;

    // Setter
    void setName(const std::string& name);
    void setHealth(int health);

    // Methods
    void showInfo() const;

    virtual int hitSword();

    virtual int throughPotion();

    virtual void takeDamage(int damage);

    virtual ~Character() = default;
};

// Make different classes of main hero
class Knight : public Character {
    public:
    Knight(const std::string& n) : Character(n) {}
};

class Alchemist : public Character {
    public:
    Alchemist(const std::string& n) : Character(n) {};

    // Methods to override
    int hitSword() override;
    int throughPotion() override;
};

#endif // ENTITIES_H