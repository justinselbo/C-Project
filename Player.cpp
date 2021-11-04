#include <string>
#include <iostream>
#include <vector>
#include <unordered_map>
#include "Player.h"
#include "Room.h"
#include "Item.h"

Player::Player(Room* startRoom) {
    this->currRoom = startRoom;
    std::cout << startRoom->getDescription() << std::endl;
}

// setters
void Player::setCurrRoom(Room* nextRoom) {
    this->currRoom = nextRoom;
}
void Player::addItem(Item* item) {
    inventory[item->getName()] = item;
}

// getters
Room* Player::getCurrRoom() {
    return currRoom;
}

std::unordered_map<std::string, Item*> Player::getInventory() {
    return inventory;
}

std::string Player::getInvStr() {
    std::string invStr = "";
    std::unordered_map<std::string, Item*>::iterator invIt = inventory.begin();
    while (invIt != inventory.end()) {
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