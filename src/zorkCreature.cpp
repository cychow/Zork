/*
 * zorkCreature.cpp
 *
 *  Created on: Dec 10, 2015
 *      Author: cchow
 */

#include "zorkCreature.h"
#include "zorkAttack.h"
#include "tinyxml2/tinyxml2.h"

zorkCreature::zorkCreature(tinyxml2::XMLElement * element) : zorkObj(element) {
	if (element->FirstChildElement("attack") != NULL) {
		attack = new zorkAttack(element->FirstChildElement("attack"));
	} else {
		attack = NULL;
	}
}
