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

	int addToPlaylist(const QString& fileName);
	void removeFromPlaylist(const QString& fileName);
	int getPlaylistIndex(const QString& fileName);
	void play(int pl_index, int loops = 1);
	void stop(int pl_index);

private:
	AudioServer();

	std::vector<QMixerStreamHandle> playlist;
	std::map<QString, int> playlistInfo;

	QMixerStream* mixer;
	QAudioOutput* output;

};


#endif /* SRC_AUDIO_SERVER_AUDIOSERVER_H_ */
