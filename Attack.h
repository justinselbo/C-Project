#pragma once
#include <string>
#include <iostream>
#include <vector>
#include <unordered_map>
#include "Condition.h"

class Attack {
private:
	std::string print;
    Condition condition;
    std::vector<std::string> actions;

public:
    // constructor
    Attack();

	// setters
	virtual void setPrint(std::string print);
    virtual void setCondition(Condition cond);
	virtual void addAction(std::string action);

	// getters
	virtual std::string getPrint();
    virtual Condition getCondition();
    virtual std::vector<std::string> getActions();
};