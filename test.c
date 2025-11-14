#include <stdio.h>

// 1. Define this in ONE .c file (this one) before including the header
#define MINIAUDIO_IMPLEMENTATION
#define MA_ENABLE_MP3
#include "miniaudio.h" // 2. Include the header file

// A simple function to wait for the user to press Enter
void waitForEnter() {
    printf("Press Enter to quit...\n");
    getchar();
}

int main() {
    ma_result result;
    ma_engine engine;
    
    // --- IMPORTANT ---
    // Change this to the path of a .wav file you have!
    const char* pAudioFile = "song.mp3"; 
    
    // 3. Initialize the Audio Engine
    result = ma_engine_init(NULL, &engine);
    if (result != MA_SUCCESS) {
        printf("Failed to initialize audio engine.\n");
        return -1;
    }

    printf("Engine initialized. Playing '%s'...\n", pAudioFile);

    // 4. Play the sound
    result = ma_engine_play_sound(&engine, pAudioFile, NULL);
    if (result != MA_SUCCESS) {
        printf("Error: Could not load or play file: %s\n", pAudioFile);
        ma_engine_uninit(&engine); // Clean up the engine
        return -1;
    }

    // 5. Wait for the user to quit
    // (This also gives the sound time to play)
    waitForEnter();

    // 6. Clean up
    ma_engine_uninit(&engine);
    printf("Engine cleaned up. Exiting.\n");

    return 0;
}     