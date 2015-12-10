/*
 * zorkMap.h
 *
 *  Created on: Dec 9, 2015
 *      Author: cchow
 */

#ifndef ZORKMAP_H_
#define ZORKMAP_H_

#include <vector>
#include <string>
#include "tinyxml2/tinyxml2.h"
#include "zorkObj.h"
#include "zorkRoom.h"
#include "zorkItem.h"
#include "zorkContainer.h"
#include "zorkCreature.h"
#include "zorkTrigger.h"
#include "zorkAttack.h"


// Main map class; contains all the rooms, items, containers, and creatures

class zorkMap {
public:
	// make a vector of rooms
	std::vector<zorkRoom*> roomList;
	std::vector<zorkItem *> itemList;
	std::vector<zorkContainer *> containerList;
	std::vector<zorkCreature *> creatureList;

	zorkMap (tinyxml2::XMLDocument * mapDoc);

};

#endif /* ZORKMAP_H_ */
