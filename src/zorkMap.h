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
#include <map>
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
	std::vector<zorkObj *> objectList;
	std::map<std::string, zorkObj *> objectMap;
	std::vector<zorkRoom*> roomList;
	std::map<std::string,zorkRoom *> roomMap;
	std::vector<zorkItem *> itemList;
	std::map<std::string, zorkItem *> itemMap;
	std::vector<zorkContainer *> containerList;
	std::map< std::string, zorkContainer *> containerMap;
	std::vector<zorkCreature *> creatureList;
	std::map<std::string, zorkCreature *> creatureMap;
	zorkMap (tinyxml2::XMLDocument * mapDoc);
	zorkRoom * findRoom(std::string name);

};

#endif /* ZORKMAP_H_ */
