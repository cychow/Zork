// debug flag; comment to hide debug things

#ifndef VECTOR_H
#define VECTOR_H
#include <vector>
#endif

#ifndef TINYXML2_H
#define TINYXML2_H
#include "tinyxml2/tinyxml2.h"
#endif

#ifndef IOSTREAM_H
#define IOSTREAM_H
#include <iostream>
#endif

#include "zorkMap.h"
#include "zorkObj.h"
#include "gameState.h"

void parseCommand(zorkMap * map, gameState * gamestate, std::string lastCommand);

//using namespace std;
int main(int argc, char* argv[]) {
	// PARSE ALL THE THINGS
	tinyxml2::XMLDocument * mapDoc = new tinyxml2::XMLDocument();
	std::string filename;
	// load XML file
	if (argc !=2) {
		std::cout << "Loading default file: sample.txt.xml" << std::endl;
		filename = "./maps/sample.txt.xml";
	} else {
		std::cout << "Loading file: " << argv[1] << std::endl;
		filename = argv[1];
	}
	tinyxml2::XMLError errType = mapDoc->LoadFile(filename.c_str());
	if (errType != 0) {
		std::cerr << "ERROR:\tFailed to parse " << filename << "; error " << errType << ": ";
		std::cerr << mapDoc->ErrorName() << std::endl;
		//std::cerr << map.GetErrorStr2() << std::endl;
		return 1;
	} else {
		std::cout << "Successfully loaded " << filename << std::endl;
	}
	zorkMap::zorkMap * map = new zorkMap::zorkMap(mapDoc);
	// Game initialization
	std::cout << "Init game state..." << std::endl;
	gameState * state = new gameState();
	state->won = false;
	std::string lastCommand;
	// get first room
	state->currentRoom = map->findRoom("Entrance");
	// display the first room's description
	state->currentRoom->printDescription();
	while (!state->won) {
		std::getline(std::cin, lastCommand);
		parseCommand(map, state, lastCommand);
	}

	//delete(map);
	return 0;
}

void parseCommand(zorkMap * map, gameState * state, std::string lastCommand) {
	// Check for triggers
	std::cout << "Checking for triggers " << std::endl;
	for (auto trigger = state->currentRoom->triggerList.begin(); trigger != state->currentRoom->triggerList.end(); ++trigger) {
		// IF the trigger is not triggered and is of type single, or if the trigger is permanent
		if ((!((*trigger)->triggered) && !((*trigger)->type).compare("single")) || !((*trigger)->type).compare("permanent")) {
			bool doTrigger = false;
			//check if it's an object/status trigger
			if (!(*trigger)->conditions->object.empty() && !(*trigger)->conditions->status.empty()) {
				zorkObj * objectOfInterest = NULL;
				for (auto iter = map->objectList.begin(); iter != map->objectList.end(); ++iter) {
					if (!(*iter)->name.compare((*trigger)->conditions->object)) {
						objectOfInterest = *iter;
						break;
					}
				}
				if (objectOfInterest != NULL) {
					// if object has the status given by trigger, do something
					if(!objectOfInterest->status.compare((*trigger)->conditions->status)) {
						doTrigger = true;
					}
				}

			}
			//or if it's an object/has/owner trigger
			if (!(*trigger)->conditions->object.empty() && !(*trigger)->conditions->has.empty() && !(*trigger)->conditions->owner.empty()) {
				std::string targetObject = (*trigger)->conditions->object;
				std::string targetOwner = (*trigger)->conditions->owner;
				std::string targetHas = (*trigger)->conditions->has;
				std::cout << "Checking O-H-O Trigger: " << targetOwner << " (" << targetHas << ")has " << targetObject << std::endl;
				zorkObj * owner = NULL;
				bool isContainer = false;
				// look through containers to see if it has the item
				for (auto iter = map->containerList.begin(); iter != map->containerList.end(); ++iter) {
					if (!(*iter)->name.compare(targetOwner)) {
						owner = (zorkObj *)(*iter);
						isContainer = true;
						break;
					}
				}
				// now look through rooms to see if it has the item
				if (owner == NULL) {
					for (auto iter = map->roomList.begin(); iter != map->roomList.end(); ++iter) {
						if(!(*iter)->name.compare(targetOwner)) {
							owner = (zorkObj *)(*iter);
							break;
						}
					}
				}
				if (owner != NULL) {
					bool foundObj = false;
					std::cout << "Owner found: " << owner->name << std::endl;
					if (isContainer) {
						for (auto iter = ((zorkContainer *)owner)->itemList.begin(); iter != ((zorkContainer *)owner)->itemList.end(); ++iter) {
							if (!(*iter).compare(targetObject)) {
								foundObj = true;
							}
						}
					} else {
						for (auto iter = ((zorkRoom *)owner)->itemList.begin(); iter != ((zorkRoom *)owner)->itemList.end(); ++iter) {
							if (!(*iter).compare(targetObject)) {
								foundObj = true;
							}
						}
					}
					// if you've found the object and the trigger has is true OR if you haven't found the object and the trigger has is 'no'
					if ((foundObj && !targetHas.compare("yes")) || (!foundObj && !targetHas.compare("no"))) {
						doTrigger = true;
					}
				} else {
					std::cerr << "Something went wrong in the owner/has/object trigger; couldn't find owner '" << targetOwner << "'." << std::endl;
				}
			}
			if (!(lastCommand.compare((*trigger)->command)) && (doTrigger)) {
				//intercept the command by returning before you do things if it matches and conditions are met
				for (auto iter = (*trigger)->printList.begin(); iter != (*trigger)->printList.end(); ++iter) {
					std::cout << *iter << std::endl;
				}
				return;
			} else if (doTrigger && (*trigger)->command.empty()) {
				// do command and do trigger actions by falling through to parsing
				for (auto iter = (*trigger)->printList.begin(); iter != (*trigger)->printList.end(); ++iter) {
					std::cout << *iter << std::endl;
				}
			}
			// otherwise fall through and don't do the trigger
		}
	}


	//parse directional commands
	if (!lastCommand.compare("n") || !lastCommand.compare("s") || !lastCommand.compare("e") || !lastCommand.compare("w")) {
		std::string dirtoCompare = "";
		if (!lastCommand.compare("n")) {
			dirtoCompare = "north";
		} else if (!lastCommand.compare("s")) {
			dirtoCompare = "south";
		} else if (!lastCommand.compare("e")) {
			dirtoCompare = "east";
		} else if (!lastCommand.compare("w")) {
			dirtoCompare = "west";
		}
		for (auto direction = state->currentRoom->borderList.begin(); direction != state->currentRoom->borderList.end(); ++direction) {
			if(!(*direction)->direction.compare(dirtoCompare)) {
				// go to the northern room
				state->currentRoom = map->findRoom((*direction)->name);
				state->currentRoom->printDescription();
				return;
			}
		}
		std::cout << "Can't go that way." << std::endl;
		return;
	}

	std::cout << "Error" << std::endl;
}
