#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include "XMLParser.h"
#include "Element.h"
#include "Player.h"
#include "CommandHandler.h"

int main(int argc, char** args) {
	// prompt for XML file to parse
	std::string filename;
	// bool shouldPause = true;

	// if given a second argument, use that as the XML file
	// means calling "XMLParseDemo studentActivity.xml" will parse the file "studentActivity.xml". The Makefile is set up to supply this argument when using on command line
	if (argc >= 2) {
		filename = args[1];
		// shouldPause = false;
	}
	else {
		// if no argument, prompt for filename. This is the form used in running in Visual Studio
		std::cout << "Enter filename: ";
		std::cin >> filename;
		// remove the extra newline character from cin
		std::cin.get();
	}

	// call the parser to parse the XML
	XMLParser parser;
	std::unordered_map<std::string, Element*> gameMap = parser.parseXML(filename);

	std::cout << "-----Game Begin----" << std::endl;
	Player* player = new Player(gameMap["Entrance"]->getRoom());
	// std::cout << player->getCurrRoom()->getDescription() << std::endl;
	CommandHandler commandHandler;
	commandHandler.setTriggers(player, gameMap);

	bool gameEnd = false;
	std::string command;
	while(!gameEnd) {
		std::cout << "Input command: ";
		std::getline(std::cin, command);
		gameEnd = commandHandler.handleCommand(command, player, gameMap);
	}
	
	gameMap.clear();
	// if (shouldPause) std::cin.get();

	return 0;
}