/*
 * configuration.h
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
