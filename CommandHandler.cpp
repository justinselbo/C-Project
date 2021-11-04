#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <unordered_map>
#include "Player.h"
#include "Room.h"
#include "Item.h"
#include "CommandHandler.h"

bool CommandHandler::handleCommand(std::string command, Player* player, std::unordered_map<std::string, Element*> gameMap) {
    if (command == "n" || command == "e" || command == "s" || command == "w") {
        std::string dir;
        if (command == "n") {
            dir = "north";
        }
        else if (command == "e") {
            dir = "east";
        }
        else if (command == "s") {
            dir = "south";
        }
        else if (command == "w") {
            dir = "west";
        }

        changeRoom(player, dir);
    }
    else if (command == "i") {
        printInventory(player);
    }
    else if (command == "open exit") {
        return openExit(player);
    }
    else {
        std::string *commandArr;
        commandArr = new std::string [4];
        int i = 0;
        std::istringstream myStream(command);
        std::string actionWord;
        while (myStream) {
            myStream >> actionWord;
            if (myStream) {
                commandArr[i] = actionWord;
                i++;
            }
            else {
                break;
            }
        }

        if (commandArr[0] == "take") {
            takeItem(player, commandArr);
        }
        else if (commandArr[0] == "open") {

        }
        else if (commandArr[0] == "read") {

        }
        else if (commandArr[0] == "drop") {
            dropItem(player, commandArr, gameMap);
        }
        else if (commandArr[0] == "put" && commandArr[2] == "in") {

        }
        else if (commandArr[0] == "turn" && commandArr[1] == "on") {

        }
        else if (commandArr[0] == "attack" && commandArr[2] == "with") {

        }

        delete[] commandArr;
    }
    return false;
}

void CommandHandler::changeRoom(Player* player, std::string dir) {
    Room *currRoom = player->getCurrRoom();
    std::unordered_map<std::string, Room*> borders = currRoom->getBorders();
    if (borders.find(dir) == borders.end()) {
        std::cout << "cannot move that way" << std::endl;
    }
    else {
        Room *nextRoom = currRoom->getBorders()[dir];
        player->setCurrRoom(nextRoom);
        std::cout << nextRoom->getDescription() << std::endl;
    }
}

void CommandHandler::printInventory(Player* player) {
    std::string invStr = player->getInvStr();
    if (invStr.length() == 0) {
        std::cout << "Inventory: empty" << std::endl;
    }
    else {
        std::cout << "Inventory: " << invStr << std::endl;
    }
}

bool CommandHandler::openExit(Player * player) {
    if (player->getCurrRoom()->getType() == "exit") {
        std::cout << "Game Over" << std::endl;
        return true;
    }
    else {
        std::cout << "Not an exit" << std::endl;
        return false;
    }
}

void CommandHandler::takeItem(Player * player, std::string *commandArr) {
    std::string takeItemName = commandArr[1];
    std::unordered_map<std::string, Item*> roomInventory = player->getCurrRoom()->getItems();
    if (roomInventory.find(takeItemName) != roomInventory.end()) {
        Item *takeItem = roomInventory[takeItemName];
        player->addItem(takeItem);
        player->getCurrRoom()->eraseItem(takeItem);
        std::cout << "Item " << takeItemName << " added to inventory." << std::endl;
    } 
    else {
        std::cout << "Item " << takeItemName << " not found in room." << std::endl;
    }
}

void CommandHandler::dropItem(Player *player, std::string *commandArr, std::unordered_map<std::string, Element*> gameMap) {
    std::string dropItemName = commandArr[1];
    std::unordered_map<std::string, Item*> playerInventory = player->getInventory();
    if (playerInventory.find(dropItemName) != playerInventory.end()) {
        Item *dropItem = playerInventory[dropItemName];
        player->getCurrRoom()->addItem(dropItem);
        playerInventory.erase(dropItemName);
        std::cout << dropItemName << " dropped" << std::endl;
    } 
    else {
        std::cout << "Item " << dropItemName << " not found in player inventory." << std::endl;
    }
}
