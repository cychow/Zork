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
#include <sstream>
#endif

#include <algorithm>
#include <map>

#include "zorkMap.h"
#include "zorkObj.h"
#include "gameState.h"

void parseCommand(zorkMap * map, gameState * gamestate, std::string lastCommand);
bool checkTriggers(zorkMap * map, gameState * gamestate, std::string lastCommand, bool interceptCommands);

// list of commands
void doPut(zorkMap * map, gameState * gamestate, std::vector<std::string> * inputCommandList);
void doUpdate(zorkMap * map, gameState * state, std::vector<std::string> * inputCommandList);
void doDelete(zorkMap * map, gameState * state, std::vector<std::string> * inputCommandList);
void doAdd(zorkMap * map, gameState * state, std::vector<std::string> * inputCommandList);
void doAttack(zorkMap * map, gameState * state, std::vector<std::string> * inputCommandList);

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
	// store inventory pointer in gamestate
	//find inventory
	for(auto iter = map->containerList.begin(); iter != map->containerList.end(); ++iter) {
		if (!(*iter)->name.compare("inventory")) {
			state->inventory = *iter;
			break;
		}
	}

	state->currentRoom->printDescription();
	while (!state->won) {
		std::getline(std::cin, lastCommand);
		parseCommand(map, state, lastCommand);
		checkTriggers(map,state,"",true);
	}

	//delete(map);
	return 0;
}

