#include <string>
#include <vector>
#include <iostream>
#include <unordered_map>
#include "XMLParser.h"
#include "tinyxml.h"
#include "Element.h"

// for a couple of concepts in parsing, TinyXML converts an XML file into a tree structure containing nodes
// a node for our uses will either be an element node (for example, <Student>...</Student>) or a text node (the "Prof. Midkiff" in <name>Prof. Midkiff</name>)

// in parsing the XML file, there are a few cases where there are multiple methods to perform the same task, so I tried to show both ways in this code
// in those cases, there should be comments pointing to the other methods to perform the task, so choose whichever method you like the best

std::unordered_map<std::string, Element*> gameMap;

std::string getTextFromNamedChild(TiXmlElement* element, std::string name) {
	TiXmlElement* child = element->FirstChildElement(name);
	if (child != NULL) {
		// we could use GetText instead of getting the child and calling ToText, but I wanted to show another method of parsing the child node
		TiXmlNode* grandchild = child->FirstChild();
		if (grandchild != NULL) {
			// similar to ToElement, this returns null if the node is not a text node
			TiXmlText* text = grandchild->ToText();
			if (text != NULL) {
				return text->ValueStr();
			}
		}
	}
	return "";
}

Element* XMLParser::parseItem(TiXmlElement* element) {
	// there are two different ways to parse the values contained in nested elements
	// this function iterates all the elements child nodes nodes, and if an element matches one of the expected names then set the cooresponding attribute
	// see parseClub for the other method
	Element* itemElem;
	Item* item;
	std::string itemName;
	if (element->FirstChildElement() != NULL) {
		itemName = getTextFromNamedChild(element, "name");
	}
	else {
		itemName = element->GetText();
	}

	if (gameMap.find(itemName) == gameMap.end()) {
		itemElem = new Element();
		item = new Item();
		itemElem->setItem(item);
		itemElem->getItem()->setName(itemName);
		gameMap[itemElem->getItem()->getName()] = itemElem;
		// std::cout << "Item " << itemElem->getItem()->getName() << " added to map\n" << std::endl;
	}
	else {
		itemElem = gameMap[itemName];
		item = itemElem->getItem();
	}

	for (TiXmlNode* node = element->IterateChildren(NULL); node != NULL; node = element->IterateChildren(node)) {
		TiXmlElement* childElement = node->ToElement();
		if (childElement != NULL) {
			// ValueStr gets the name of the element type
			std::string name = childElement->ValueStr();

			if (name == "writing") {
				itemElem->getItem()->setWriting(childElement->GetText());
			}
			else if (name == "status") {
				itemElem->getItem()->setStatus(childElement->GetText());
			}
			else if (name == "turnon") {
				itemElem->getItem()->setPrint(getTextFromNamedChild(childElement, "print"));
				itemElem->getItem()->setAction(getTextFromNamedChild(childElement, "action"));
			}
		}
	}

	return itemElem;
}

Element* XMLParser::parseContainer(TiXmlElement* element) {
	Element* contElem;
	Container* container;
	std::string contName;
	if (element->FirstChildElement() != NULL) {
		contName = getTextFromNamedChild(element, "name");
	}
	else {
		contName = element->GetText();
	}

	if (gameMap.find(contName) == gameMap.end()) {
		contElem = new Element();
		container = new Container();
		contElem->setContainer(container);
		contElem->getContainer()->setName(contName);
		gameMap[contElem->getContainer()->getName()] = contElem;
		// std::cout << "Container " << contElem->getContainer()->getName() << " added to map\n" << std::endl;
	}
	else {
		contElem = gameMap[contName];
		container = contElem->getContainer();
	}

	for (TiXmlNode* node = element->IterateChildren(NULL); node != NULL; node = element->IterateChildren(node)) {
		TiXmlElement* childElement = node->ToElement();
		if (childElement != NULL) {
			// ValueStr gets the name of the element type
			std::string name = childElement->ValueStr();
			// this method gets the text contained inside the node
			//std::string value = childElement->GetText();

			// need a condition for each attribute we want to parse. Any unknown attributes are ignored
			if (name == "status") {
				contElem->getContainer()->setStatus(childElement->GetText());
			}
			else if (name == "accept") {
				contElem->getContainer()->setAccept(childElement->GetText());
			}
			else if (name == "trigger") {
				Trigger trigger = parseTrigger(childElement);
				contElem->getContainer()->setTrigger(trigger);
			}
			else if (name == "item") {
				Element* itemElem = parseItem(childElement);
				if (itemElem != NULL) {
					contElem->getContainer()->addItem(itemElem->getItem());
				}
			}
		}
	}

	return contElem;
}

