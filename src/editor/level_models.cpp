/*
 * LevelModel.cpp
 *
 *  Created on: 8 gen 2022
 *      Author: andrea
 */

#include "level_models.h"
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>

namespace LevelEditor {

LevelModel::LevelModel() {
	// TODO Auto-generated constructor stub

}

LevelModel::~LevelModel() {
	// TODO Auto-generated destructor stub
}

void LevelModel::serialize()
{
	qDebug("LevelModel::serilize");
	qDebug("...serializing model to json");
	QJsonObject level;
	QJsonObject player_obj;
	player->write(player_obj);
	level["player"] = player_obj;

	QJsonArray json_monsters;
	foreach (auto m, monsters) {
		QJsonObject json_monster;
		m->write(json_monster);
		json_monsters.append(json_monster);
	}
	level["monsters"] = json_monsters;

	QJsonDocument document(level);
	qDebug("%s", (document.toJson(QJsonDocument::Indented)).toStdString().c_str());
}

const std::pair<int, int>& LevelEntity::getPosition() const {
	return position;
}

void LevelEntity::setPosition(const std::pair<int, int> &position) {
	this->position = position;
}

const std::pair<int, int>& LevelEntity::getSize() const {
	return size;
}

void LevelEntity::setSize(const std::pair<int, int> &size) {
	this->size = size;
}

QJsonDocument& LevelModel::load(QString file_path)
{
	Q_UNUSED(file_path)
}

void LevelEntity::read(QJsonObject &json_obj)
{
	Q_UNUSED(json_obj)
}

void LevelEntity::write(QJsonObject &json_obj)
{
	Q_UNUSED(json_obj)
}

} /* namespace LevelEdior */
