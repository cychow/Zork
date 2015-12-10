/*
 * zorkItem.h
 *
 *  Created on: Dec 9, 2015
 *      Author: cchow
 */

#include <vector>
#include <string>
#include "zorkObj.h"
#include "zorkTrigger.h"
#include "tinyxml2/tinyxml2.h"

#ifndef ZORKITEM_H_
#define ZORKITEM_H_

class zorkTurnOn {
public:
	std::string action;
	std::string print;
	zorkTurnOn(tinyxml2::XMLElement *);
};

class zorkItem : public zorkObj {
public:
	std::string writing;
	zorkTurnOn * turnon;
	std::vector<zorkTrigger *> triggerList;
	zorkItem(tinyxml2::XMLElement *);
};

#endif /* ZORKITEM_H_ */
