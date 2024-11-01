/*
 * AudioServer.cpp
 *
 *  Created on: 25 feb 2024
 *      Author: andrea
 */

#include "AudioServer.h"


#include <QAudioDeviceInfo>
#include <QAudioOutput>
#include <persistence.h>

AudioServer::~AudioServer() {
	// TODO Auto-generated destructor stub
}

int AudioServer::addFx(const QString& fileName) {
    int current_index = 0;
    auto it = fxPlaylistInfo.find(fileName);
    if(it == fxPlaylistInfo.end()) {
        current_index = fxPlaylist.size();
        fxPlaylistInfo[fileName] = current_index;
        QMixerStreamHandle tmp = mixer->openStream(fileName);
        tmp.setLoops(1);
        fxPlaylist.push_back(tmp);
    }
    else
        current_index = it->second;

    return current_index;
}

void AudioServer::playFx(int pl_index) {
	if (not (pl_index < fxPlaylist.size())){
		qWarning() << "Play list index " << pl_index <<
				" not valid (playlist size: " << fxPlaylist.size() << ")";
		return;
	}
	if(soundsEnable){
		QMixerStreamHandle handle = fxPlaylist[pl_index];
		if(handle.state()==QtMixer::Playing)
			handle.stop();

		handle.play();
	}
}

void AudioServer::stopFx(int pl_index) {
	if (not (pl_index < fxPlaylist.size())){
			qWarning() << "Play list index " << pl_index <<
					" not valid (playlist size: " << fxPlaylist.size() << ")";
			return;
		}
    fxPlaylist[pl_index].stop();
}

void AudioServer::removeFx(const QString& fileName) {
    auto it = fxPlaylistInfo.find(fileName);
    if(it != fxPlaylistInfo.end()) {
    	auto fx = fxPlaylist.at(it->second);
    	fx.stop();
    	mixer->closeStream(fx);
        fxPlaylistInfo.erase(fileName);
        fxPlaylist.erase(fxPlaylist.begin() + it->second);
    }
}

void AudioServer::setMusicScore(const QString& fileName) {
	if(currentMusicScore == fileName)
		return;

	if(currentMusicScore != ""){
		musicScore.stop();
		mixer->closeStream(musicScore);
	}
	currentMusicScore = fileName;
	musicScore = mixer->openStream(fileName);
	musicScore.setLoops(-1);
	if(musicEnable)
		musicScore.play();

	return;
}

int AudioServer::getFxIndex(const QString& fileName) {
    int index = -1; //a valid index should be non negative
    auto it = fxPlaylistInfo.find(fileName);
    if(it != fxPlaylistInfo.end()) {
        index = it->second;
    }
    return index;
}

void AudioServer::enableSounds(bool en) {
	if(en == false){
		for(auto it: fxPlaylist){
			it.stop();
		}
	}
	soundsEnable = en;
}

void AudioServer::enableMusic(bool en) {
	musicEnable = en;
	if(currentMusicScore == "")
		return;
	if(en)
		musicScore.play();
	else
		musicScore.stop();
}

void AudioServer::setVolume(unsigned int v) {
	volume = v;
	qreal lv = QAudio::convertVolume(v / qreal(10.0),
			QAudio::LogarithmicVolumeScale,
			QAudio::LinearVolumeScale);
	output->setVolume(lv);
}


AudioServer::AudioServer() {
	const QAudioDeviceInfo &device = QAudioDeviceInfo::defaultOutputDevice();
	const QAudioFormat &audioFormat = device.preferredFormat();

	mixer = new QMixerStream(audioFormat);
	output = new QAudioOutput(device, audioFormat);

	//load from config
	auto sound_cfg = Persistence::instance().getConfigurationItem("sound");
	int vol = sound_cfg.value("volume").toInt(5);
	qDebug() << "volume is " << vol;
	soundsEnable = sound_cfg.value("soundfx").toBool(true);
	musicEnable = sound_cfg.value("music").toBool(true);
	setVolume(vol);
	output->start(mixer);

}

AudioServer& AudioServer::instance() {
	static AudioServer instance;
	return instance;
}
