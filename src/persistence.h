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

class Persistence {
public:
	virtual ~Persistence();
	static Persistence &instance();

	QJsonObject getConfiguration(QString item);
	void setConfiguration(QJsonObject item);
	void commit();

private:
	Persistence();
	QJsonObject get(QString item, QJsonObject &document);
	QJsonDocument persistence;

	QJsonObject configuration;
	QJsonObject highScores;
	QJsonObject players;
};

#endif /* SRC_PERSISTENCE_H_ */
