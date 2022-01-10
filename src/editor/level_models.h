/*
 * LevelModel.h
 *
 *  Created on: 8 gen 2022
 *      Author: andrea
 */

#ifndef SRC_EDITOR_LEVEL_MODELS_H_
#define SRC_EDITOR_LEVEL_MODELS_H_

#include <vector>

#include <QJsonDocument>

namespace LevelEditor {

class Player;
class Monster;
class Wall;

class LevelModel final {
public:
	LevelModel();
	virtual ~LevelModel();

	void serialize();
	QJsonDocument &load(QString file_path);

private:
	QString level_name;
	std::pair<int,int> grid_size;
	std::vector<Wall*> walls;
	std::vector<Monster*> monsters;
	Player *player;

};

class LevelEntity
{
public:
	virtual void read(QJsonObject &json_obj);
	virtual void write(QJsonObject &json_obj);

	const std::pair<int, int>& getPosition() const;
	void setPosition(const std::pair<int, int> &position);
	const std::pair<int, int>& getSize() const;
	void setSize(const std::pair<int, int> &size);

protected:
	std::pair<int,int> position;
	std::pair<int,int> size;
};

class Player: public LevelEntity
{
public:

};
class Monster: public LevelEntity
{
public:
};
class Wall: public LevelEntity
{
public:
};

} /* namespace LevelEdior */

#endif /* SRC_EDITOR_LEVEL_MODELS_H_ */
