/*
 * zorkMap.cpp
 *
 *  Created on: Dec 9, 2015
 *      Author: cchow
 */

#include "zorkMap.h"
#include <iostream>

zorkMap::zorkMap(tinyxml2::XMLDocument * mapDoc) {

   tinyxml2::XMLElement * root = mapDoc->RootElement();
   if (strcmp(root->Name(),"map") != 0) {
	  std::cerr << "ERROR:\tUnexpected first node; expected 'map' got '" << root->Name() << "'." << std::endl;
   }

   // Parse all objects in map
   for (tinyxml2::XMLElement * child = root->FirstChildElement(); child != NULL; child = child->NextSiblingElement()) {
	   std::cout << child->Name() << std::endl;
   }

}
