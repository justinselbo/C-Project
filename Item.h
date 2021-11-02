#pragma once
#include <string>
#include <iostream>
#include <vector>
#include <unordered_map>

class Item {
private:
	std::string name;
	std::string writing;
	std::string status;
	std::string turnOnPrint;
	std::string turnOnAction;

public:
	// constructors
	Item();
	Item(std::string name);

	// setters
	virtual void setName(std::string name);
	virtual void setWriting(std::string writing);
	virtual void setStatus(std::string status);
	virtual void setPrint(std::string print);
	virtual void setAction(std::string action);

	// getters
	virtual std::string getName();
	virtual std::string getWriting();
	virtual std::string getStatus();
	virtual std::string getPrint();
	virtual std::string getAction();
	
};