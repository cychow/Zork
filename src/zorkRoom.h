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
	std::vector<border> borders;
	std::vector<zorkContainer> containers;
	std::vector<zorkItem> items;
	std::vector<zorkCreature> creatures;
	std::vector<zorkTrigger> triggers;
	zorkRoom(tinyxml2::XMLElement *);

};

#endif /* ZORKROOM_H_ */
