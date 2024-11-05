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

#include "playerqtviews.h"
#include "lib/animations.h"
// Player Score view

PlayerScore::PlayerScore(PlayerModel* m)
    :_model(m)
{
    this->setPen(QPen(Qt::blue));
    QFont font("Helvetica",14,QFont::Bold);
    this->setFont(font);
    this->setBrush(Qt::white);
    this->setText(QString::asprintf("%06d", _model->score));
}

void PlayerScore::updateScore(){
    this->setText(QString::asprintf("%06d", _model->score));
}


/*
 * PlayerShape methods implementation
 */

PlayerShape::PlayerShape(PlayerModel* m)
{
    color[0] = QColor(Qt::yellow);
    color[1] = QColor(Qt::red);
    model = m;
}

QRectF PlayerShape::boundingRect() const
{
    return QRectF(-15.5, -15.5, 34, 34);
}

void PlayerShape::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    double scale_anim =  model->current_animation->getAnimationScale();
    this->setScale(scale_anim);
    double alpha_anim =  model->current_animation->getAnimationAlpha();
    this->setOpacity(alpha_anim);

    switch(model->state){
    case on_rage:
#ifdef  DEBUG
        qDebug("%d on_rage", __LINE__);
#endif
        color_idx = 1;
        break;
    case normal:
    case rage_available:
#ifdef  DEBUG
        qDebug("%d normal", __LINE__);
#endif
        color_idx = 0;
        break;
    case on_damage:
    	color_idx = static_cast<PlayerDamageAnimation*>(model->current_animation)->getColorIndex();
        break;
    case dead:
    default:
        break;
    }
    painter->setPen(Qt::NoPen);
    painter->setBrush(Qt::darkGray);
    painter->drawEllipse(-12, -12, 30, 30);
    painter->setPen(QPen(Qt::black, 1));
    painter->setBrush(QBrush(color[color_idx]));
    painter->drawEllipse(-15, -15, 30, 30);
}

// Player Score view

PlayerEnergyGauge::PlayerEnergyGauge(PlayerModel *m)
    :model(m)
{
    color = QColor(0,255,0,127);
    color_rage[0] = QColor(255,0,0,127);
    color_rage[1] = QColor(255,100,0,127);
    color_rage_idx = 0;
}


QRectF PlayerEnergyGauge::boundingRect() const
{
    return QRectF(0,0, 104,20);
}

int PlayerEnergyGauge::blink()
{
    if(iteration==5){
        color_rage_idx=1-color_rage_idx;
        iteration = 0;
    } else
        iteration++;
    return color_rage_idx;
}

void PlayerEnergyGauge::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{

    Q_UNUSED(option);
    Q_UNUSED(widget);
    //draw external rectangle
    painter->setPen(QPen(Qt::black, 2));
    painter->setBrush(Qt::NoBrush);
    painter->drawRect(0,0, 104,20);
    //draw inner rectangle
    painter->setPen(Qt::NoPen);
    if(model->state == rage_available)
        painter->setBrush(color_rage[blink()]);
    else if(model->state == on_rage)
        painter->setBrush(color_rage[0]);
    else{
        painter->setBrush(color);
    }

    painter->drawRect(2,2,static_cast<int>(model->energy),16);
}

