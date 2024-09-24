/*
 * AudioServer.h
 *
 *  Created on: 25 feb 2024
 *      Author: andrea
 */

#ifndef SRC_AUDIO_SERVER_AUDIOSERVER_H_
#define SRC_AUDIO_SERVER_AUDIOSERVER_H_

#include <iostream>

class AudioServer {
public:
	virtual ~AudioServer();

	static AudioServer& instance();

	void play(const std::string file);

private:
	AudioServer();

};


#endif /* SRC_AUDIO_SERVER_AUDIOSERVER_H_ */
