#pragma once
#include <string>
#include <iostream>
#include <vector>
#include <unordered_map>
#include "Item.h"
#include "Container.h"
#include "Condition.h"
#include "Trigger.h"
#include "Attack.h"

class Container {
private:
	std::string name;
	std::string status;
	std::string accept;
	Trigger trigger;
	std::unordered_map<std::string, Item*> items;

public:
	// constructor
	Container();

	// setters
	virtual void setName(std::string name);
	virtual void setStatus(std::string status);
	virtual void setAccept(std::string accept);
	virtual void setTrigger(Trigger trigger);
	virtual void addItem(Item *item);
	virtual void eraseItem(Item *delItem);

	// getters
	virtual std::string getName();
	virtual std::string getStatus();
	virtual std::string getAccept();
	virtual Trigger getTrigger();
	virtual std::unordered_map<std::string, Item*> getItems();
};