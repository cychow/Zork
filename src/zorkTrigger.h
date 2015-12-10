/*
 * zorkTrigger.h
 *
 *  Created on: Dec 9, 2015
 *      Author: cchow
 */

#ifndef ZORKTRIGGER_H_
#define ZORKTRIGGER_H_

#include <string>
#include <iostream>
#include <vector>
#include "tinyxml2/tinyxml2.h"


class zorkCondition {
public:
	std::string owner;
	std::string has;
	std::string object;
	std::string status;
	zorkCondition(tinyxml2::XMLElement * element);
};


class zorkTrigger {
public:
	std::string type;
	std::vector<std::string> printList;
	std::string command;
	std::vector<std::string> actionList;
	bool triggered;
	zorkCondition * conditions;
	zorkTrigger(tinyxml2::XMLElement * element);
};
#endif /* ZORKTRIGGER_H_ */
