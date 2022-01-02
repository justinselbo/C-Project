#include <string>
#include <iostream>
#include <vector>
#include <unordered_map>
#include "Item.h"
#include "Container.h"
#include "Creature.h"
#include "Trigger.h"
#include "Room.h"

Room::Room() {
	// std::cout << "Room constructor" << std::endl;
}

Room::~Room() {
    // std::cout << "room delete lol" << std::endl;
}

void Room::setName(std::string name) {
	this->name = name;
    // std::cout << "Set room name to: " << name << std::endl;
}

void Room::setDescription(std::string descrip) {
    this->description = descrip;
    // std::cout << "Set room description to: " << descrip << std::endl;
}

void Room::setType(std::string type_) {
    this->type = type_;
    // std::cout << "Set room type to: " << this->type << std::endl;
}

void Room::addItem(Item* anItem) {
    items[anItem->getName()] = anItem;
    // std::string outStr = "Add item: " + anItem->getName() + " to room";
    // std::cout << outStr << std::endl;
}

void Room::addContainer(Container* aContainer) {
    containers[aContainer->getName()] = aContainer;
    // std::string outStr = "Add container: " + aContainer->getName() + " to room";
    // std::cout << outStr << std::endl;
}

void Room::addCreature(Creature* aCreature) {
    creatures[aCreature->getName()] = aCreature;
    // std::string outStr = "Add creature: " + aCreature->getName() + " to room";
    // std::cout << outStr << std::endl;
}

void Room::addTrigger(Trigger aTrigger) {
    triggers[aTrigger.getCommand()] = aTrigger;
    // std::string outStr = "Add trigger with command: " + aTrigger.getCommand() + " to room";
    // std::cout << outStr << std::endl;
}

void Room::delTrigger(Trigger aTrigger) {
    if (triggers.find(aTrigger.getCommand()) != triggers.end()) {
        triggers.erase(aTrigger.getCommand());
    }
    else {
        std::cout << "Trigger not found for room: " << aTrigger.getCommand() << std::endl;
    }
}

void Room::addBorder(std::string direction, Room* aRoom) {
    borders[direction] = aRoom;
    // std::string outStr = "Add room: " + aRoom->getName() + " as " + direction + " border to room";
    // std::cout << outStr << std::endl;
}

void Room::eraseItem(Item* itemDelete) {
    if (items.find(itemDelete->getName()) != items.end()) {
        items.erase(itemDelete->getName());
    }
    else {
        std::cout << "Item not found in room: " << itemDelete->getName() << std::endl;
    }
}

void Room::eraseCreature(Creature *creatDelete) {
    if (creatures.find(creatDelete->getName()) != creatures.end()) {
        creatures.erase(creatDelete->getName());
    }
    else {
        std::cout << "Creature not found in room: " << creatDelete->getName() << std::endl;
    }
}

std::string Room::getName() {
    return name;
}

std::string Room::getDescription() {
    return description;
}

std::string Room::getType() {
    return type;
}

std::unordered_map<std::string, Room*> Room::getBorders() {
    return borders;
}

std::unordered_map<std::string, Item*> Room::getItems() {
    return items;
}

std::unordered_map<std::string, Container*> Room::getContainers() {
    return containers;
}
std::unordered_map<std::string, Creature*> Room::getCreatures() {
    return creatures;
}
std::unordered_map<std::string, Trigger> Room::getTriggers() {
    return triggers;
}
// std::unordered_map<std::string, Room*> Room::getRooms() {
//     get rooms;
// }