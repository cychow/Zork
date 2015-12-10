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

class zorkTrigger {
public:
	std::string type;
	std::vector<string> print;
	std::string command;
	std::vector<string> action;


};

#endif /* ZORKTRIGGER_H_ */
