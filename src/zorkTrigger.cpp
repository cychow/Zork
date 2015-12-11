/*
 * zorkTrigger.cpp
 *
 *  Created on: Dec 9, 2015
 *      Author: cchow
 */

#include "zorkTrigger.h"
#include "generator.h"

#include <string>
#include <iostream>
#include <vector>
#include "tinyxml2/tinyxml2.h"


zorkCondition::zorkCondition() {
	owner = "";
	has = "";
	status = "";
	object = "";
}


zorkCondition::zorkCondition(tinyxml2::XMLElement * element) {
	if (element->FirstChildElement("owner") != NULL) {
		owner = element->FirstChildElement("owner")->GetText();
	} else {
		owner = "";
	}
	if (element->FirstChildElement("has") != NULL) {
		has = element->FirstChildElement("has")->GetText();
	} else {
		has = "";
	}
	if (element->FirstChildElement("object") != NULL) {
		object = element->FirstChildElement("object")->GetText();
	} else {
		object = "";
		}
	if (element->FirstChildElement("status") != NULL) {
		status = element->FirstChildElement("status")->GetText();
	} else {
		status = "";
	}
//	std::cout << "---: condition: " << std::endl;
//	std::cout << "----: owner: " << owner << std::endl;
//	std::cout << "----: has: " << has << std::endl;
//	std::cout << "----: object: " << object << std::endl;
//	std::cout << "----: status: " << status << std::endl;
}



zorkTrigger::zorkTrigger(tinyxml2::XMLElement * element) {
	triggered = false;
	if (element->FirstChildElement("type") != NULL) {
		type = element->FirstChildElement("type")->GetText();
	} else {
		type = "";
	}
	if (element->FirstChildElement("command") != NULL) {
		command = element->FirstChildElement("command")->GetText();
	} else {
		command = "";
	}
//	std::cout << "--: trigger." << std::endl;
//	std::cout << "---: type: " << type << std::endl;
//	std::cout << "---: command: " << command << std::endl;

	generateList(element, printList, "print");
	generateList(element, actionList, "action");
	if (element->FirstChildElement("condition") != NULL) {
		conditions = new zorkCondition(element->FirstChildElement("condition"));
	} else {
		conditions = new zorkCondition();
	}
}

zorkTrigger::zorkTrigger() {
	triggered = false;
	type = "";
	command = "";
	conditions = new zorkCondition();
}
