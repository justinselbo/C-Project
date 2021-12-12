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
    this->type = "Item";
    // std::cout << "Element set to item" << std::endl;
}

void Element::setContainer(Container *container) {
    this->container = container;
    this->type = "Container";
    // std::cout << "Element set to container" << std::endl;
}

void Element::setCreature(Creature *creature) {
    this->creature = creature;
    this->type = "Creature";
    // std::cout << "Element set to creature" << std::endl;
}

void Element::setTrigger(Trigger *trigger) {
    this->trigger = trigger;
    this->type = "Trigger";
    // std::cout << "Element set to trigger" << std::endl;
}

void Element::setRoom(Room *room) {
    this->room = room;
    this->type = "Room";
    // std::cout << "Element set to room" << std::endl;
}

void Element::setAttack(Attack *attack) {
    this->attack = attack;
    this->type = "Attack";
    // std::cout << "Element set to attack" << std::endl;
}

void Element::setCondition(Condition *condition) {
    this->condition = condition;
    this->type = "Condition";
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