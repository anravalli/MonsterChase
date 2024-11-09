/*
 * monsters_animations.h
 *
 *  Created on: 7 nov 2024
 *      Author: andrea
 */

#include "lib/animations.h"

#ifndef SRC_MONSTERS_MONSTERS_ANIMATIONS_H_
#define SRC_MONSTERS_MONSTERS_ANIMATIONS_H_


class MonsterDeathAnimation: public Animation {
public:
	MonsterDeathAnimation(unsigned short duration);
	virtual void update() override;
private:
	unsigned short frame_number;
	unsigned short scale_sub_rate = 5;
	unsigned short scale_frame_counter = scale_sub_rate;
	double rotation_step = 10;
};





#endif /* SRC_MONSTERS_MONSTERS_ANIMATIONS_H_ */
