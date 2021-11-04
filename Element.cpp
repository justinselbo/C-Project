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
#include "Element.h"

Element::Element() {
    // std::cout << "New element created" << std::endl;
}

void Element::setItem(Item *item) {
    this->item = item;
    // std::cout << "Element set to item" << std::endl;
}

void Element::setContainer(Container *container) {
    this->container = container;
    // std::cout << "Element set to container" << std::endl;
}

void Element::setCreature(Creature *creature) {
    this->creature = creature;
    // std::cout << "Element set to creature" << std::endl;
}

void Element::setTrigger(Trigger *trigger) {
    this->trigger = trigger;
    // std::cout << "Element set to trigger" << std::endl;
}

void Element::setRoom(Room *room) {
    this->room = room;
    // std::cout << "Element set to room" << std::endl;
}

void Element::setAttack(Attack *attack) {
    this->attack = attack;
    // std::cout << "Element set to attack" << std::endl;
}

void Element::setCondition(Condition *condition) {
    this->condition = condition;
    // std::cout << "Element set to condition" << std::endl;
}

Item* Element::getItem() {
    return item;
}
Container* Element::getContainer() {
    return container;
}
Creature* Element::getCreature() {
    return creature;
}
Trigger* Element::getTrigger() {
    return trigger;
}
Room* Element::getRoom() {
    return room;
}
Attack* Element::getAttack() {
    return attack;
}
Condition* Element::getCondition() {
    return condition;
}