void parseCommand(zorkMap * map, gameState * state, std::string lastCommand) {
	// if checktriggers doesn't intercept
	if (!checkTriggers(map, state, lastCommand, true)) {
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
					state->currentRoom->printDescription(true);
					checkTriggers(map,state,"",false);
					return;
				}
			}
			std::cout << "Can't go that way." << std::endl;
			return;
		}
		// do a take
		if (lastCommand.find("take") == 0) {
			if (lastCommand.erase(lastCommand.find_last_not_of(" \n\r\t")+1).length() == 4) {
				std::cout << "Take what?" << std::endl;
				return;
			} else {
				std::string itemToFind = lastCommand.substr(5);
				//std::cout << "Attempting to take " << itemToFind << std::endl;
				for(auto iter = state->currentRoom->itemList.begin(); iter != state->currentRoom->itemList.end(); ++iter) {
					if (!(*iter).compare(itemToFind)) {
						//found the item in the room
						// put item into inventory
						state->inventory->itemList.push_back(itemToFind);
						// remove item from room
						state->currentRoom->itemList.erase(iter);
						std::cout << "Item " << itemToFind << " added to inventory." << std::endl;
						return;
					}
				}
				// check containers in the room
				for(auto iterContainerString = state->currentRoom->containerList.begin(); iterContainerString != state->currentRoom->containerList.end(); ++iterContainerString) {
					auto iterContainer = map->containerMap.find((*iterContainerString));
					if((iterContainer != (map->containerMap.end()))) {
						//found the container
						for(auto iterItem = (*iterContainer).second->itemList.begin(); iterItem != (*iterContainer).second->itemList.end(); ++iterItem) {
							if (!(*iterItem).compare(itemToFind)) {
								// remove item from container
								if ((*iterContainer).second->isOpen) {
									//found the item
									state->inventory->itemList.push_back(itemToFind);
									(*iterContainer).second->itemList.erase(iterItem);
									std::cout << "Item " << itemToFind << " added to inventory." << std::endl;
									return;
								}
							}
						}
					}
				}
				std::cout << "You can't see a " << itemToFind << " here." << std::endl;
				return;
			}
		}
		// inventory
		if (!lastCommand.compare("i")) {
			bool firstItem = true;
			std::cout << "Inventory: ";
			if (state->inventory->itemList.size() == 0) {
				std::cout << "empty" << std::endl;
				return;
			}
			for (auto iter = state->inventory->itemList.begin(); iter != state->inventory->itemList.end(); ++iter) {
				if (!firstItem) {
					std::cout << ", ";
				}
				std::cout << (*iter);
				firstItem = false;
			}
			std::cout << std::endl;
			return;
		}
	// open
	if (lastCommand.find("open") == 0) {
		if (lastCommand.erase(lastCommand.find_last_not_of(" \n\r\t")+1).length() == 4) {
			std::cout << "Open what?" << std::endl;
			return;
		} else {
			std::string containertoOpen = lastCommand.substr(5);
			if (!containertoOpen.compare("exit")) {
				// you want to find the exit
				if (!state->currentRoom->type.compare("exit")) {
					std::cout << "Game Over" << std::endl;
					state->won = true;
					return;
				} else {
					std::cout << "There's no exit here!" << std::endl;
					return;
				}

				return;
			}
			if ((map->containerMap.count(containertoOpen)>0)  && (std::find(state->currentRoom->containerList.begin(), state->currentRoom->containerList.end(), containertoOpen) != state->currentRoom->containerList.end())) {
				auto targetContainer = (map->containerMap)[containertoOpen];
				std::cout << containertoOpen;
				targetContainer->isOpen = true;
				if (targetContainer->itemList.size() != 0) {
					bool first = true;
					for (auto iter = targetContainer->itemList.begin(); iter != targetContainer->itemList.end(); ++iter) {
						if (!first) {
							std::cout << ", ";
						} else {
							first = false;
							std::cout << " contains ";
						}
						std::cout << (*iter);
					}
					std::cout << "." << std::endl;
				} else {
					std::cout << " is empty." << std::endl;
				}
				return;
			} else {
				std::cout << "Can't find a " << containertoOpen << " to open." << std::endl;
				return;
			}
		}
	}

		// read command
		if (lastCommand.find("read") == 0) {
			if (lastCommand.erase(lastCommand.find_last_not_of(" \n\r\t")+1).length() == 4) {
				std::cout << "Read what?" << std::endl;
				return;
			} else {
				std::string itemToRead = lastCommand.substr(5);
				// read objects in inventory
				auto iter = std::find(state->inventory->itemList.begin(), state->inventory->itemList.end(), itemToRead);
				if (iter != state->inventory->itemList.end()) {
					//do whatever the fuck read
					if (map->itemMap[itemToRead]->writing.compare("")) {
						std::cout << map->itemMap[itemToRead]->writing << std::endl;
					} else {
						std::cout << "The " << itemToRead << " doesn't have writing on it." << std::endl;
					}
					return;
				} else {
					std::cout << "Error" << std::endl;
					return;
				}
			}
		}

		// turn on command
		if (lastCommand.find("turn on") == 0) {
			if (lastCommand.erase(lastCommand.find_last_not_of(" \n\r\t")+1).length() == 7) {
				std::cout << "Turn on what?" << std::endl;
				return;
			} else {
				std::string targetItem = lastCommand.substr(8);
				// read objects in inventory
				auto iter = std::find(state->inventory->itemList.begin(), state->inventory->itemList.end(), targetItem);
				if (iter != state->inventory->itemList.end()) {
					//do whatever the fuck turnon command
					std::cout << map->itemMap[targetItem]->turnon->print << std::endl;
					parseCommand(map, state, map->itemMap[targetItem]->turnon->action);
					return;
				} else {
					std::cout << "Error" << std::endl;
					return;
				}

			}
		}

		// do a drop
		if (lastCommand.find("drop") == 0) {
			if (lastCommand.erase(lastCommand.find_last_not_of(" \n\r\t")+1).length() == 4) {
				std::cout << "Drop what?" << std::endl;
				return;
			} else {
				std::string targetItem = lastCommand.substr(5);
				//find objects in inventory
				auto iter = std::find(state->inventory->itemList.begin(), state->inventory->itemList.end(), targetItem);
				if (iter != state->inventory->itemList.end()) {
					//found the item
					state->inventory->itemList.erase(iter);
					// put item from room
					state->currentRoom->itemList.push_back(targetItem);
					std::cout << targetItem << " dropped." << std::endl;
					return;
				} else {
					std::cout << "You don't have a " << targetItem << " to drop!" << std::endl;
					return;
				}
			}
		}
		//TODO make everything do this and parse commands
		std::vector<std::string> * inputCommandList = new std::vector<std::string>;
		std::istringstream f(lastCommand);
		std::string s;
		while (getline(f, s, ' '))	{
			inputCommandList->push_back(s);
		}
		if (!inputCommandList->at(0).compare("put")) {
			//std::cout << "running put command with '" << lastCommand << "'" << std::endl;
			doPut(map, state, inputCommandList);
			return;
		}
		if (!inputCommandList->at(0).compare("Update")) {
			//std::cout << "running Update command with '" << lastCommand << "'" << std::endl;
			doUpdate(map,state,inputCommandList);
			return;
		}
		if (!inputCommandList->at(0).compare("Delete")) {
			//std::cout << "running Delete command with '" << lastCommand << "'" << std::endl;
			doDelete(map,state,inputCommandList);
			return;
		}
		if (!inputCommandList->at(0).compare("Add")) {
			//std::cout << "running Add command with '" << lastCommand << "'" << std::endl;
			doAdd(map,state,inputCommandList);
			return;
		}
		if (!inputCommandList->at(0).compare("attack")) {
			doAttack(map,state,inputCommandList);
			return;
		}
		if (!lastCommand.compare("Game Over")) {
			state->won = true;
			std::cout << "Victory!" << std::endl;
			return;
		}
		std::cout << "Error parsing '" << lastCommand << "'" << std::endl;
	}
}

