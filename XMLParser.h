#pragma once
#include <vector>
#include <string>
#include <unordered_map>
#include "Item.h"
#include "Container.h"
#include "Creature.h"
#include "Trigger.h"
#include "Room.h"
#include "Attack.h"
#include "Condition.h"
#include "Element.h"
#include "tinyxml.h"

// The way this class is set up, you could easily use static methods or non-class C functions.
// I choose to use functions in a class to use something familar
class XMLParser {
private:
	/**
	 * Parses a list of students from the given element
	 * Expects the passed element to be a Students element, containing zero or more Student elements
	 */
	std::unordered_map<std::string, Element*> parseMap(TiXmlElement* element);

	/**
	 * Parses a student from the given element
	 * Expects the passed element to be a Student element, containing a name attribute and zero or more child activities
	 */
	Element* parseRoom(TiXmlElement* element);
	Element* parseItem(TiXmlElement* element);
	Element* parseContainer(TiXmlElement* element);
	Element* parseCreature(TiXmlElement* element, Room *owner);
	Trigger parseTrigger(TiXmlElement* element, std::string ownerName);
	Condition parseCondition(TiXmlElement* element);
	Attack parseAttack(TiXmlElement* element);
	//std::string getTextFromNamedChild(TiXmlElement* element, std::string name);

public:
	/**
	 * Parses the given XML file as a list of students. The caller is responsible for freeing the memory associated with the students
	 * Note the return type does not have to be a vector, you can write a parsing method to return any object type you wish
	 */
	std::unordered_map<std::string, Element*> parseXML(std::string filename);
};

