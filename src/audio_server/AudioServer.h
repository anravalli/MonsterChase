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
 *  Created on: 25 feb 2024
 *      Author: andrea
 */

#ifndef SRC_AUDIO_SERVER_AUDIOSERVER_H_
#define SRC_AUDIO_SERVER_AUDIOSERVER_H_

#include <QtCore>
#include <vector>
#include <map>

#include "QMixerStream.h"

//class QMixerStreamHandle;
//class QMixerStream;
class QAudioOutput;

class AudioServer {
public:
	virtual ~AudioServer();

	static AudioServer& instance();

	void setMusicScore(const QString& fileName);
	int addFx(const QString& fileName);
	void removeFx(const QString& fileName);
	int getFxIndex(const QString& fileName);
	void playFx(int fx_index);
	void stopFx(int fx_index);

	void enableSounds(bool en);
	void enableMusic(bool en);
	void setVolume(unsigned int v);

private:
	AudioServer();

	QMixerStreamHandle musicScore;
	QString currentMusicScore = "";
	std::vector<QMixerStreamHandle> fxPlaylist;
	std::map<QString, int> fxPlaylistInfo;

	QMixerStream* mixer;
	QAudioOutput* output;

	bool soundsEnable = true;
	bool musicEnable = true;
	int volume = 5; //store in linear scale

};


#endif /* SRC_AUDIO_SERVER_AUDIOSERVER_H_ */
