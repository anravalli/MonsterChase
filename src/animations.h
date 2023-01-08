/*
 * animations.h
 *
 *  Created on: 6 gen 2023
 *      Author: andrea
 */

#ifndef SRC_ANIMATIONS_H_
#define SRC_ANIMATIONS_H_

#include <QPoint>

enum AnimationState {
	anim_not_started,
	anim_running,
	anim_paused,
	anim_completed
};

namespace Monster{
struct MonsterModel;
}

class Animation {
public:
	Animation();
	virtual ~Animation();

	unsigned short getAnimationFrameIdx() const;
	void setAnimationFrameIdx(unsigned short frame);
	AnimationState getState() const;
	void reset();
	void start();
	void pause();

//	virtual void *getAnimationFrame(); TODO manage sprite animation
	double getAnimationScale(){return scale;}
//	virtual QColor getAnimationColor(); TODO manage color animation
	QPointF getAnimationPos(){return position;}
	double getAnimationRotation(){return rotation;}

	virtual void update(){};

protected:
	AnimationState state;
	unsigned short frame_index;
	unsigned short duration;
	//bool looping;
	//unsigned short loop[];
	//AnimationType type = linear

	double rotation = 0.0;
	double scale = 1.0;
	QPointF position = {0.0, 0.0};

};

class DeathAnimation: public Animation {
public:
	DeathAnimation(unsigned short duration);
	virtual void update() override;
private:
	unsigned short frame_number;
	unsigned short scale_sub_rate = 5;
	unsigned short scale_frame_counter = scale_sub_rate;
	double rotation_step = 10;
};

#endif /* SRC_ANIMATIONS_H_ */
