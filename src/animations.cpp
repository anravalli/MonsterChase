/*
 * animations.cpp
 *
 *  Created on: 6 gen 2023
 *      Author: andrea
 */

#include "animations.h"
#include "gameconfig.h"

Animation::Animation() {
	this->state = anim_not_started;
	this->frame_index = 0;
	this->duration = 1; //seconds
}

Animation::~Animation() {
	// TODO Auto-generated destructor stub
}

unsigned short Animation::getAnimationFrameIdx() const {
	return frame_index;
}

void Animation::setAnimationFrameIdx(unsigned short frame) {
	this->frame_index = frame;
}

AnimationState Animation::getState() const {
	return state;
}

void Animation::reset() {
	this->state = anim_not_started;
	this->frame_index = 0;
}

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
	}
	if(this->frame_index >= this->frame_number)
		this->state = anim_completed;
}

void Animation::start() {
	this->state = anim_running;
}

void Animation::pause() {
	this->state = anim_paused;
}

PlayerDeathAnimation::PlayerDeathAnimation(unsigned short duration) {
	this->duration = duration;
	this->frame_number = duration * GameConfig::framerate;
}

void PlayerDeathAnimation::update() {
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


