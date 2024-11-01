/*
 * optionpage_controller.cpp
 *
 *  Created on: 24 mar 2022
 *      Author: andrea
 */

#include "optionpage_controller.h"
#include "optionpage_view.h"
#include "optionsmenu.h"
#include "audio_server/AudioServer.h"
#include "persistence.h"

OptionPageController::OptionPageController(UiPageController *parent):
	UiPageController(parent)
{

	is_saved = true;
	initPageView<OptionPageView>();

	initModel();

	options_menu = new OptionsMenu(&model);
	options_menu->setPos(GameConfig::playground_width/2,
	    		GameConfig::playground_width/2+100);
	options_menu->setAlignement(align_center);

	vector<QString> popup_model = {"apply", "discard"};
	vector<function<void()>> popup_actions;
	popup_actions.push_back([this]{
		this->apply_settings();
		this->close_confirm_popup();
		this->exit();
	});
	popup_actions.push_back([this]{
		this->discard_settings();
		this->close_confirm_popup();
		this->exit();
	});
	auto *popup_view = new UiPagePopupWidget_qt(QString("Do you want to apply your changes before exit?"),
			new UiPageMenuWidget_qt(&popup_model));

	confirm_exit_menu = new UiPageMenu(popup_actions, popup_view, 1);
	confirm_exit_menu->setPos(GameConfig::playground_width/2, GameConfig::playground_height/3);
	confirm_exit_menu->hide();
	confirm_exit_menu->addToPage(page_view);

	active_menu = options_menu;
	active_menu->addToPage(page_view);

	//load saved config
	sound_cfg = Persistence::instance().getConfigurationItem("sound");
	video_cfg = Persistence::instance().getConfigurationItem("video");


}

OptionPageController::~OptionPageController()
{
	// TODO Auto-generated destructor stub
}

static int resolutionToIndex(QString res)
{
	int index = 0;
	if(res == "800x600")
		index = 0;
	else if(res == "1024x768")
		index = 1;
	else if(res == "1280x960")
		index = 2;
	return index;
}
void OptionPageController::show(){

	//update config model
	QString resolution = video_cfg.value("resolution").toString("800x600");
	bool fscreenEnable = video_cfg.value("fullscreen").toBool(true);
	int vol = sound_cfg.value("volume").toInt(5);
	bool soundsEnable = sound_cfg.value("soundfx").toBool(true);
	bool musicEnable = sound_cfg.value("music").toBool(true);

	((OptionsMenu*)options_menu)->change_current_value_of(0, resolutionToIndex(resolution));
	((OptionsMenu*)options_menu)->change_current_value_of(1, fscreenEnable? 0 : 1);
	((OptionsMenu*)options_menu)->change_current_value_of(2, soundsEnable? 0 : 1);
	((OptionsMenu*)options_menu)->change_current_value_of(3, musicEnable? 0 : 1);
	((OptionsMenu*)options_menu)->change_current_value_of(4, vol-1);

	UiPageController::show();
}

void OptionPageController::exit()
{
    qDebug("OptionPageController::exit()");
    qDebug("is_saved %d", is_saved);
    UiPageController::exit();
}

bool OptionPageController::handleKey(int key, bool released)
{

    bool ret = false;
    switch(key){
    case Qt::Key_W:
    case Qt::Key_S:
    case Qt::Key_A:
    case Qt::Key_D:
    case Qt::Key_Up:
    case Qt::Key_Down:
    case Qt::Key_Left:
    case Qt::Key_Right:
    case Qt::Key_Enter:
    case Qt::Key_Return:
    	ret = active_menu->handleKey(key, released);
    	break;
    case Qt::Key_Exit:
    case Qt::Key_Escape:
    	if (released)
    	{
    		if(active_menu == confirm_exit_menu)
    		{
    			close_confirm_popup();
    		}
    		else if (!is_saved)
    		{
    			open_confirm_popup();
    		}
    		else
    			exit();
    	}
        ret = true;
        break;
    default:
        break;
    }
    return ret;

}

void OptionPageController::open_confirm_popup()
{
	if (!is_saved)
	{
		this->active_menu->deactivate();
		this->active_menu = this->confirm_exit_menu;
		this->active_menu->show();
	}
	else
		this->exit();
}

void OptionPageController::close_confirm_popup()
{
	this->active_menu->hide();
	this->active_menu = this->options_menu;
	this->active_menu->activate();
}

