/*
 *	Monster Chase: a testing playground for behaviors trees
 *
 *	Copyright 2024 Andrea Ravalli <anravalli @ gmail.com>
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
 *
 *  Created on: 15 ott 2024
 *      Author: andrea
 */

#ifndef SRC_PERSISTENCE_H_
#define SRC_PERSISTENCE_H_

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

class Persistence {
public:
	virtual ~Persistence();
	static Persistence &instance();

	QJsonObject getConfigurationItem(QString item);
	QJsonObject getConfiguration();
	QJsonArray getHighScores();
	QJsonArray getPlayers();
	void setConfiguration(QJsonObject item);
	void setHighScores(QJsonArray hs);
	void setPlayers(QJsonArray players);

private:
	Persistence();
	void commit();
	QJsonObject getObject(QString item, QJsonObject &document);
	QJsonArray getArray(QString item, QJsonObject &pnode);
	QJsonObject persistence;

};

#endif /* SRC_PERSISTENCE_H_ */
