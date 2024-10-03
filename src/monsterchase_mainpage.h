/*
 * monsterchase_mainpage.h
 *
 *  Created on: 19 dic 2021
 *      Author: andrea
 */

#ifndef SRC_MONSTERCHASE_MAINPAGE_H_
#define SRC_MONSTERCHASE_MAINPAGE_H_

#include <ui_framework/uipageview_qt.h>
#include <ui_framework/uiviewitems_qt.h>
#include <audio_server/AudioServer.h>

class MonsterChaseMainPage: public UiPageViewQt
{
public:
    MonsterChaseMainPage(UiPageViewQt *parent): UiPageViewQt(parent)
    {
        auto logo = new QGraphicsPixmapItem(QPixmap(":/resources/monster_chase_logo.png"));
        scene->addItem(logo);
        theme_index = AudioServer::instance().addToPlaylist(":/resources/audio/MainTheme.wav");
    };

    virtual void show() final override {
        AudioServer::instance().play(theme_index, -1);
        UiPageViewQt::show();
    }

    virtual void hide() final override {
        AudioServer::instance().stop(theme_index);
        UiPageViewQt::hide();
    }
protected:
    virtual void setUpView() override
    {
        view->setBackgroundBrush(QColor(0x8e,0x68,0x85,0xff));
    }
private:
    int theme_index = 0;
};




#endif /* SRC_MONSTERCHASE_MAINPAGE_H_ */
