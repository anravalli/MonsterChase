/*
 * EditorManager.cpp
 *
 *  Created on: 8 gen 2022
 *      Author: andrea
 */

#include "../arena.h"
#include "../gameconfig.h"
#include <editor/editor_ui.h>
#include <editor/level_editor.h>

namespace LevelEditor {

LevelEditor::LevelEditor(UiPageController *parent):
	UiPageController(parent)
{
	initPageView<EditorUi>();
	connect(page_view, SIGNAL(editor_closed()),this,SLOT(editor_closed()));

	QString map = ":/resources/map.txt";
	arena = new Arena(map, GameConfig::playground_width/MAP_WIDTH);
	arena->addToPage(page_view);

}

LevelEditor::~LevelEditor()
{
	delete arena;
}

void LevelEditor::show()
{
	arena->showAll();
	UiPageController::show();
}

void LevelEditor::exit()
{
	qDebug("LevelEditor::exit");
}

bool LevelEditor::handleKey(int key, bool released)
{
    bool ret = false;
    switch(key){
    case Qt::Key_Up:
    case Qt::Key_W:
    case Qt::Key_S:
    case Qt::Key_Down:
    case Qt::Key_Enter:
    case Qt::Key_Return:
    	qDebug("LevelEditor::handleKey");
    	break;
    case Qt::Key_Exit:
    case Qt::Key_Escape:
    	if (released)
    	{
    	}
        ret = true;
        break;
    default:
        break;
    }
    return ret;

}

void LevelEditor::editor_closed()
{
	qDebug("LevelEditor::editor_closed()");
	this->exit();
	emit(editor_finalized());
}

} /* namespace LevelEdior */
