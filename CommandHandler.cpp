#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <any>
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
            bool isOver = attack(player, commandArr[1], commandArr[3], gameMap);
            delete[] commandArr;
            return isOver;
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

    std::cout << "Error: Item " << takeItemName << " not found." << std::endl;
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
        std::cout << "Error: Item " << dropItemName << " not found in player inventory." << std::endl;
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
        std::cout << "Error: " << contName << " not found in room." << std::endl;
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
            std::cout << item->getWriting() << std::endl;
        }
        else {
            std::cout << "Nothing written" << std::endl;
        }
    }
    else {
        std::cout << "Error: " << itemName << " not in inventory" << std::endl;
    }
}

void CommandHandler::put(Player *player, std::string itemName, std::string contName) {
    if (!isInInventory(player, itemName)) {
        std::cout << "Error: " << itemName << " not in inventory." << std::endl;
        return;
    }
    if (!contInRoom(player, contName)) {
        std::cout << "Error: " << contName << " not in current room." << std::endl;
        return;
    }
    if (player->getCurrRoom()->getContainers()[contName]->getStatus() != "open" && 
        player->getCurrRoom()->getContainers()[contName]->getAccept() != itemName) {
        std::cout << "Error: Cannot add " << itemName << " to closed container" << std::endl;
        return;
    }

    Container *cont = player->getCurrRoom()->getContainers()[contName];
    Item *item = player->getInventory()[itemName];

    cont->addItem(item);
    player->eraseItem(item);
    std::cout << "Item " << itemName << " added to " << contName << std::endl;
}

void CommandHandler::turnOn(Player *player, std::string itemName, std::unordered_map<std::string, Element*> gameMap) {
    if (!isInInventory(player, itemName)) {
        std::cout << "Error: " << itemName << " not in inventory" << std::endl;
        return;
    }

    Item *item = player->getInventory()[itemName];
    if (item->getPrint().length() == 0) {
        std::cout << "No action" << std::endl;
    }
    else {
        std::cout << item->getPrint() << std::endl;
        handleCommand(item->getAction(), player, gameMap);
    }
}

bool CommandHandler::creatInRoom(Player *player, std::string creatName) {
    std::unordered_map<std::string, Creature*> creatures = player->getCurrRoom()->getCreatures();
    if (creatures.find(creatName) != creatures.end()) {
        return true;
    }
    else {
        return false;
    }
}

bool CommandHandler::checkVulners(std::string itemName, Creature *creature) {
    // std::cout << "got here 2.1" << std::endl;
    if (std::find(creature->getVulners().begin(), creature->getVulners().end(), itemName) != creature->getVulners().end()) {
        // std::cout << "got here 2.2" << std::endl;
        return true;
    }
    else {
        return false;
    }
}

bool CommandHandler::attack(Player *player, std::string creatName, std::string itemName, std::unordered_map<std::string, Element*> gameMap) {
    if (creatInRoom(player, creatName)) {
        if (isInInventory(player, itemName)) {
            Creature *creature = player->getCurrRoom()->getCreatures()[creatName];
            // std::cout << "got here 1" << std::endl;
            if (checkVulners(itemName, creature)) {
                std::cout << "You assault the " << creatName << " with the " << itemName << std::endl;
                // std::cout << "got here 2" << std::endl;
                if (creature->getAttack().getPrint().length() != 0) {
                    // std::cout << "got here 4" << std::endl;
                    std::cout << creature->getAttack().getPrint() << std::endl;
                }

                for (std::string anAct : creature->getAttack().getActions()) {
                    // std::cout << "got here 3" << std::endl;
                    if(performAction(player, gameMap, anAct) == true) {
                        return true;
                    }
                }
            }
            else {
                std::cout << "Error: " << creatName << " not vulnerable to " << itemName << std::endl;
            }
        }
        else {
            std::cout << "Error: Item " << itemName << " is not in your inventory" << std::endl;
        }
    }
    else {
        std::cout << "Error: Creature " << creatName << " is not in the room" << std::endl;
    }
    return false;
}

bool CommandHandler::performAction(Player *player, std::unordered_map<std::string, Element*> gameMap, std::string action) {
    std::string *commandArr;
    commandArr = new std::string [4];
    int i = 0;
    std::istringstream myStream(action);
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

    if (commandArr[0] == "Add" && commandArr[2] == "to") {
        if (contInRoom(player, commandArr[3])) {
            Container *container = player->getCurrRoom()->getContainers()[commandArr[3]];
            if (gameMap.find(commandArr[1]) != gameMap.end()) {
                Element *thing = gameMap[commandArr[1]];
                if (thing->type == "Item") {
                    container->addItem(thing->getItem());
                }
                else if (thing->type == "Creature") {
                    std::cout << "WEIRD: Tried to add creature to container" << std::endl;
                }
            }
        }
        else {
            Room *room = gameMap[commandArr[3]]->getRoom();
            if (gameMap.find(commandArr[1]) != gameMap.end()) {
                Element *thing = gameMap[commandArr[1]];
                if (thing->type == "Item") {
                    room->addItem(thing->getItem());
                }
                if (thing->type == "Creature") {
                    room->addCreature(thing->getCreature());
                }
            }
        }
    }
    else if (commandArr[0] == "Delete") {
        Creature *creature = gameMap[commandArr[1]]->getCreature();
        gameMap[creature->getOwner()]->getRoom()->eraseCreature(creature);
    }
    else if (commandArr[1] == "Update" && commandArr[2] == "to") {
        if (gameMap.find(commandArr[1]) != gameMap.end()) {
            Element *thing = gameMap[commandArr[1]];
            if (thing->type == "Item") {
                thing->getItem()->setStatus(commandArr[3]);
            }
            if (thing->type == "Container") {
                thing->getContainer()->setStatus(commandArr[3]);
            }
        }
    }
    else if (commandArr[0] == "Game" && commandArr[1] == "Over") {
        std::cout << "Victory!" << std::endl;
        return true;
    }
    else {
        return handleCommand(action, player, gameMap);
    }

    return false;
}

// bool CommandHandler::inMap(std::unordered_map<std::string, std::any*> aMap, std::string thing) {
//     if (aMap.find(thing) != aMap.end()) {
//         return true;
//     }
//     else {
//         return false;
//     }
// }
