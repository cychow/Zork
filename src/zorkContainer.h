/*
 * zorkContainer.h
 *
 *  Created on: Dec 9, 2015
 *      Author: cchow
 */

#ifndef ZORKCONTAINER_H_
#define ZORKCONTAINER_H_

#include <vector>
#include <string>

#include "tinyxml2/tinyxml2.h"
#include "zorkObj.h"

class zorkContainer : public zorkObj {
public:
	bool isOpen;
	std::vector<std::string> acceptList;
	std::vector<std::string> itemList;
	zorkContainer(tinyxml2::XMLElement *);
	zorkContainer();
};

#endif /* ZORKCONTAINER_H_ */
