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
	virtual void reset();
	virtual void start();
	virtual void pause();

//	virtual void *getAnimationFrame(); TODO manage sprite animation
	virtual double getAnimationScale(){return scale;}
	virtual double getAnimationAlpha(){return alpha;}
//	virtual QColor getAnimationColor(); TODO manage color animation
	virtual QPointF getAnimationPos(){return position;}
	virtual double getAnimationRotation(){return rotation;}

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
	double alpha = 1.0;
	QPointF position = {0.0, 0.0};

};

#endif /* SRC_ANIMATIONS_H_ */