bool checkTriggers(zorkMap * map, gameState * state, std::string lastCommand, bool interceptCommands) {
	// Check for triggers
	bool intercepted = false;
	//std::cout << "Checking for triggers " << std::endl;
	// create list of every trigger in this room
	std::vector<zorkTrigger *> * allTriggers = new std::vector<zorkTrigger *>;
	for (auto trigger = state->currentRoom->triggerList.begin(); trigger != state->currentRoom->triggerList.end(); ++trigger) {
		allTriggers->push_back(*trigger);
	}
	// find triggers in every container in the room
	for (auto containerIter = state->currentRoom->containerList.begin(); containerIter != state->currentRoom->containerList.end(); ++containerIter) {
		// find triggers in every item in every container in the room
		auto currentContainer = map->containerMap[(*containerIter)];
		for (auto triggerIter = currentContainer->triggerList.begin(); triggerIter != currentContainer->triggerList.end(); ++triggerIter) {
			allTriggers->push_back(*triggerIter);
		}
		for (auto itemIter = currentContainer->itemList.begin(); itemIter != currentContainer->itemList.end(); ++itemIter) {
			auto currentItem = map->itemMap[(*itemIter)];
			for (auto triggerIter = currentItem->triggerList.begin(); triggerIter != currentItem->triggerList.end(); ++triggerIter) {
				allTriggers->push_back(*triggerIter);
			}
		}
	}
	// find triggers for every item loose in the room
	for (auto itemIter = state->currentRoom->itemList.begin(); itemIter != state->currentRoom->itemList.end(); ++itemIter) {
		auto currentItem = map->itemMap[(*itemIter)];
		for (auto triggerIter = currentItem->triggerList.begin(); triggerIter != currentItem->triggerList.end(); ++triggerIter) {
			allTriggers->push_back(*triggerIter);
		}
	}
	// find triggers for every creature in the room holy shit yay
	for (auto creatureIter = state->currentRoom->creatureList.begin(); creatureIter != state->currentRoom->creatureList.end(); ++creatureIter) {
		auto currentCreature = map->creatureMap[(*creatureIter)];
		for (auto triggerIter = currentCreature->triggerList.begin(); triggerIter != currentCreature->triggerList.end(); ++triggerIter) {
			allTriggers->push_back(*triggerIter);
		}
	}



	for (auto trigger = allTriggers->begin(); trigger != allTriggers->end(); ++trigger) {
		// IF the trigger is not triggered and is of type single, or if the trigger is permanent
		if ((!((*trigger)->triggered) && ((*trigger)->type).compare("permanent")) || !((*trigger)->type).compare("permanent")) {
			bool doTrigger = false;
			//check if it's an object/status trigger
			if (!(*trigger)->conditions->object.empty() && !(*trigger)->conditions->status.empty()) {
				std::string targetObj = (*trigger)->conditions->object;
				std::string targetStatus = (*trigger)->conditions->status;
				//std::cout << "Checking Obj/Status Trigger: " << targetObj << " | " << targetStatus << std::endl;
				if (map->objectMap.count(targetObj) > 0) {
					// found object
					//std::cout << "found " << targetObj << std::endl;
					auto objIter = map->objectMap[targetObj];
					if (!(objIter->status.compare(targetStatus))) {
						//std::cout << "^ this trigger is active ^" << std::endl;
						(*trigger)->triggered = true;
						doTrigger = true;
					} else {
						//std::cout << "^ this trigger is inactive ^ status is :" << objIter->status << " needs " << targetStatus << std::endl;
					}
				}
			}
			//or if it's an object/has/owner trigger
			if (!(*trigger)->conditions->object.empty() && !(*trigger)->conditions->has.empty() && !(*trigger)->conditions->owner.empty()) {
				std::string targetObject = (*trigger)->conditions->object;
				std::string targetOwner = (*trigger)->conditions->owner;
				std::string targetHas = (*trigger)->conditions->has;
				//std::cout << "Checking O-H-O Trigger: " << targetOwner << " (" << targetHas << ")has " << targetObject << std::endl;
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
					//std::cout << "Owner found: " << owner->name << std::endl;
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
						(*trigger)->triggered = true;
						doTrigger = true;
					}
				} else {
					std::cerr << "Something went wrong in the owner/has/object trigger; couldn't find owner '" << targetOwner << "'." << std::endl;
				}
			}
			if (!(*trigger)->command.empty() && (*trigger)->command.compare(lastCommand)) {
				//std::cout << (*trigger)->command << "|" << lastCommand << std::endl;
				continue;
			}
			if (!(lastCommand.compare((*trigger)->command)) && (doTrigger) && interceptCommands) {
				std::cout << "Intercepted command " << lastCommand << std::endl;
				//intercept the command by returning before you do things if it matches and conditions are met
				for (auto iter = (*trigger)->printList.begin(); iter != (*trigger)->printList.end(); ++iter) {
					std::cout << *iter << std::endl;
				}
				for (auto iter = (*trigger)->actionList.begin(); iter != (*trigger)->actionList.end(); ++iter) {
					parseCommand(map, state, (*iter));
					//std::cout << "CHECKING TRIGGERS AFTER ACTIVATING THIS COMMAND!" << std::endl;
					checkTriggers(map, state, "", false);
				}
				intercepted = true;
				continue;
			} else if (doTrigger && !interceptCommands && (lastCommand.compare((*trigger)->command))) {
				// do command and do trigger actions by falling through to parsing
				for (auto iter = (*trigger)->printList.begin(); iter != (*trigger)->printList.end(); ++iter) {
					std::cout << *iter << std::endl;
				}
				for (auto iter = (*trigger)->actionList.begin(); iter != (*trigger)->printList.end(); ++iter) {
					parseCommand(map, state, (*iter));
					//std::cout << "CHECKING TRIGGERS AFTER ACTIVATING THIS COMMAND!" << std::endl;
					checkTriggers(map, state, "", false);
				}
				continue;
			}
			// otherwise fall through and don't do the trigger
		}
	}
	return intercepted;
}
void doPut(zorkMap * map, gameState * state, std::vector<std::string> * inputCommandList) {
	if (inputCommandList->size() != 4) {
		std::cout << "Error" << std::endl;
		return;
	} else {
		// look for item in inventory
		auto iter = std::find(state->inventory->itemList.begin(), state->inventory->itemList.end(), inputCommandList->at(1));
		// if has inventory
		if (!(iter == state->inventory->itemList.end())) {
			//std::cout << "Found " << (*iter) << std::endl;
			auto iterContainer = std::find(state->currentRoom->containerList.begin(), state->currentRoom->containerList.end(), inputCommandList->at(3));
			if (!(iterContainer == state->currentRoom->containerList.end())) {
				//std::cout << "Found " << (*iterContainer) << std::endl;
				auto container = map->containerMap[inputCommandList->at(3)];
				// make sure you can put it in the container
				auto iterAcceptedItem = std::find((*container).acceptList.begin(), (*container).acceptList.end(), inputCommandList->at(1));
				if ((iterAcceptedItem != (*container).acceptList.end()) || ((*container).acceptList.size() == 0)) {
					state->inventory->itemList.erase(iter);
					(*container).itemList.push_back(inputCommandList->at(1));
					std::cout << "Item " << inputCommandList->at(1) << " added to " << inputCommandList->at(3) << "." << std::endl;
					return;
				} else {
					std::cout << "You can't put your " << inputCommandList->at(1) << " in the " << inputCommandList->at(3) << "." << std::endl;
					return;
				}
			} else {
				std::cout << "There isn't a " << inputCommandList->at(3) << " here." << std::endl;
			}
		} else {
			std::cout << "You don't have a " << inputCommandList->at(1) << "." << std::endl;
			return;
		}

	}
	return;
}

