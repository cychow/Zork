/*
 * zorkContainer.cpp
 *
 *  Created on: Dec 10, 2015
 *      Author: cchow
 */

#include "zorkContainer.h"
#include "tinyxml2/tinyxml2.h"
#include "generator.h"
#include <vector>
#include <string>
#include <iostream>



zorkContainer::zorkContainer(tinyxml2::XMLElement * element) : zorkObj(element) {
	generateList(element, itemList, "item");
	generateList(element, acceptList, "accept");
}

