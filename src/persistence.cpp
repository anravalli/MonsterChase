/*
 * configuration.cpp
 *
 *  Created on: 15 ott 2024
 *      Author: andrea
 */

#include "persistence.h"
#include <QDir>
#include <QFile>
#include <QDebug>
#include <QJsonObject>
#include <QJsonArray>

#define PRESISTENCE_FILE_NAME "monsterchase_persistence.json"
#define PRESISTENCE_DIR_NAME ".config"
Persistence::Persistence() {
	QDir::home().mkdir("/" PRESISTENCE_DIR_NAME);
	QDir configDir(QDir::homePath() + "/" PRESISTENCE_DIR_NAME);
	const QString persistence_path(configDir.absolutePath()+ "/" PRESISTENCE_FILE_NAME);
	QFile persistence_file(persistence_path);
	qDebug() << "persistence";
	if(configDir.exists()){
		qDebug() << "config dir ok";
		// Verifica se il file esiste e lo crea se necessario
		if (!persistence_file.exists()) {
			if (!persistence_file.open(QIODevice::WriteOnly)) {
				qCritical() << "Cannot create persistence file: " << persistence_file.fileName();
				//	            return 1;
			}
			qDebug() << "config file created";
			persistence_file.close(); // Chiudiamo il file dopo averlo creato
		}

		// Apri il file in lettura e scrittura
		if (persistence_file.open(QIODevice::ReadWrite)) {

			QByteArray data = persistence_file.readAll();


			auto doc = QJsonDocument::fromJson(data);

			// Verifica se il JSON è valido
			if (doc.isNull()) {
				qWarning() << "persistence is not a valid JSON document";
			}
			else if (doc.isObject()) {
				persistence = doc.object();
			}
			persistence_file.close();
		}
		else
			qCritical() << "cannot open file " << persistence_file.fileName();
	}
	else {
		qCritical() << "cannot create config dir: " << QDir::homePath() + "/"PRESISTENCE_DIR_NAME;
	}

}

Persistence &Persistence::instance() {
	static Persistence me;
	return me;
}

Persistence::~Persistence() {
	// TODO Auto-generated destructor stub
}

QJsonObject Persistence::getObject(QString item, QJsonObject &pnode) {
	qDebug() << "Persistence::get: " << item;
	QJsonObject obj;
	qDebug() << "Persistence - node.contains(item)" << pnode.contains(item);
	qDebug() << "Persistence - item.isObject()" << pnode.value(item).isObject();
	if (pnode.contains(item) && pnode.value(item).isObject()) {
		obj = pnode.value(item).toObject();
	}
	return obj;

}

QJsonArray Persistence::getArray(QString item, QJsonObject &pnode) {
	qDebug() << "Persistence::get: " << item;
	QJsonArray obj;
	qDebug() << "Persistence - node.contains(item)" << pnode.contains(item);
	qDebug() << "Persistence - item.isObject()" << pnode.value(item).isArray();
	if (pnode.contains(item) && pnode.value(item).isArray()) {
		obj = pnode.value(item).toArray();
	}
	return obj;

}



QJsonObject Persistence::getConfigurationItem(QString item) {
	qDebug() << "Persistence::getConfiguration: " << item;
	QJsonObject obj;
	auto configuration = getObject("configuration", persistence);
	obj = getObject(item, configuration);
	return obj;
}

QJsonObject Persistence::getConfiguration() {
	return getObject("configuration", persistence);
}

QJsonArray Persistence::getHighScores() {
	return getArray("high_score", persistence);
}

QJsonArray Persistence::getPlayers() {
	return getArray("players", persistence);
}


void Persistence::setConfiguration(QJsonObject cfg) {
	persistence["configuration"] = cfg;
	commit();
}

void Persistence::setHighScores(QJsonArray hs) {
	persistence["high_score"] = hs;
	commit();
}

void Persistence::setPlayers(QJsonArray players) {
	persistence["players"] = players;
	commit();
}

void Persistence::commit() {
	qDebug() << "Persistence::commit";
	QString homeDir = QDir::homePath();
//	QDir configDir(homeDir + "/.config");
	QFile file(homeDir + "/" + PRESISTENCE_DIR_NAME + "/" + PRESISTENCE_FILE_NAME);
	if (!file.open(QIODevice::WriteOnly)) {
		qCritical() << "Connot open \"~/" <<
				 PRESISTENCE_DIR_NAME "/" PRESISTENCE_FILE_NAME << "\" for wrinting";
	}

	//update document

	QJsonDocument doc;
	doc.setObject(persistence);

	// Scrivi il JSON nel file
	file.write(doc.toJson());

	// Chiudi il file
	file.close();

	qDebug() << "Persistence file \" ~/" <<
			 PRESISTENCE_DIR_NAME "/" PRESISTENCE_FILE_NAME << "\" updated";
}




