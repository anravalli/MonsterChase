/*
 * monsters_animations.cpp
 *
 *  Created on: 7 nov 2024
 *      Author: andrea
 */

#include "monsters_animations.h"
#include "base_game/gameconfig.h"

MonsterDeathAnimation::MonsterDeathAnimation(unsigned short duration) {
	this->duration = duration;
	this->frame_number = duration * GameConfig::framerate;
}

void MonsterDeathAnimation::update() {
	if(this->state == anim_running) {
		this->frame_index++;
		this->rotation += this->rotation_step;
		this->scale_frame_counter--;
		if(!this->scale_frame_counter){
			this->scale -= 0.1;
			this->scale_frame_counter = this->scale_sub_rate;
		}
		if(this->frame_index >= this->frame_number)
			this->state = anim_completed;
	}
}


