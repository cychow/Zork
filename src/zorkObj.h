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

class zorkObj {
public:
	std::string name;
	std::string description;
	std::string status;
	zorkObj(tinyxml2::XMLElement * element);
};

#endif /* ZORKOBJ_H_ */