void doUpdate(zorkMap * map, gameState * state, std::vector<std::string> * inputCommandList) {
	if (inputCommandList->size() == 4) {
		if (map->objectMap.count(inputCommandList->at(1)) > 0) {
			map->objectMap[inputCommandList->at(1)]->status = inputCommandList->at(3);
			return;
		} else {
			std::cerr << "Can't find object " << inputCommandList->at(1) << std::endl;
		}
	} else {
		std::cerr << "Malformed Update command!" << std::endl;
		return;
	}
}

void doAdd(zorkMap * map, gameState * state, std::vector<std::string> * inputCommandList) {
	if (inputCommandList->size() == 4) {
		std::string targetObj = inputCommandList->at(1);
		std::string destObj = inputCommandList ->at(3);
		std::string destType = "none";
		if (map->objectMap.count(destObj) > 0) {
			if (map->containerMap.count(destObj) > 0) {
				destType = "container";
			} else if (map->roomMap.count(destObj) > 0) {
				destType = "room";
			} else {
				std::cerr << destObj << " isn't a room or a container!" << std::endl;
				return;
			}
		} else {
			std::cerr << "Couldn't find destination " << destObj << std::endl;
			return;
		}
		if (map->objectMap.count(targetObj) > 0) {
			//found the object

			// check if item
			if (map->itemMap.count(targetObj) > 0) {
				//is an item
				if (!destType.compare("container")) {
					// put it in the container
					map->containerMap[destObj]->itemList.push_back(targetObj);
					return;
				} else {
					map->roomMap[destObj]->itemList.push_back(targetObj);
					return;
				}
			}
			// check if container
			else if (map->containerMap.count(targetObj) > 0) {
				// is a container
				if (!destType.compare("room")) {
					map->roomMap[destObj]->containerList.push_back(targetObj);
					return;
				} else {
					std::cerr << "tried to put container " << targetObj << " in other container " << destObj << std::endl;
					return;
				}
			}
			// check if creature
			else if (map->creatureMap.count(targetObj) > 0) {
				if (!destType.compare("room")) {
					map->roomMap[destObj]->creatureList.push_back(targetObj);
					return;
				} else {
					std::cerr << "tried to put creature " << targetObj << " in container " << destObj << std::endl;
					return;
				}
			} else {
				std::cerr << targetObj << " isn't an item, container, or creature!" << std::endl;
				return;
			}
			return;
		} else {
			std::cerr << "Can't find object " << inputCommandList->at(1) << std::endl;
			return;
		}
	} else {
		std::cerr << "Malformed Add command!" << std::endl;
		return;
	}
}

