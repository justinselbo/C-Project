#include <string>
#include <iostream>
#include <vector>
#include <unordered_map>
#include "Trigger.h"
#include "Condition.h"

// constructor
Trigger::Trigger() {
    // std::cout << "Trigger constructor\n" << std::endl;
}

// setters
void Trigger::setType(std::string type) {
    this->type = type;
    // std::string outStr = "Set trigger type to " + type;
    // std::cout << outStr << std::endl; 
}

void Trigger::setCommand(std::string command) {
    this->command = command;
    // std::string outStr = "Set trigger command to " + command;
    // std::cout << outStr << std::endl;
}

void Trigger::setCondition(Condition condition) {
    this->condition = condition;
    // std::string outStr = "Set trigger condition";
    // std::cout << outStr << std::endl;
}

void Trigger::setPrint(std::string print) {
    this->print = print;
    // std::string outStr = "Set trigger print to " + print;
    // std::cout << outStr << std::endl;
}

// getters
std::string Trigger::getType() {
    return type;
}

std::string Trigger::getCommand() {
    return command;
}

Condition Trigger::getCondition() {
    return condition;
}

std::string Trigger::getPrint() {
    return print;
}
