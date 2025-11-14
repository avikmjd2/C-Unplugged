#include <stdio.h>
#define MINIAUDIO_IMPLEMENTATION
#define MA_ENABLE_MP3
#define DR_MP3_IMPLEMENTATION  
#include "miniaudio.h"
#include "audio.h"
#include "song.h"
#include "libplay.h"
#include "global.h"
#include "doc.h"
ma_engine g_audio_engine;
ma_engine engine;
ma_result result;
ma_sound sound;
ma_bool32 isSoundInitialized = MA_FALSE;
ma_bool32 isRunning = MA_FALSE;
ma_decoder decoder;

void finished(){
    printf("Playlist Finished\n");
    // next();
}


void init()
{
    result = ma_engine_init(NULL, &engine);
    // result = ma_decoder_init_file(NULL,NULL, &decoder);
}

void uninit()
{
    ma_engine_uninit(&engine);
    ma_decoder_uninit(&decoder);
    // printf("Engine cleaned up. Exiting.\n");
}
int playSong(char* pAudioFile) {

    // ma_engine_uninit(&engine);
    // uninit();
    
    // printf("Engine cleaned up. Exiting.\n");
    // ma_engine engine;
    // ma_result result;
    if(isSoundInitialized==MA_FALSE)
    init();
    else if (isRunning == MA_TRUE) 
    {
        ma_sound_uninit(&sound);
        ma_decoder_uninit(&decoder);
        // isSoundInitialized = MA_FALSE;
    }


    
    // result = ma_engine_init(NULL, &engine);
    result = ma_decoder_init_file(pAudioFile, NULL, &decoder);
    if (result != MA_SUCCESS) {
        printf("Error: ma_decoder_init_file FAILED. Reason: %s\n", ma_result_description(result));
        printf("Check that '%s' exists and that MP3 support is enabled.\n", pAudioFile);
        return -1; 
    }
    // printf("Error: ma_decoder_init_file failed. Reason: %s\n", ma_result_description(result));
    
    ma_sound_config config = ma_sound_config_init();
    config.endCallback = finished;
    config.pDataSource = &decoder; //


    // 4. Play the sound

    // result = ma_engine_play_sound(&engine, pAudioFile, NULL);

    // result = ma_sound_init_from_file(&engine, pAudioFile, 0, NULL, &config, &sound);
    // printf("The file path is %s which is valid\n", pAudioFile);

    result = ma_sound_init_ex(&engine, &config, &sound);
    // printf("%s",result);
    if (result != MA_SUCCESS) {
        printf("Error: Could not init sound_ex\n");
        printf("Error: ma_sound_init_ex failed. Reason: %s\n", ma_result_description(result));
        ma_decoder_uninit(&decoder); 
        return -1;
    }
    // printf("[AUDIO] playSong using engine: %p\n", (vo    id*)&engine);
    printf("playing %s\n",pAudioFile);
    ma_sound_start(&sound);
    isSoundInitialized = MA_TRUE;
    isRunning = MA_TRUE;

    if (result != MA_SUCCESS) {
        printf("Error: Could not load or play file: %s\n", pAudioFile);
        return -1;
    }

    // waitForEnter();

    // // 6. Clean up
    // ma_engine_uninit(&engine);
    // printf("Engine cleaned up. Exiting.\n");
    

    return 0;
}  

void stop()
{
    // ma_sound_stop(&sound);
    uninit();
    isRunning = MA_FALSE;
    isSoundInitialized = MA_FALSE;
    free_list_playlist(playlistHead);
    playlistHead = NULL;
    playlistTail = NULL;

}



int pause()
{
    if(isSoundInitialized==MA_TRUE&&isRunning==MA_TRUE)
    {
        ma_sound_stop(&sound);
        return(0);
    }
    else 
    return(1);
}

int resume()
{
    if(isSoundInitialized==MA_TRUE&&isRunning==MA_TRUE)
    {
        ma_sound_start(&sound);
        return(0);
    }
    else 
    return(1);
}

float duration()
{

    ma_result resultA;
    float durationInSeconds = 0.0f;
    resultA = ma_sound_get_length_in_seconds(&sound, &durationInSeconds);

    if (resultA != MA_SUCCESS) 
    {
        fprintf(stderr, "SONG NOT PLAYED.\n");
        return -1.0f;
    }
    return durationInSeconds;
}

float currentTS()
{
    float time = 0.0f;
    ma_result ans = ma_sound_get_cursor_in_seconds(&sound, &time);

    if (ans != MA_SUCCESS) 
    {
        fprintf(stderr, "SONG NOT PLAYED.\n");
        return -1.0f;
    }
    return(time);

}