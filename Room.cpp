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
	std::cout << "Room constructor" << std::endl;
}

Room::~Room() {
    std::cout << "room delete lol" << std::endl;
}

void Room::setName(std::string name) {
	this->name = name;
    std::cout << "Set room name to: " << name << std::endl;
}

void Room::setDescription(std::string descrip) {
    this->description = description;
    std::cout << "Set room description to: " << descrip << std::endl;
}

void Room::setType(std::string type) {
    this->type = type;
    std::cout << "Set room type to: " << type << std::endl;
}

void Room::addItem(Item* anItem) {
    items[anItem->getName()] = anItem;
    std::string outStr = "Add item: " + anItem->getName() + " to room";
    std::cout << outStr << std::endl;
}

void Room::addContainer(Container* aContainer) {
    containers[aContainer->getName()] = aContainer;
    std::string outStr = "Add container: " + aContainer->getName() + " to room";
    std::cout << outStr << std::endl;
}

void Room::addCreature(Creature* aCreature) {
    creatures[aCreature->getName()] = aCreature;
    std::string outStr = "Add creature: " + aCreature->getName() + " to room";
    std::cout << outStr << std::endl;
}

void Room::addTrigger(Trigger aTrigger) {
    triggers[aTrigger.getCommand()] = aTrigger;
    std::string outStr = "Add trigger with command: " + aTrigger.getCommand() + " to room";
    std::cout << outStr << std::endl;
}

void Room::addBorder(std::string direction, Room* aRoom) {
    borders[direction] = aRoom;
    std::string outStr = "Add room: " + aRoom->getName() + " as " + direction + " border to room";
    std::cout << outStr << std::endl;
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

// std::unordered_map<std::string, Item*> getItems();
// std::unordered_map<std::string, Container*> getContainers();
// std::unordered_map<std::string, Creature*> getCreatures();
// std::unordered_map<std::string, Trigger*> getTriggers();
// std::unordered_map<std::string, Room*> getRooms();