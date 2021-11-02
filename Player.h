#pragma once
#include <string>
#include <iostream>
#include <vector>
#include <unordered_map>
#include "Room.h"
#include "Item.h"

class Player {
private:
	Room* currRoom;
    std::unordered_map<std::string, Item*> inventory;
public:
	// constructors
	Player(Room* startRoom);

	// setters
	virtual void setCurrRoom(Room* nextRoom);
    virtual void addItem(Item* item);

	// getters
    virtual std::string getCurrRoom();
	virtual std::unordered_map<std::string, Item*> getInventory();
    virtual std::string printInventory();
};