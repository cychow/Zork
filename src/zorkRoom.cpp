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
	// create room woo
	std::string name = node->FirstChildElement("name")->GetText();
	std::cout << "-: Creating room '" << name << "'" << std::endl;

}
