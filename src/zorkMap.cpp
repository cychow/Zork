/*
 * zorkMap.cpp
 *
 *  Created on: Dec 9, 2015
 *      Author: cchow
 */

#include "zorkMap.h"
#include <iostream>

/*
#ifndef REGEX_H
#define REGEX_H
#include <regex>
#endif
*/

zorkMap::zorkMap(tinyxml2::XMLDocument * mapDoc) {

	tinyxml2::XMLElement * root = mapDoc->RootElement();
	if (strcmp(root->Name(),"map") != 0) {
		std::cerr << "ERROR:\tUnexpected first node; expected 'map' got '" << root->Name() << "'." << std::endl;
	}
//	std::cout << "--- Populating map ---" << std::endl;
	// Parse all objects in map
	// initialize inventory
	zorkContainer * inventory = new zorkContainer();
	inventory->name = "inventory";
	containerList.push_back(inventory);
	objectList.push_back((zorkObj*)inventory);
	for (tinyxml2::XMLElement * child = root->FirstChildElement(); child != NULL; child = child->NextSiblingElement()) {
		//std::cout << child->Name() << std::endl;
		if (!strcmp(child->Name(), "room")) {
			// Do room thing
			// zorkRoom room = new zorkRoom(child);
//			std::cout << "-: Creating room " << std::endl;
			auto room = new zorkRoom(child);
			roomMap.insert(std::make_pair(room->name,room));
			roomList.push_back(room);
			objectList.push_back((zorkObj*)room);
		} else if (!strcmp(child->Name(), "item")) {
			// Do item thing
//			std::cout << "-: Creating item " << std::endl;
			auto item = new zorkItem(child);
			itemMap.insert(std::make_pair(item->name,item));
			itemList.push_back(item);
			objectList.push_back((zorkObj*)item);
		} else if (!strcmp(child->Name(), "container")) {
			// Do container thing
//			std::cout << "-: Creating container " << std::endl;
			auto container = new zorkContainer(child);
			containerMap.insert(std::make_pair(container->name,container));
			containerList.push_back(container);
			objectList.push_back((zorkObj*)container);
		} else if (!strcmp(child->Name(), "creature")) {
			// Do creature thing
//			std::cout << "-: Creating creature " << std::endl;
			auto creature = new zorkCreature(child);
			creatureMap.insert(std::make_pair(creature->name,creature));
			creatureList.push_back(creature);
			objectList.push_back((zorkObj*)creature);
		} else {
			// something went wrong
			std::cerr << "ERROR:\tUnexpected node name: got '" << child->Name() << "'." << std::endl;
		}
//		std::cout << "----------------------" << std::endl;
		for (auto iter = objectList.begin(); iter != objectList.end(); ++iter) {
			objectMap.insert(std::make_pair((*iter)->name,(*iter)));
		}
   }


}

zorkRoom * zorkMap::findRoom(std::string name) {
	for (auto room = roomList.begin(); room != roomList.end(); ++room) {
		if (!(*room)->name.compare(name)) {
			return *room;
		}
	}
	return NULL;
}
