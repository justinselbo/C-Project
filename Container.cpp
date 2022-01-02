#include <string>
#include <iostream>
#include <vector>
#include <unordered_map>
#include "Item.h"
#include "Container.h"
#include "Creature.h"
#include "Trigger.h"
#include "Condition.h"
#include "Attack.h"

Container::Container() {
    // std::cout << "Container constructor" << std::endl;
}

void Container::setName(std::string name) {
    this->name = name;
    // std::string outStr = "Set container name to " + name;
    // std::cout << outStr << std::endl;
}

void Container::setStatus(std::string status) {
    this->status = status;
    // std::string outStr = "Set container status to " + status;
    // std::cout << outStr << std::endl;
}

void Container::setAccept(std::string accept) {
    this->accept = accept;
    // std::string outStr = "Set container accept to " + accept;
    // std::cout << outStr << std::endl;
}

void Container::setTrigger(Trigger trigger) {
    this->trigger = trigger;
    // std::string outStr = "Set container trigger";
    // std::cout << outStr << std::endl;
}

void Container::addItem(Item *item) {
    items[item->getName()] = item;
    // std::string outStr = "Added item: " + item->getName() + " to container";
    // std::cout << outStr << std::endl;
}

void Container::eraseItem(Item *delItem) {
    if (items.find(delItem->getName()) != items.end()) {
        items.erase(delItem->getName());
    }
    else {
        std::cout << "Item not found in container: " << delItem->getName() << std::endl;
    }
}

// getters
std::string Container::getName() {
    return name;
}

std::string Container::getStatus() {
    return status;
}

std::string Container::getAccept() {
    return accept;
}

Trigger *Container::getTrigger() {
    return &trigger;
}

std::unordered_map<std::string, Item*> Container::getItems() {
    return items;
}

std::string Container::getInvStr() {
    std::string invStr = "";
    std::unordered_map<std::string, Item*>::iterator invIt = items.begin();
    while (invIt != items.end()) {
        if (invStr.length() != 0) {
            invStr = invStr + ", " + invIt->second->getName();
        }
        else {
            invStr = invStr + invIt->second->getName();
        }
        invIt++;
    }
    return invStr;
}
