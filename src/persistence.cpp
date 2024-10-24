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

			// Converti i dati in un QJsonDocument
			persistence = QJsonDocument::fromJson(data);

			// Verifica se il JSON è valido
			if (persistence.isNull()) {
				qWarning() << "persistence is not a valid JSON document";
			}
			else if (persistence.isObject()) {
				QJsonObject obj = persistence.object();
				configuration = get("configuration", obj);
				highScores = get("high_score", obj);
				players = get("players", obj);
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

QJsonObject Persistence::get(QString item, QJsonObject &node) {
	qDebug() << "Persistence::get: " << item;
	QJsonObject obj;
	qDebug() << "Persistence - node.contains(item)" << node.contains(item);
	qDebug() << "Persistence - item.isObject()" << node.value(item).isObject();
	if (node.contains(item) && node.value(item).isObject()) {
		obj = node.value(item).toObject();
	}
	return obj;

}

QJsonObject Persistence::getConfiguration(QString item) {
	qDebug() << "Persistence::getConfiguration: " << item;
	QJsonObject obj;
	obj = get(item, configuration);
	return obj;
}
void Persistence::setConfiguration(QJsonObject item) {

}

void Persistence::commit() {
	QString homeDir = QDir::homePath();
//	QDir configDir(homeDir + "/.config");
	QFile file(homeDir + "/" + PRESISTENCE_DIR_NAME + "/" + PRESISTENCE_FILE_NAME);
	if (!file.open(QIODevice::WriteOnly)) {
		qCritical() << "Connot open \"~/" <<
				 PRESISTENCE_DIR_NAME "/" PRESISTENCE_FILE_NAME << "\" for wrinting";
	}
	// Scrivi il JSON nel file
	file.write(persistence.toJson());

	// Chiudi il file
	file.close();

	qDebug() << "Persistence file \" ~/" <<
			 PRESISTENCE_DIR_NAME "/" PRESISTENCE_FILE_NAME << "\" updated";
}




