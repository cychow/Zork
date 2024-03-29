/*
 * zorkObj.h
 *
 *  Created on: Dec 9, 2015
 *      Author: cchow
 */

#ifndef ZORKOBJ_H_
#define ZORKOBJ_H_

#ifndef STRING_H
#include <string>
#endif

#ifndef TINYXML2_H
#include "tinyxml2/tinyxml2.h"
#endif


#include "zorkTrigger.h"
class zorkObj {
public:
	std::string name;
	std::string description;
	std::string status;
	std::vector<zorkTrigger *> triggerList;
	zorkObj(tinyxml2::XMLElement * element);
	zorkObj();
};

#endif /* ZORKOBJ_H_ */
