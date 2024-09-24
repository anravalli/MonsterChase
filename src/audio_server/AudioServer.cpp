/*
 * AudioServer.cpp
 *
 *  Created on: 25 feb 2024
 *      Author: andrea
 */

#include "AudioServer.h"


#include <QAudioDeviceInfo>
#include <QAudioOutput>

#include "QMixerStream.h"

AudioServer::~AudioServer() {
	// TODO Auto-generated destructor stub
}

void AudioServer::play(const std::string file) {
	main_theme = mixer->openStream("../resources/MainTheme.wav");
	main_theme.setLoops(-1);
	main_theme.play();
}

AudioServer::AudioServer() {
	const QAudioDeviceInfo &device = QAudioDeviceInfo::defaultOutputDevice();
	const QAudioFormat &audioFormat = device.preferredFormat();

	QMixerStream mixer(audioFormat);
	QAudioOutput output(device, audioFormat);
	output.setVolume(0.5);
	output.start(&mixer);

}

AudioServer& AudioServer::instance() {
	static AudioServer instance;
	return instance;
}
