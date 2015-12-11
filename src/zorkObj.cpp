/*
 * zorkObj.cpp
 *
 *  Created on: Dec 9, 2015
 *      Author: cchow
 */

#include "zorkObj.h"
#include "tinyxml2/tinyxml2.h"
#include <iostream>
#include <string>

zorkObj::zorkObj() {
	name = "";
	status = "";
	description = "";
}

zorkObj::zorkObj(tinyxml2::XMLElement * node) {
	// get name
	if (node->FirstChildElement("name") != NULL) {
		name = node->FirstChildElement("name")->GetText();
	} else {
		name = "";
	}
//	std::cout << "--: name: " << name << std::endl;
	// get status
	if (node->FirstChildElement("status") != NULL) {
		status = node->FirstChildElement("status")->GetText();
	} else {
		status = "none";
	}
//	std::cout << "--: status: '" << status << "'" << std::endl;
	// get description
	if (node->FirstChildElement("description") != NULL) {
		description = node->FirstChildElement("description")->GetText();
	} else {
		description = "none";
	}
//	std::cout << "--: description: '" << description << "'" << std::endl;

	for(tinyxml2::XMLElement * element = node->FirstChildElement("trigger"); element != NULL; element = element->NextSiblingElement("trigger")) {
		triggerList.push_back(new zorkTrigger(element));
	}

}

