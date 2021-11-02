#include <string>
#include <iostream>
#include <vector>
#include <unordered_map>
#include "Item.h"

Item::Item() {
    std::cout << "Item constructor" << std::endl;
}
Item::Item(std::string name) : name(name) {
    std::cout << "Item constructor with name" << name << std::endl;
}

// setters
void Item::setName(std::string name) {
    this->name = name;
    std::string outStr = "Item name set to " + name;
    std::cout << outStr << std::endl;
}

void Item::setWriting(std::string writing) {
    this->writing = writing;
    std::string outStr = "Item writing set to " + writing;
    std::cout << outStr << std::endl;
}

void Item::setStatus(std::string status) {
    this->status = status;
    std::string outStr = "Item status set to " + status;
    std::cout << outStr << std::endl;
}

void Item::setPrint(std::string print) {
    this->turnOnPrint = print;
    std::string outStr = "Item turn on print set to " + print;
    std::cout << outStr << std::endl;
}

void Item::setAction(std::string action) {
    this->turnOnAction = action;
    std::string outStr = "Item turn on action set to " + action;
    std::cout << outStr << std::endl;
}

// getters
std::string Item::getName() {
    return name;
}
std::string Item::getWriting() {
    return writing;
}
std::string Item::getStatus() {
    return status;
}
std::string Item::getPrint() {
    return turnOnPrint;
}
std::string Item::getAction() {
    return turnOnAction;
}