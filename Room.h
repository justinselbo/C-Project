#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include "Item.h"
#include "Container.h"
#include "Creature.h"
#include "Trigger.h"

class Room {
private:
	std::string name;
    std::string description;
    std::string type;
    std::unordered_map<std::string, Item*> items;
    std::unordered_map<std::string, Container*> containers;
    std::unordered_map<std::string, Creature*> creatures;
    std::unordered_map<std::string, Trigger> triggers;
    std::unordered_map<std::string, Room*> borders;

public:
	virtual ~Room();
    Room();

	virtual void setName(std::string name);
    virtual void setDescription(std::string descrip);
    virtual void setType(std::string type);
	virtual void addItem(Item* anItem);
    virtual void addContainer(Container* aContainer);
    virtual void addCreature(Creature* aCreature);
    virtual void addTrigger(Trigger aTrigger);
    virtual void addBorder(std::string direction, Room* aRoom);

    virtual void eraseItem(Item* itemDelete);

	virtual std::string getName();
    virtual std::string getDescription();
    virtual std::string getType();
    virtual std::unordered_map<std::string, Room*> getBorders();
    virtual std::unordered_map<std::string, Item*> getItems();
    std::unordered_map<std::string, Container*> getContainers();
    std::unordered_map<std::string, Creature*> getCreatures();
    std::unordered_map<std::string, Trigger*> getTriggers();
    // std::unordered_map<std::string, Room*> getRooms();
};
