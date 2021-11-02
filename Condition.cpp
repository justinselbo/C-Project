#include <string>
#include <iostream>
#include <vector>
#include <unordered_map>
#include "Condition.h"

// constructor
Condition::Condition() {
    std::cout << "Condition constructor\n" << std::endl;
}

// setters
void Condition::setHas(std::string has) {
    this->has = has;
    std::string outStr = "Set condition has to " + has;
    std::cout << outStr << std::endl;
}

void Condition::setObjName(std::string objName) {
    this->objName = objName;
    std::string outStr = "Set condition object name to " + objName;
    std::cout << outStr << std::endl;    
}

void Condition::setStatus(std::string status) {
    this->status = status;
    std::string outStr = "Set condition status to " + status;
    std::cout << outStr << std::endl;
}
void Condition::setOwnerName(std::string ownerName) {
    this->ownerName = ownerName;
    std::string outStr = "Set owner name to " + ownerName;
    std::cout << outStr << std::endl;
}

// getters
std::string Condition::getHas() {
    return has;
}

std::string Condition::getObjName() {
    return objName;
}

std::string Condition::getStatus() {
    return status;
}

std::string Condition::getOwnerName() {
    return ownerName;
}
