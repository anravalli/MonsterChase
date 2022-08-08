/*
 * optionpage_controller.h
 *
 *  Created on: 24 mar 2022
 *      Author: andrea
 */

#ifndef SRC_HISCORE_PANEL_OPTIONPAGE_CONTROLLER_H_
#define SRC_HISCORE_PANEL_OPTIONPAGE_CONTROLLER_H_

#include <vector>
#include <ui_framework/uipagecontroller.h>
#include <ui_framework/uipagemenu.h>

class HighScorePageController: public UiPageController
{
public:
	HighScorePageController(UiPageController *parent);
	virtual ~HighScorePageController();
	virtual void exit() override;
	virtual void show() override;
	bool handleKey(int key, bool released) override;

private:
	vector<vector<QString>> high_scores[4];
//	vector<vector<QString>> hunter_score_moc;
//	vector<vector<QString>> survivor_score_moc;
//	vector<vector<QString>> other_score_moc;

};

#endif /* SRC_HISCORE_PANEL_OPTIONPAGE_CONTROLLER_H_ */