void OptionPageController::change_screen_resolution()
{
	int idx = options_menu->get_current_item_idx();
	int val_idx = ((OptionsMenu *)options_menu)->get_current_value_of(idx);
	qDebug("screen resolution set to %s", model[idx].str_values[val_idx].toStdString().c_str());

	//TODO: set resolution

	video_cfg["resolution"] = QJsonValue(model[idx].str_values[val_idx]);

	is_saved = false;
}

void OptionPageController::set_fullscreen()
{
	int idx = options_menu->get_current_item_idx();
	int val_idx = ((OptionsMenu *)options_menu)->get_current_value_of(idx);
	qDebug("fullscreen set to %s", model[idx].str_values[val_idx].toStdString().c_str());
	bool fscreen_en = false;
	if(model[idx].str_values[val_idx] == "on")
		fscreen_en = true;

	//TODO: set fullscreen

	video_cfg["fullscreen"] = fscreen_en;
	is_saved = false;
}

void OptionPageController::set_soundsfx()
{
	int idx = options_menu->get_current_item_idx();
	int val_idx = ((OptionsMenu *)options_menu)->get_current_value_of(idx);
	qDebug("soundFx set to %s", model[idx].str_values[val_idx].toStdString().c_str());
	bool sfx_en = false;
	if(model[idx].str_values[val_idx] == "on")
		sfx_en = true;

	AudioServer::instance().enableSounds(sfx_en);
	sound_cfg["soundfx"] = sfx_en;
	is_saved = false;
}

void OptionPageController::set_music()
{
	int idx = options_menu->get_current_item_idx();
	int val_idx = ((OptionsMenu *)options_menu)->get_current_value_of(idx);
	qDebug("music set to %s", model[idx].str_values[val_idx].toStdString().c_str());
	bool music_en = false;
	if(model[idx].str_values[val_idx] == "on")
		music_en = true;

	AudioServer::instance().enableMusic(music_en);
	sound_cfg["music"] = music_en;
	is_saved = false;
}

void OptionPageController::set_volume()
{
	int idx = options_menu->get_current_item_idx();
	int val_idx = ((OptionsMenu *)options_menu)->get_current_value_of(idx);
	qDebug("volume set to %s", model[idx].str_values[val_idx].toStdString().c_str());
	bool ok = false;
	unsigned int vol = model[idx].str_values[val_idx].toUInt(&ok, 10);
	if(ok)
		AudioServer::instance().setVolume(vol);

	sound_cfg["volume"] = QJsonValue((int)vol);
	is_saved = false;
}

void OptionPageController::apply_settings()
{
	auto cfg = Persistence::instance().getConfiguration();
	cfg["sound"] = sound_cfg;
	cfg["video"] = video_cfg;
	Persistence::instance().setConfiguration(cfg);
	is_saved = true;
}

void OptionPageController::discard_settings()
{
	sound_cfg = Persistence::instance().getConfigurationItem("sound");
	video_cfg = Persistence::instance().getConfigurationItem("video");

	int vol = sound_cfg.value("volume").toInt(5);
	bool soundsEnable = sound_cfg.value("soundfx").toBool(true);
	bool musicEnable = sound_cfg.value("music").toBool(true);

	//TODO restore video settings

	AudioServer::instance().setVolume(vol);
	AudioServer::instance().enableMusic(musicEnable);
	AudioServer::instance().enableSounds(soundsEnable);

	is_saved = true;
}

void OptionPageController::initModel()
{

	model.push_back(
			OptionItem(
					"Screen Resolution",
					{"800x600","1024x768","1280x960"},
					0,
					0,
					[this]{	this->change_screen_resolution(); }
			)
	);

	model.push_back(
			OptionItem(
					"Fullscreen",
					{"yes", "not"},
					1,
					1,
					[this]{this->set_fullscreen();}
			)
	);

	model.push_back(
			OptionItem(
					"Sound FX",
					{"on","off"},
					0,
					0,
					[this]{this->set_soundsfx();}
			)
	);

	model.push_back(
			OptionItem(
					"Music",
					{"on","off"},
					0,
					0,
					[this]{this->set_music();}
			)
	);

	model.push_back(
			OptionItem(
					"Volume",
					{"1","2","3", "4", "5", "6", "7", "8", "9", "10"},
					0,
					0,
					[this]{this->set_volume();}
			)
	);

	model.push_back(
			OptionItem(
					"Apply",
					{},
					-1,
					-1,
					[this]{this->apply_settings();}
			)
	);

	model.push_back(
			OptionItem(
					"Back",
					{},
					-1,
					-1,
					[this]{this->open_confirm_popup();}
			)
	);
}

