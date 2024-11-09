/*
 * player_animations.h
 *
 *  Created on: 7 nov 2024
 *      Author: andrea
 */

#include "lib/animations.h"

#ifndef SRC_PLAYER_PLAYER_ANIMATIONS_H_
#define SRC_PLAYER_PLAYER_ANIMATIONS_H_


class PlayerDeathAnimation: public Animation {
public:
	PlayerDeathAnimation(unsigned short duration);
	virtual void update() override;
	virtual void reset() override;
	virtual ~PlayerDeathAnimation(){};
private:
	unsigned short frame_number;

	unsigned short frame_duration = 0;
};


class PlayerDamageAnimation: public Animation {
public:
	PlayerDamageAnimation(unsigned short duration);
	virtual void update() override;
	virtual void reset() override;
	unsigned short getColorIndex(){return color_idx;};
	virtual ~PlayerDamageAnimation(){};
private:
	unsigned short frame_number;
	unsigned short blink_delay = 10;
	unsigned short colors[2] = {0,1};
	unsigned short color_idx = 0;
};




#endif /* SRC_PLAYER_PLAYER_ANIMATIONS_H_ */
