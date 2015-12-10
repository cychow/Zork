/*
 * generator.h
 *
 *  Created on: Dec 10, 2015
 *      Author: cchow
 */

#ifndef GENERATOR_H_
#define GENERATOR_H_

static void generateList(tinyxml2::XMLElement * root, std::vector<std::string> &list, std::string elementName) {
	for(tinyxml2::XMLElement * element = root->FirstChildElement(elementName.c_str()); element != NULL; element = element->NextSiblingElement(elementName.c_str())) {
		std::cout << "--: " << elementName << ": " << element->GetText() << std::endl;
		list.push_back(element->GetText());
	}
}


#endif /* GENERATOR_H_ */
