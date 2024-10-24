/*
 * AudioServer.h
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