Element* XMLParser::parseCreature(TiXmlElement* element) {
	Element* creatElem;
	Creature* creature;
	std::string creatName;
	if (element->FirstChildElement() != NULL) {
		creatName = getTextFromNamedChild(element, "name");
	}
	else {
		creatName = element->GetText();
	}
	if (gameMap.find(creatName) == gameMap.end()) {
		creatElem = new Element();
		creature = new Creature();
		creatElem->setCreature(creature);
		creatElem->getCreature()->setName(creatName);
		gameMap[creatElem->getCreature()->getName()] = creatElem;
		// std::cout << "Creature " << creatElem->getCreature()->getName() << " added to map\n" << std::endl;
	}
	else {
		creatElem = gameMap[creatName];
		creature = creatElem->getCreature();
	}

	for (TiXmlNode* node = element->IterateChildren(NULL); node != NULL; node = element->IterateChildren(node)) {
		TiXmlElement* childElement = node->ToElement();
		if (childElement != NULL) {
			// ValueStr gets the name of the element type
			std::string name = childElement->ValueStr();
			// this method gets the text contained inside the node
			//std::string value = childElement->GetText();

			// need a condition for each attribute we want to parse. Any unknown attributes are ignored
			if (name == "vulnerability") {
				creatElem->getCreature()->addVulner(childElement->GetText());
			}
			else if (name == "attack") {
				Attack attack = parseAttack(childElement);
				creatElem->getCreature()->setAttack(attack);
			}
			else if (name == "trigger") {
				Trigger trigger = parseTrigger(childElement);
				creatElem->getCreature()->setTrigger(trigger);
			}
		}
	}

	return creatElem;
}

Trigger XMLParser::parseTrigger(TiXmlElement* element) {
	Trigger trigger;

	for (TiXmlNode* node = element->IterateChildren(NULL); node != NULL; node = element->IterateChildren(node)) {
		TiXmlElement* childElement = node->ToElement();
		if (childElement != NULL) {
			std::string name = childElement->ValueStr();

			if (name == "type") {
				trigger.setType(childElement->GetText());
			}
			else if (name == "command") {
				trigger.setCommand(childElement->GetText());
			}
			else if (name == "condition") {
				Condition condition = parseCondition(childElement);
				trigger.setCondition(condition);
			}
			else if (name == "print") {
				trigger.setPrint(childElement->GetText());
			}
		}
	}

	return trigger;
}

Condition XMLParser::parseCondition(TiXmlElement* element) {
	Condition condition;

	for (TiXmlNode* node = element->IterateChildren(NULL); node != NULL; node = element->IterateChildren(node)) {
		TiXmlElement* childElement = node->ToElement();
		if (childElement != NULL) {
			std::string name = childElement->ValueStr();

			if (name == "has") {
				condition.setHas(childElement->GetText());
			}
			else if (name == "objName") {
				condition.setObjName(childElement->GetText());
			}
			else if (name == "status") {
				condition.setStatus(childElement->GetText());
			}
			else if (name == "ownerName") {
				condition.setOwnerName(childElement->GetText());
			}
		}
	}

	return condition;
}

Attack XMLParser::parseAttack(TiXmlElement* element) {
	Attack attack;

	for (TiXmlNode* node = element->IterateChildren(NULL); node != NULL; node = element->IterateChildren(node)) {
		TiXmlElement* childElement = node->ToElement();
		if (childElement != NULL) {
			std::string name = childElement->ValueStr();

			if (name == "print") {
				attack.setPrint(childElement->GetText());
			}
			else if (name == "condition") {
				Condition condition = parseCondition(childElement);
				attack.setCondition(condition);
			}
			else if (name == "action") {
				attack.addAction(childElement->GetText());
			}
		}
	}

	return attack;
}