void doDelete(zorkMap * map, gameState * state, std::vector<std::string> * inputCommandList) {
	if (inputCommandList->size() == 2) {
		std::string targetObj = inputCommandList->at(1);
		if (map->objectMap.count(targetObj) > 0) {
			//delete any border references
			for (auto roomIter = map->roomList.begin(); roomIter != map->roomList.end(); ++roomIter) {
				// delete any border references
				for (auto borderIter = (*roomIter)->borderList.begin(); borderIter != (*roomIter)->borderList.end(); ++borderIter) {
					if (!(*borderIter)->name.compare(targetObj)) {
						(*roomIter)->borderList.erase(borderIter);
						break;
					}
				}
				// delete any items in rooms
				for (auto itemIter = (*roomIter)->itemList.begin(); itemIter != (*roomIter)->itemList.end(); ++itemIter) {
					if (!(*itemIter).compare(targetObj)) {
						(*roomIter)->itemList.erase(itemIter);
						break;
					}
				}
				// delete any containers in rooms
				for (auto containerIter = (*roomIter)->containerList.begin(); containerIter != (*roomIter)->containerList.end(); ++containerIter) {
					if (!(*containerIter).compare(targetObj)) {
						(*roomIter)->containerList.erase(containerIter);
					}
				}
				// delete any items in containers
				for (auto containerIter = map->containerList.begin(); containerIter != map->containerList.end(); ++containerIter) {
					for (auto itemIter = (*containerIter)->itemList.begin(); itemIter != (*containerIter)->itemList.end(); ++itemIter) {
						if (!(*itemIter).compare(targetObj)) {
							(*containerIter)->itemList.erase(itemIter);
							break;
						}
					}
				}
				// delete any creatures in rooms
				for (auto creatureIter = (*roomIter)->creatureList.begin(); creatureIter != (*roomIter)->creatureList.end(); ++creatureIter) {
					if (!(*creatureIter).compare(targetObj)) {
						(*roomIter)->creatureList.erase(creatureIter);
						break;
					}
				}
			}
			return;
		} else {
			std::cerr << "Can't find object " << inputCommandList->at(1) << std::endl;
		}
	} else {
		std::cerr << "Malformed delete command!" << std::endl;
		return;
	}
}

