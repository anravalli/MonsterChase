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

#include <QtWidgets>
#include "monster.h"


class MonsterNormal: public MonsterSm {
public:
    MonsterNormal(MonsterModel* model)
        :_model(model){}

    virtual void tick(){
        move();
    }
    virtual ~MonsterNormal(){}

private:
    int _speed=5;
protected:
    MonsterModel* _model;

    void move(){
        if(_model->direction[Monster_up])
            _model->pos_y=_model->pos_y-_speed;
        if(_model->direction[Monster_down])
            _model->pos_y=_model->pos_y+_speed;
        if(_model->direction[Monster_left])
            _model->pos_x=_model->pos_x-_speed;
        if(_model->direction[Monster_right])
            _model->pos_x=_model->pos_x+_speed;
        return;
    }
};

class MonsterRageAvailable: public MonsterNormal {
public:
    MonsterRageAvailable(MonsterModel* model)
        :MonsterNormal(model){}
    virtual void tick(){
        move();
    }
};

class MonsterOnRage: public MonsterSm {
public:
    MonsterOnRage(MonsterModel* model)
        :_model(model){}

    virtual void tick(){
        move();
    }
    virtual void toggleRage(){
        _model->state=normal;
    }
    virtual ~MonsterOnRage(){}
private:
    MonsterModel* _model;
    int _speed=10;

    void move(){
        if(_model->direction[Monster_up])
            _model->pos_y=_model->pos_y-_speed;
        if(_model->direction[Monster_down])
            _model->pos_y=_model->pos_y+_speed;
        if(_model->direction[Monster_left])
            _model->pos_x=_model->pos_x-_speed;
        if(_model->direction[Monster_right])
            _model->pos_x=_model->pos_x+_speed;
        return;
    }
};

class MonsterDead: public MonsterSm {
public:
    MonsterDead(MonsterModel* model)
        :_model(model){}

    virtual void tick(){}
    virtual void toggleRage(){}
    virtual ~MonsterDead(){}
private:
    MonsterModel* _model;
};

Monster::Monster(QGraphicsScene * s){

    shape = new MonsterShape(&model);

    //init state machine
    pstates[normal] = new MonsterNormal(&model);
    pstates[rage_available] = new MonsterRageAvailable(&model);
    pstates[on_rage] = new MonsterOnRage(&model);
    pstates[dead] = new MonsterDead(&model);
    //the order we add the items to the scene affects the z-order
    s->addItem(shape);
    QApplication::instance()->installEventFilter(this);
}

void Monster::tick(){
    pstates[model.state]->tick();

    shape->setPos(model.pos_x,model.pos_y);
    shape->update();
}

Monster::~Monster(){
    delete pstates[normal];
    delete pstates[on_rage];
    delete pstates[dead];
    //TODO: check wether the QGraphicsItems are deleted by the QGraphicsScene
    // they belongs to
    delete shape;
}

/*
 * MonsterShape methods implementation
 */

MonsterShape::MonsterShape(MonsterModel* m)
{
    color[0] = QColor(Qt::green);
    color[1] = QColor(Qt::red);
    model = m;
}

QRectF MonsterShape::boundingRect() const
{
    return QRectF(-15.5, -15.5, 34, 34);
}

void MonsterShape::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    switch(model->state){
    case on_rage:
        //qDebug("%d on_rage", __LINE__);
        color_idx = 1;
        break;
    case normal:
        //qDebug("%d normal", __LINE__);
        color_idx = 0;
        break;
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

