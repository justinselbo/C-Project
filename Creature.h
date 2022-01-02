#pragma once
#include <string>
#include <iostream>
#include <vector>
#include <unordered_map>
#include "Trigger.h"
#include "Attack.h"

class Creature {
private:
	std::string name;
	std::vector<std::string> vulners;
	Attack attack;
	Trigger trigger;
	std::string ownerName;

public:
	// constructors
	Creature();

	// setters
	virtual void setName(std::string name);
	virtual void addVulner(std::string vulner);
	virtual void setAttack(Attack attack);
	virtual void setTrigger(Trigger trigger);
	virtual void setOwner(std::string owner);

	// getters
	virtual std::string getName();
	virtual std::vector<std::string> getVulners();
	virtual Attack getAttack();
	virtual Trigger *getTrigger();
	virtual std::string getOwner();

};