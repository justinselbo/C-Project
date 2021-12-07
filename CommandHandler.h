#pragma once
#include <string>
#include <iostream>
#include <vector>
#include <unordered_map>
#include "Room.h"
#include "Item.h"
#include "Player.h"
#include "Element.h"

class CommandHandler {
private:
	virtual bool isInInventory(Player *player, std::string itemName);
	virtual bool contInRoom(Player *player, std::string contName);
	virtual void changeRoom(Player *player, std::string dir);
	virtual void printInventory(Player *player);
	virtual bool openExit(Player *player);
	virtual void takeItem(Player *player, std::string *commandArr);
	virtual void dropItem(Player *player, std::string *commandArr, std::unordered_map<std::string, Element*> gameMap);
	virtual void openContainer(Player *player, std::string *commandArr);
	virtual void readItem(Player *player, std::string itemName);
	virtual void put(Player *player, std::string itemName, std::string contName);
	virtual void turnOn(Player *player, std::string itemName, std::unordered_map<std::string, Element*> gameMap);
public:
	virtual bool handleCommand(std::string command, Player* player, std::unordered_map<std::string, Element*> gameMap);
};