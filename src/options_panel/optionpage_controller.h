/*
 * optionpage_controller.h
 *
 *  Created on: 24 mar 2022
 *      Author: andrea
 */

#ifndef SRC_OPTIONS_PANEL_OPTIONPAGE_CONTROLLER_H_
#define SRC_OPTIONS_PANEL_OPTIONPAGE_CONTROLLER_H_

#include <vector>
#include <ui_framework/uipagecontroller.h>
#include <ui_framework/uipagemenu.h>

class OptionItem;

class OptionPageController: public UiPageController
{
public:
	OptionPageController(UiPageController *parent);
	virtual ~OptionPageController();
	virtual void exit() override;
	virtual void show() override;
	bool handleKey(int key, bool released) override;

private:
	vector<OptionItem> model;

	UiPageMenu *active_menu;
	UiPageMenu *options_menu;
	UiPageMenu *confirm_exit_menu;
	QGraphicsPixmapItem *logo;

	bool is_saved;

	void open_confirm_popup();
	void close_confirm_popup();

	QJsonDocument &load_options(QString file_path);

	void change_screen_resolution();
	void set_fullscreen();
	void set_sounds();
	void apply_settings();
};

#endif /* SRC_OPTIONS_PANEL_OPTIONPAGE_CONTROLLER_H_ */
