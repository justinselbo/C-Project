#include <string>
#include <iostream>
#include <vector>
#include <unordered_map>
#include "Creature.h"
#include "Trigger.h"
#include "Attack.h"
#include "Room.h"

// constructors
Creature::Creature() {
    // std::cout << "Creature constructor" << std::endl;
}

// setters
void Creature::setName(std::string name) {
    this->name = name;
    // std::string outStr = "Creature name set to " + name;
    // std::cout << outStr << std::endl;
}

void Creature::addVulner(std::string vulner) {
    vulners.push_back(vulner);
    // std::string outStr = "Added vulnerability: " + vulner + " to creature";
    // std::cout << outStr << std::endl;
}

void Creature::setAttack(Attack attack) {
    this->attack = attack;
    // std::string outStr = "Set attack for creature";
    // std::cout << outStr << std::endl;
}

void Creature::setTrigger(Trigger trigger) {
    this->trigger = trigger;
    // std::string outStr = "Set trigger for creature";
    // std::cout << outStr << std::endl;
}

void Creature::setOwner(std::string owner) {
    this->ownerName = owner;
}

// getters
std::string Creature::getName() {
    return name;
}

std::vector<std::string> Creature::getVulners() {
    return vulners;
}

Attack Creature::getAttack() {
    return attack;
}

Trigger *Creature::getTrigger() {
    return &trigger;
}

std::string Creature::getOwner() {
    return ownerName;
}
