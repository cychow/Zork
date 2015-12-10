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
	std::cout << "--- Populating map ---" << std::endl;
	// Parse all objects in map
	for (tinyxml2::XMLElement * child = root->FirstChildElement(); child != NULL; child = child->NextSiblingElement()) {
		//std::cout << child->Name() << std::endl;
		if (!strcmp(child->Name(), "room")) {
			// Do room thing
			// zorkRoom room = new zorkRoom(child);
			std::cout << "-: Creating room " << std::endl;
			roomList.push_back(new zorkRoom(child));
		} else if (!strcmp(child->Name(), "item")) {
			// Do item thing
			std::cout << "-: Creating item " << std::endl;
			itemList.push_back(new zorkItem(child));
		} else if (!strcmp(child->Name(), "container")) {
			// Do container thing
		} else if (!strcmp(child->Name(), "creature")) {
			// Do creature thing
		} else {
			// something went wrong
			std::cerr << "ERROR:\tUnexpected node name: got '" << child->Name() << "'." << std::endl;
		}
		std::cout << "----------------------" << std::endl;
   }


}
