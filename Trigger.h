#pragma once
#include <string>
#include <iostream>
#include <vector>
#include <unordered_map>
#include "Condition.h"

class Trigger {
private:
	std::string type;
	std::string command;
	Condition condition;
	std::string print;
	std::vector<std::string> actions;
	std::string ownerName;

public:
	// constructor
	Trigger();

	// setters
	virtual void setType(std::string type);
	virtual void setCommand(std::string command);
	virtual void setCondition(Condition condition);
	virtual void setPrint(std::string print);
	virtual void addActions(std::string action);
	virtual void setOwnerName(std::string ownName);

	// getters
	virtual std::string getType();
	virtual std::string getCommand();
	virtual Condition *getCondition();
	virtual std::string getPrint();
	virtual std::vector<std::string> getActions();
	virtual std::string getOwnerName();
};
