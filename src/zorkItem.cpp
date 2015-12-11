/*
 * zorkItem.cpp
 *
 *  Created on: Dec 9, 2015
 *      Author: cchow
 */


#include <vector>
#include <string>
#include <iostream>
#include "zorkItem.h"
#include "tinyxml2/tinyxml2.h"

zorkItem::zorkItem(tinyxml2::XMLElement * element) : zorkObj(element) {
	if (element->FirstChildElement("writing") != NULL) {
		writing = element->FirstChildElement("writing")->GetText();
	} else {
		writing = "";
	}

//	std::cout << "--: writing: " << writing << std::endl;
	if (element->FirstChildElement("turnon") != NULL) {
		turnon = new zorkTurnOn(element->FirstChildElement("turnon"));
	} else {
		turnon = NULL;
	}


}

zorkTurnOn::zorkTurnOn(tinyxml2::XMLElement * element) {
//	std::cout << "--: turnon" << std::endl;
	if (element->FirstChildElement("action") != NULL) {
		action = element->FirstChildElement("action")->GetText();
	} else {
		action = "";
	}
//	std::cout << "---: action: " << action << std::endl;
	if (element->FirstChildElement("print") != NULL) {
		print = element->FirstChildElement("print")->GetText();
	} else {
		print = "";
	}
//	std::cout << "---: print: " << print << std::endl;
}
