/*
 * zorkRoom.h
 *
 *  Created on: Dec 9, 2015
 *      Author: cchow
 */

#include <vector>
#include <string>

#ifndef ZORKROOM_H_
#define ZORKROOM_H_
#include "tinyxml2/tinyxml2.h"
#include "zorkContainer.h"
#include "zorkItem.h"
#include "zorkCreature.h"
#include "zorkTrigger.h"

// Zork room header file
// Contents:
//  zorkRoom:
//  inherits from zorkObj
//  border
//

class border {
public:
	std::string direction;
	std::string name;
	border(tinyxml2::XMLElement *);
};


class zorkRoom: public zorkObj {
public:
	std::string type; // should init to regular
	std::vector<border *> borderList;
	std::vector<std::string> containerList;
	std::vector<std::string> itemList;
	std::vector<std::string> creatureList;
	bool visited;

	void printDescription(bool descriptive = false);
	zorkRoom(tinyxml2::XMLElement *);

};

#endif /* ZORKROOM_H_ */
