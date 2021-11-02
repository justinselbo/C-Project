#pragma once
#include <string>
#include <iostream>
#include <vector>
#include <unordered_map>

class Condition {
private:
    std::string has;
    std::string objName;
    std::string status;
    std::string ownerName;

public:
    // constructor
    Condition();

	// setters
    virtual void setHas(std::string has);
    virtual void setObjName(std::string objName);
    virtual void setStatus(std::string status);
    virtual void setOwnerName(std::string ownerName);

	// getters
    virtual std::string getHas();
    virtual std::string getObjName();
    virtual std::string getStatus();
    virtual std::string getOwnerName();
};