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
            openContainer(player, commandArr);
        }
        else if (commandArr[0] == "read") {
            readItem(player, commandArr[1]);
        }
        else if (commandArr[0] == "drop") {
            dropItem(player, commandArr, gameMap);
        }
        else if (commandArr[0] == "put" && commandArr[2] == "in") {
            put(player, commandArr[1], commandArr[3]);
        }
        else if (commandArr[0] == "turn" && commandArr[1] == "on") {
            turnOn(player, commandArr[2], gameMap);
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
        return;
    }
    
    for (std::pair<std::string, Container*> element : player->getCurrRoom()->getContainers()) {
        if (element.second->getStatus() == "open") {
            if (element.second->getItems().find(takeItemName) != element.second->getItems().end()) {
                Item *takeItem = element.second->getItems()[takeItemName];
                player->addItem(takeItem);
                element.second->eraseItem(takeItem);
                std::cout << "Item " << takeItemName << " added to inventory." << std::endl;
                return;
            }
        }
    }

    std::cout << "Item " << takeItemName << " not found." << std::endl;
}

void CommandHandler::dropItem(Player *player, std::string *commandArr, std::unordered_map<std::string, Element*> gameMap) {
    std::string dropItemName = commandArr[1];
    std::unordered_map<std::string, Item*> playerInventory = player->getInventory();
    if (playerInventory.find(dropItemName) != playerInventory.end()) {
        Item *dropItem = playerInventory[dropItemName];
        player->getCurrRoom()->addItem(dropItem);
        player->eraseItem(dropItem);
        std::cout << dropItemName << " dropped" << std::endl;
    } 
    else {
        std::cout << "Item " << dropItemName << " not found in player inventory." << std::endl;
    }
}

void CommandHandler::openContainer(Player *player, std::string *commandArr) {
    std::string contName = commandArr[1];
    if (player->getCurrRoom()->getContainers().find(contName) != player->getCurrRoom()->getContainers().end()) {
        Container *cont = player->getCurrRoom()->getContainers()[contName];

        cont -> setStatus ("open");

        std::unordered_map<std::string, Item*> contInventory = cont->getItems();

        std::string invStr = "";
        for (std::pair<std::string, Item*> element : contInventory) {
            if (invStr.length() != 0) {
                invStr = invStr + ", " + element.first;
            }
            else {
                invStr = invStr + element.first;
            }
        }
        if (invStr.length() == 0) {
            std::cout << contName << " is empty" << std::endl;
        }
        else {
            std::cout << contName << " contains " << invStr << std::endl;
        }
    }
    else {
        std::cout << "Container " << contName << " not found in room." << std::endl;
    }
}

bool CommandHandler::isInInventory(Player *player, std::string itemName) {
    std::unordered_map<std::string, Item*> playerInventory = player->getInventory();
    if (playerInventory.find(itemName) != playerInventory.end()) {
        return true;
    }
    else {
        return false;
    }
}

bool CommandHandler::contInRoom(Player *player, std::string contName) {
    std::unordered_map<std::string, Container*> containers = player->getCurrRoom()->getContainers();
    if (containers.find(contName) != containers.end()) {
        return true;
    }
    else {
        return false;
    }
}

void CommandHandler::readItem(Player *player, std::string itemName) {
    if (isInInventory(player, itemName)) {
        Item *item = player->getInventory()[itemName];
        if (item->getWriting().length() != 0) {
            std::cout << item->getWriting().length() << std::endl;
        }
        else {
            std::cout << "Nothing written" << std::endl;
        }
    }
    else {
        std::cout << itemName << " not in inventory" << std::endl;
    }
}

void CommandHandler::put(Player *player, std::string itemName, std::string contName) {
    if (!isInInventory(player, itemName)) {
        std::cout << itemName << " not in inventory." << std::endl;
    }
    if (!contInRoom(player, contName)) {
        std::cout << contName << " not in current room." << std::endl;
    }
    if (player->getCurrRoom()->getContainers()[contName]->getStatus() != "open") {
        std::cout << "Cannot add " << itemName << " to closed container" << std::endl;
    }

    Container *cont = player->getCurrRoom()->getContainers()[contName];
    Item *item = player->getInventory()[itemName];

    cont->addItem(item);
    player->eraseItem(item);
    std::cout << "Item " << itemName << " added to " << contName << std::endl;
}

void CommandHandler::turnOn(Player *player, std::string itemName, std::unordered_map<std::string, Element*> gameMap) {
    if (!isInInventory(player, itemName)) {
        std::cout << itemName << " not in inventory" << std::endl;
    }

    Item *item = player->getCurrRoom()->getItems()[itemName];
    if (item->getPrint().length() == 0) {
        std::cout << "No action" << std::endl;
    }
    else {
        std::cout << item->getPrint() << std::endl;
        handleCommand(item->getAction(), player, gameMap);
    }
}
