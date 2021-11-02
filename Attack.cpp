#include <string>
#include <iostream>
#include <vector>
#include <unordered_map>
#include "Item.h"
#include "Condition.h"
#include "Attack.h"

Attack::Attack() {
    std::cout << "Attack constructor" << std::endl;
}

// setters
void Attack::setPrint(std::string print) {
    this->print = print;
    std::string outStr = "Set print for attack to: " + print;
    std::cout << outStr << std::endl; 
}

void Attack::setCondition(Condition cond) {
    condition = cond;
    std::cout << "Set condition for attack" << std::endl;
}

void Attack::addAction(std::string action) {
    actions.push_back(action);
    std::string outStr = "Added action: " + action + " to attack";
    std::cout << outStr << std::endl;
}

// getters
std::string Attack::getPrint() {
    return print;
}

Condition Attack::getCondition() {
    return condition;
}

std::vector<std::string> Attack::getActions() {
    return actions;
}