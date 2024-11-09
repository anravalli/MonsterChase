/*
 *	Monster Chase: a testing playground for behaviors trees
 *
 *	Copyright 2019 Andrea Ravalli <anravalli @ gmail.com>
 *
 *	This file is part of Monster Chase.
 *
 *	Monster Chase is free software: you can redistribute it and/or modify
 *	it under the terms of the GNU General Public License as published by
 *	the Free Software Foundation, either version 3 of the License, or
 *	(at your option) any later version.

 *	Monster Chase is distributed in the hope that it will be useful,
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *	GNU General Public License for more details.

 *	You should have received a copy of the GNU General Public License
 *	along with Monster Chase.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "behaviors.h"
#include <math.h>       /* cos */

Behavior::~Behavior(){

}

BehaviorStatus Sequence::exec() {
	BehaviorStatus status = success;
	for (auto c: childs){
		status = c->exec();
		if (fail == status)
			break;
	};
	return status;
}

void Sequence::addChild(Behavior* child) {
	childs.push_back(child);
}

Sequence::~Sequence(){

};
