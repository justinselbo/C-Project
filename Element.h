#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include "Item.h"
#include "Container.h"
#include "Creature.h"
#include "Trigger.h"
#include "Room.h"
#include "Attack.h"
#include "Condition.h"

class Element {
private:
    Item *item;
    Container *container;
    Creature *creature;
    Trigger *trigger;
    Room *room;
    Attack *attack;
    Condition *condition;

public:
    Element();
    virtual void setItem(Item *item);
    virtual void setContainer(Container *container);
    virtual void setCreature(Creature *creature);
    virtual void setTrigger(Trigger *trigger);
    virtual void setRoom(Room *room);
    virtual void setAttack(Attack *attack);
    virtual void setCondition(Condition *condition);

    virtual Item* getItem();
    virtual Container* getContainer();
    virtual Creature* getCreature();
    virtual Trigger* getTrigger();
    virtual Room* getRoom();
    virtual Attack* getAttack();
    virtual Condition* getCondition();
};
