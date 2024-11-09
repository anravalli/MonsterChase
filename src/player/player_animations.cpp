/*
 * player_animations.cpp
 *
 *  Created on: 7 nov 2024
 *      Author: andrea
 */

#include "player_animations.h"
#include "base_game/gameconfig.h"

PlayerDeathAnimation::PlayerDeathAnimation(unsigned short duration) {
	this->duration = duration;
	this->frame_number = duration * GameConfig::framerate;
}

void PlayerDeathAnimation::update() {
	static unsigned short next_frame = 0;
	static unsigned short frame_counter = 0;
	static double alpha_decay = 0.01;
	static double scale_rise = 0.2;
	static unsigned short factor = 1;
	if(this->state == anim_running) {
		if(frame_counter == next_frame){
			next_frame += 5;
			alpha -= alpha_decay*factor;
			scale += scale_rise/factor;
			factor++;
		}
		frame_counter++;
		if(frame_counter >= frame_number){
			state = anim_completed;
		}
	}
	return;
}

void PlayerDeathAnimation::reset() {
	frame_index = 0;
	Animation::reset();
}

PlayerDamageAnimation::PlayerDamageAnimation(unsigned short duration) {
	this->duration = duration;
	this->frame_number = duration * GameConfig::framerate;
}

void PlayerDamageAnimation::update() {
	if(this->state == anim_running) {
		if(blink_delay>0){
			blink_delay--;
		} else {
			color_idx = 1-color_idx;
			blink_delay = 10;
		}
	}
}

void PlayerDamageAnimation::reset() {
	color_idx=0;
	blink_delay = 10;
	Animation::reset();
}




