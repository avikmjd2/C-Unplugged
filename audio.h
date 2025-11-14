#ifndef AUDIO_H
#define AUDIO_H

#include "miniaudio.h"


void waitForEnter();
void stop();

int playSong(char *pAudioFile);
void init();
void uninit();
int pause();
int resume();
extern ma_engine g_audio_engine;
extern ma_engine engine;
extern ma_result result;
float duration();
float currentTS();
#endif