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

#include "monster.h"
#include "monsterchase.h"

namespace Monster{

    class MonsterPatrol: public MonsterSm {
    public:
        MonsterPatrol(MonsterModel* model)
            :_model(model){}

        virtual void tick(){
            move();
        }
        virtual ~MonsterPatrol(){}

    private:
        int _speed=2;
        int xsteps = 0;
        int ysteps = 0;
    protected:
        MonsterModel* _model;

        void move(){
            if (xsteps < 100 and ysteps == 0){
                _model->pos_x+=_speed;
                xsteps++;
            }
            else if(xsteps == 100 and ysteps < 100){
                _model->pos_y+=_speed;
                ysteps++;
            }
            else if(xsteps > 0 and ysteps == 100){
                _model->pos_x-=_speed;
                xsteps--;
            }
            else if(xsteps == 0 and ysteps > 0){
                _model->pos_y-=_speed;
                ysteps--;
            }

            if(_model->direction<=360)
                _model->direction++;
            else
                _model->direction=0;
            return;
        }
    };

    class MonsterAttack: public MonsterSm {
    public:
        MonsterAttack(MonsterModel* model)
            :_model(model){}
        virtual void tick(){
            move();
        }
    private:
        MonsterModel* _model;

        void move(){
            return;
        }
    };

    class MonsterFlee: public MonsterSm {
    public:
        MonsterFlee(MonsterModel* model)
            :_model(model){}

        virtual void tick(){
            move();
        }
        virtual ~MonsterFlee(){}
    private:
        MonsterModel* _model;
        int _speed=10;

        void move(){
            _model->pos_x=_model->pos_x-_speed;
            _model->pos_x=_model->pos_x+_speed;
            return;
        }
    };

    Monster::Monster(MonsterChase* w):
        world(w)
    {

        shape = new MonsterShape(&model);
        sight = new MonsterSight(&model);

        //init state machine
        mstates[patrol] = new MonsterPatrol(&model);
        mstates[attack] = new MonsterAttack(&model);
        mstates[flee] = new MonsterFlee(&model);

        //the order we add the items to the scene affects the z-order
        world->getScene()->addItem(shape);
        world->getScene()->addItem(sight);

        QApplication::instance()->installEventFilter(this);
    }

    void Monster::show(){
        shape->show();
        sight->show();
    }

    void Monster::hide(){
        shape->hide();
        sight->hide();
    }

    QRectF Monster::collisionBox() const
    {
        return QRectF(model.pos_x-15, model.pos_y-15, 30, 30);
    }

    void Monster::update(){
        mstates[model.state]->tick();

        shape->setPos(model.pos_x,model.pos_y);
        shape->setRotation(model.direction);
        sight->setPos(model.pos_x,model.pos_y);
        sight->setRotation(model.direction);
        shape->update();
        sight->update();
    }

    Monster::~Monster(){
        delete mstates[patrol];
        delete mstates[attack];
        delete mstates[flee];
        //TODO: check wether the QGraphicsItems are deleted by the QGraphicsScene
        // they belongs to
        delete shape;
        delete sight;
    }

    /*
     * MonsterShape methods implementation
     */

    MonsterShape::MonsterShape(MonsterModel* m)
    {
        color[patrol] = QColor(0,127,127);
        color[attack] = QColor(255,50,127);
        color[flee] = QColor(0,127,255);
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

        painter->setPen(Qt::NoPen);
        painter->setBrush(Qt::darkGray);
        painter->drawRect(-12, -12, 30, 30);
        painter->setPen(QPen(Qt::black, 1));
        painter->setBrush(QBrush(color[model->state]));
        painter->drawRect(-15, -15, 30, 30);
        painter->setPen(Qt::NoPen);
        //temp
        //painter->setBrush(QBrush(QColor(0,255,50,50)));
        //painter->drawPie(-100,-165,200,300,50*16,80*16);
    }

} //namescpace Monster