void doAttack(zorkMap * map, gameState * state, std::vector<std::string> * inputCommandList) {
	if(inputCommandList->size() == 4) {
		std::string targetCreature = inputCommandList->at(1);
		std::string targetWeapon = inputCommandList->at(3);
		auto weaponIter = std::find(state->inventory->itemList.begin(), state->inventory->itemList.end(), targetWeapon);
		if (weaponIter == state->inventory->itemList.end()) {
			std::cout << "You don't have a " << targetWeapon << "." << std::endl;
			return;
		}
		auto creatureIter = std::find(state->currentRoom->creatureList.begin(), state->currentRoom->creatureList.end(), targetCreature);
		if (creatureIter != state->currentRoom->creatureList.end()) {
			zorkCreature * creature = map->creatureMap[targetCreature];
			// check for vulnerability -> you have weapon selected and something else
			auto vulnIter = std::find(creature->vulnerabilityList.begin(), creature->vulnerabilityList.end(), targetWeapon);
			if (vulnIter != creature->vulnerabilityList.end()) {
				//Check for conditions
				bool doAttack = false;
				if ((creature->attack->conditions->object.empty() || creature->attack->conditions->status.empty())) {
					doAttack = true;
				} else {
					//check for these conditions
					if (map->itemMap.count(creature->attack->conditions->object) > 0) {
						// check if status equals status
						if (!(map->itemMap[creature->attack->conditions->object]->status.compare(creature->attack->conditions->status))) {
							doAttack = true;
						} else {
							std::cout << "Your " << targetWeapon << " doesn't seem to be " << creature->attack->conditions->status << ". It's " <<
									map->itemMap[creature->attack->conditions->object]->status << std::endl;
							return;
						}
					} else {
						std::cerr << "Error: object " << creature->attack->conditions->object << " doesn't exist." << std::endl;
						return;
					}
				}
				if (doAttack) {
					std::cout << "You attack the " << targetCreature << " with your " << targetWeapon << "." << std::endl;
					for (auto iter = creature->attack->printList.begin(); iter != creature->attack->printList.end(); ++iter) {
						std::cout << *iter << std::endl;
					}
					for (auto iter = creature->attack->actionList.begin(); iter != creature->attack->actionList.end(); ++iter) {
						//std::cout << "Parsing " << (*iter) << std::endl;
						parseCommand(map, state, (*iter));
						//std::cout << "CHECKING TRIGGERS AFTER ACTIVATING THIS COMMAND!" << std::endl;
						//checkTriggers(map, state, "", false);
					}
					return;
				} else {
					return;
				}
			} else {
				std::cout << "Your " << targetWeapon << " doesn't seem to be effective on the " << targetCreature << "..." << std::endl;
			}
		} else {
			std::cout << "You don't see a " << targetCreature << " here." << std::endl;
			return;
		}
	} else {
		std::cout << "Error" << std::endl;
		return;
	}
	return;
}
