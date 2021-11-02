#include <string>
#include <iostream>
#include <vector>
#include <unordered_map>
#include "Player.h"
#include "Room.h"
#include "Item.h"

Player::Player(Room* startRoom) {
    this->currRoom = startRoom;
}

// setters
void Player::setCurrRoom(Room* nextRoom) {
    this->currRoom = nextRoom;
}
void Player::addItem(Item* item) {
    inventory[item->getName()] = item;
}

// getters
std::string Player::getCurrRoom() {
    std::cout << "Current room: " << this->currRoom->getName() << std::endl;
}

std::unordered_map<std::string, Item*> Player::getInventory() {
    std::
}

std::string Player::printInventory() {

}