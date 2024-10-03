/*
 * AudioServer.cpp
 *
 *  Created on: 25 feb 2024
 *      Author: andrea
 */

#include "AudioServer.h"


#include <QAudioDeviceInfo>
#include <QAudioOutput>

AudioServer::~AudioServer() {
	// TODO Auto-generated destructor stub
}

int AudioServer::addToPlaylist(const QString& fileName) {
    int current_index = 0;
    auto it = playlistInfo.find(fileName);
    if(it == playlistInfo.end()) {
        current_index = playlist.size();
        playlistInfo[fileName] = current_index;
        QMixerStreamHandle tmp = mixer->openStream(fileName);
        playlist.push_back(tmp);
    }
    else
        current_index = it->second;

    return current_index;
}

void AudioServer::play(int pl_index, int loops) {
    playlist[pl_index].setLoops(loops);
    playlist[pl_index].play();
}

void AudioServer::stop(int pl_index) {
    playlist[pl_index].stop();
}

void AudioServer::removeFromPlaylist(const QString& fileName) {
    auto it = playlistInfo.find(fileName);
    if(it != playlistInfo.end()) {
        playlistInfo.erase(fileName);
        playlist.erase(playlist.begin() + it->second);
    }
}

int AudioServer::getPlaylistIndex(const QString& fileName) {
    int index = 0;
    auto it = playlistInfo.find(fileName);
    if(it != playlistInfo.end()) {
        index = it->second;
    }
    return index;
}

AudioServer::AudioServer() {
	const QAudioDeviceInfo &device = QAudioDeviceInfo::defaultOutputDevice();
	const QAudioFormat &audioFormat = device.preferredFormat();

	mixer = new QMixerStream(audioFormat);
	output = new QAudioOutput(device, audioFormat);
	output->setVolume(0.5);
	output->start(mixer);

}

AudioServer& AudioServer::instance() {
	static AudioServer instance;
	return instance;
}
