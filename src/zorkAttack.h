/*
 * zorkAttack.h
 *
 *  Created on: Dec 10, 2015
 *      Author: cchow
 */

#ifndef ZORKATTACK_H_
#define ZORKATTACK_H_

#include "zorkTrigger.h"
#include "tinyxml2/tinyxml2.h"

class zorkAttack : public zorkTrigger {
public:
	zorkAttack(tinyxml2::XMLElement * element);
};


#endif /* ZORKATTACK_H_ */
