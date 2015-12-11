/*
 * zorkRoom.cpp
 *
 *  Created on: Dec 9, 2015
 *      Author: cchow
 */

#include "zorkRoom.h"
#include "tinyxml2/tinyxml2.h"
#include "generator.h"
#include <string>
#include <vector>
#include <iostream>

zorkRoom::zorkRoom (tinyxml2::XMLElement * node) : zorkObj(node) {
	// create room
	visited = false;
	// get type
	if (node->FirstChildElement("type") != NULL) {
		type = node->FirstChildElement("type")->GetText();
	} else {
		type = "regular";
	}
	std::cout << "--: type: '" << type << "'" << std::endl;
	// iterate through the following:
	// border
	for(tinyxml2::XMLElement * element = node->FirstChildElement("border"); element != NULL; element = element->NextSiblingElement("border")) {
		border * newBorder = new border(element);
		borderList.push_back(newBorder);
		borderMap[newBorder->name] = newBorder;
		//instead of borderMap.insert(make_pair(newBorder->name,newBorder))
	}
	// iterate through containterList
	generateList(node, containerList, "container");
	// iterate through itemList
	generateList(node, itemList, "item");
//	for (auto iter = itemList.begin(); iter != itemList.end(); ++iter) {
//		std::cout << *iter << std::endl;
//	}
	// populate creature and triggerlist
	generateList(node, creatureList, "creature");



}

border::border(tinyxml2::XMLElement * node) {
	name = node->FirstChildElement("name")->GetText();
	direction = node->FirstChildElement("direction")->GetText();
	std::cout << "--: border: " << direction << " to " << name << std::endl;
}

void zorkRoom::printDescription(bool descriptive) {
	if (visited && !descriptive)  {
		std::cout << name << std::endl;
	} else {
		std::cout << description << std::endl;
		visited = true;
	}
}


