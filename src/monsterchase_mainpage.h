/*
 * monsterchase_mainpage.h
 *
 *  Created on: 19 dic 2021
 *      Author: andrea
 */

#ifndef SRC_MONSTERCHASE_MAINPAGE_H_
#define SRC_MONSTERCHASE_MAINPAGE_H_

#include "ui/uipageview_qt.h"
#include "ui/uiviewitems_qt.h"
class MonsterChaseMainPage: public UiPageViewQt
{
public:
    MonsterChaseMainPage(UiPageViewQt *parent): UiPageViewQt(parent)
    {
        auto logo = new QGraphicsPixmapItem(QPixmap(":/resources/monster_chase_logo.png"));
        scene->addItem(logo);
    };
protected:
    virtual void setUpView() override
    {
        view->setBackgroundBrush(QColor(0x8e,0x68,0x85,0xff));
    }
};




#endif /* SRC_MONSTERCHASE_MAINPAGE_H_ */
