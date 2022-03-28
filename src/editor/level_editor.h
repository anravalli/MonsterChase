/*
 * EditorManager.h
 *
 *  Created on: 8 gen 2022
 *      Author: andrea
 */

#ifndef SRC_EDITOR_LEVEL_EDITOR_H_
#define SRC_EDITOR_LEVEL_EDITOR_H_

#include <ui_framework/uipagecontroller.h>
#include "level_models.h"

class EditorUi;
class Arena;
class QWidget;

namespace LevelEditor {

class LevelEditor final : public UiPageController
{
	Q_OBJECT
public:
	explicit LevelEditor(UiPageController *parent = nullptr);
	virtual ~LevelEditor();
	virtual void show() override;
	virtual void exit() override;

public slots:
	virtual void editor_closed();

signals:
	void editor_finalized();

protected:
	bool handleKey(int key, bool released) override;

private:
	//EditorUi *editor_ui;
	Arena *arena;
	LevelModel level_model;

};

} /* namespace LevelEdior */

#endif /* SRC_EDITOR_LEVEL_EDITOR_H_ */
