/*
 * animations.cpp
 *
 *  Created on: 6 gen 2023
 *      Author: andrea
 */

#include "animations.h"

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

void Animation::start() {
	this->state = anim_running;
}

void Animation::pause() {
	this->state = anim_paused;
}

