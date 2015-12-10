/*
 * zorkRoom.cpp
 *
 *  Created on: Dec 9, 2015
 *      Author: cchow
 */

#include "zorkRoom.h"
#include "tinyxml2/tinyxml2.h"
#include <string>
#include <vector>
#include <iostream>

zorkRoom::zorkRoom (tinyxml2::XMLElement * node) {
	// create room
	// get name
	if (node->FirstChildElement("name") != NULL) {
		name = node->FirstChildElement("name")->GetText();
	} else {
		name = "unnamed";
	}
	std::cout << "-: Creating room '" << name << "'" << std::endl;
	// get status
	if (node->FirstChildElement("status") != NULL) {
		status = node->FirstChildElement("status")->GetText();
	} else {
		status = "none";
	}
	std::cout << "--: status: '" << status << "'" << std::endl;
	// get description
	if (node->FirstChildElement("description") != NULL) {
		description = node->FirstChildElement("description")->GetText();
	} else {
		description = "nondescript";
	}
	std::cout << "--: description: '" << description << "'" << std::endl;
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
		borderList.push_back(new border(element));
	}

}

border::border(tinyxml2::XMLElement * node) {
	name = node->FirstChildElement("name")->GetText();
	direction = node->FirstChildElement("direction")->GetText();
	std::cout << "--: border: " << direction << " to " << name << std::endl;
}
