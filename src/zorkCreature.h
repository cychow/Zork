/*
 * zorkCreature.h
 *
 *  Created on: Dec 9, 2015
 *      Author: cchow
 */

#ifndef ZORKCREATURE_H_
#define ZORKCREATURE_H_

#include <vector>
#include <string>
#include <iostream>
#include "tinyxml2/tinyxml2.h"
#include "zorkObj.h"
#include "zorkAttack.h"

class zorkCreature : public zorkObj {
public:
	std::vector<std::string> vulnerabilityList;
	zorkAttack * attack;
	zorkCreature(tinyxml2::XMLElement * element);
};

#endif /* ZORKCREATURE_H_ */
