/*
 *	Monster Chase: a testing playground for behaviors trees
 *
 *	Copyright 2021 Andrea Ravalli <anravalli @ gmail.com>
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

#ifndef MONSTERCHASE_H
#define MONSTERCHASE_H

#include <vector>
#include <functional>
#include <QTimer>
#include <lib/ui_framework/uipagecontroller.h>
#include <lib/ui_framework/uipagemenu.h>

using namespace std;

class QGraphicsPixmapItem;

namespace LevelEditor{
class LevelEditor;
}
class OptionPageController;
class HighScorePageController;
class GameController;

class MonsterChase : public UiPageController
{
    Q_OBJECT

public:
    MonsterChase();
    ~MonsterChase() override ;
    virtual void exit() override;
    bool handleKey(int key, bool released) override;


public slots:
    virtual void editor_closed();

protected:
    void select_next_item(bool released);
    void select_previous_item(bool released);
    void show_selcted_item(bool released);

private:
    GameController *game_controller = nullptr;

    UiPageMenu *current_menu;
    UiPageMenu *base_menu;
    UiPageMenu *match_menu;
    UiPageMenu *match_selection_menu;
    UiPageMenu *player_selection_menu;
    UiPageMenu *confirm_exit_menu;
    //QGraphicsPixmapItem *logo;

    int pli_main_theme;

    LevelEditor::LevelEditor *level_editor;
    OptionPageController *options_panel;
    HighScorePageController *hiscore_panel;

    UiPageMenu *populate_base_menu();
    UiPageMenu *populate_match_menu();
    UiPageMenu *populate_confirm_exit_menu();
    UiPageMenu *populate_match_selection_menu();
    UiPageMenu *populate_player_selection_menu();

    void open_popup(UiPageMenu *popup);
    void back_to_menu(UiPageMenu *menu);

    void open_level_editor();
    void open_options_panel();
    void open_high_score_page();

};


#endif // MONSTERCHASE_H