Element* XMLParser::parseRoom(TiXmlElement* element) {
	// fetch the name attribute as a string, if defined
	Element* roomElem;
	Room* room;
	
	std::string tempName = getTextFromNamedChild(element, "name");

	if (gameMap.find(tempName) == gameMap.end()) {
		roomElem = new Element();
		room = new Room();
		
		room->setName(tempName);
		room->setDescription(getTextFromNamedChild(element, "description"));
		roomElem->setRoom(room);
		gameMap[room->getName()] = roomElem;
		// std::cout << "Room " << room->getName() << " added to map\n" << std::endl;
	}
	else {
		roomElem = gameMap[tempName];
		room = roomElem->getRoom();
		roomElem->getRoom()->setDescription(getTextFromNamedChild(element, "description"));
	}

	for (TiXmlNode* node = element->IterateChildren(NULL); node != NULL; node = element->IterateChildren(node)) {
		// the ToElement function returns null if the node is not an element
		TiXmlElement* childElement = node->ToElement();
		if (childElement != NULL) {
			// if the element type is one we recognize, handle with the proper function
			// note with more if statements, we could parse multiple different child types, for instance we could include Address or Advisor as another element nested inside Student
			if (childElement->ValueStr() == "item") {
				// if we successfully parse an activity, add it to the student
				Element* itemElem = parseItem(childElement);
				if (itemElem != NULL) {
					roomElem->getRoom()->addItem(itemElem->getItem());
				}
			}
			else if (childElement->ValueStr() == "trigger") {
				Trigger trigger = parseTrigger(childElement);
				roomElem->getRoom()->addTrigger(trigger);
			}
			else if (childElement->ValueStr() == "border") {
				if (gameMap.find(getTextFromNamedChild(childElement, "name")) == gameMap.end()) {
					Element* bordRoomElem = new Element();
					Room* borderRoom = new Room();
					borderRoom->setName(getTextFromNamedChild(childElement, "name"));
					bordRoomElem->setRoom(borderRoom);
					roomElem->getRoom()->addBorder(getTextFromNamedChild(childElement, "direction"), borderRoom);
					gameMap[bordRoomElem->getRoom()->getName()] = bordRoomElem;
					// std::cout << "Room " << bordRoomElem->getRoom()->getName() << " added to map\n" << std::endl;
				}
				else {
					Room* borderRoom = gameMap[getTextFromNamedChild(childElement, "name")]->getRoom();
					roomElem->getRoom()->addBorder(getTextFromNamedChild(childElement, "direction"), borderRoom);
				}
			}
			else if (childElement->ValueStr() == "container") {
				Element* contElem = parseContainer(childElement);
				if (contElem != NULL) {
					roomElem->getRoom()->addContainer(contElem->getContainer());
				}
			}
			else if (childElement->ValueStr() == "creature") {
				Element *creatElem = parseCreature(childElement);
				roomElem->getRoom()->addCreature(creatElem->getCreature());
			}
			else if (childElement->ValueStr() == "type") {
				roomElem->getRoom()->setType(childElement->GetText());
			}
		}
	}

	return roomElem;
}

std::unordered_map<std::string, Element*> XMLParser::parseMap(TiXmlElement* element) {
	// this method of iterating child nodes uses the IterateChildren method as recommended in the TinyXML docs. It is overall the most compact, but it requires a complex while loop condition
	// I would advise against using this unless you understand exactly what it is doing
	// parseCourse shows this same method written as a for loop which might help with understanding this method
	// alternatively, parseStudent shows a cleaner for loop approach using FirstChild and NextSibling to iterate a linked list of child nodes
	TiXmlNode* node = NULL;
	while ((node = element->IterateChildren(node)) != NULL) {
		// this function will cast the node if its a TiXmlElement, or returh NULL if it is not
		// there is also a ToText function to get a TiXmlText, which represents raw text inside an XML element
		TiXmlElement* childElement = node->ToElement();
		if (childElement->ValueStr() == "room") {
			parseRoom(childElement);
		}
		else if (childElement->ValueStr() == "item") {
			parseItem(childElement);
		}
		else if (childElement->ValueStr() == "container") {
			parseContainer(childElement);
		}
		else if (childElement->ValueStr() == "creature") {
			parseCreature(childElement);
		}
	}

	return gameMap;
}

/**
 * Parses the XML file for the given filename. Returns a vector of students if successful
 * If failed, prints an error and returns an empty vector
 */
std::unordered_map<std::string, Element*> XMLParser::parseXML(std::string filename) {
	// start parsing XML, we first need to create a TiXmlDocument and read it
	TiXmlDocument doc(filename);
	doc.LoadFile();

	// fetch the top level element, this should be the map
	TiXmlElement* rootElement = doc.RootElement();
	// null check handles the case where the filename is not a valid XML file
	// there may be a way to get more info (determine whether the file is missing or just contains invalid XML), but for the example this is good enough
	if (rootElement == NULL) {
		std::cerr << "Invalid XML file, contains no data" << std::endl;
		return std::unordered_map<std::string, Element*>();
	}
	// this validation is not strictly needed, but its can help avoid the problem of accidently using an XML file from the wrong source
	if (rootElement->ValueStr() != "map") {
		std::cerr << "Invalid XML file, should start with a map array" << std::endl;
		return std::unordered_map<std::string, Element*>();
	}
	// found the proper root element, so call the relevant parsing function
	parseMap(rootElement);

	return gameMap;
}
