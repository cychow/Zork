/*
 * gameState.h
 *
 *  Created on: Dec 10, 2015
 *      Author: cchow
 */

#ifndef GAMESTATE_H_
#define GAMESTATE_H_

#include "zorkMap.h"
#include "zorkItem.h"
#include <string>
#include <vector>

class gameState {
public:
	bool won;
	zorkMap * map;
	zorkRoom * currentRoom;
	zorkContainer * inventory;
};


#endif /* GAMESTATE_H_ */
