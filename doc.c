#include <stdio.h>
#include "structures.h"
#include <stdlib.h>
#define CYAN_BOLD   "\033[1;36m"
#define WHITE_BOLD  "\033[1;37m"
#define RESET       "\033[0m"
#include "audio.h"
#include <string.h>


void help()
{
    
    char *WHITE = "\033[0m";
    char* RED = "\033[1;31m";
    char *GREEN = "\033[1;32m"; 

    printf("\n%s--- C-Unplugged Help Menu ---%s\n\n", RED, WHITE);

    // --- Core Commands ---
    printf("%s%s--- Core Commands ---%s\n\n", GREEN, RED, WHITE);
    printf("%shelp%s\n", RED, WHITE);
    printf("\tDisplays this help message.\n\n");

    printf("%suser [new_username]%s\n", RED, WHITE);
    printf("\tChanges the username displayed in the prompt.\n\n");

    printf("%squit%s\n", RED, WHITE);
    printf("\tExits the C-Unplugged application.\n\n");

    // --- Playback Controls ---
    printf("%s%s--- Playback Controls ---%s\n\n", GREEN, RED, WHITE);
    printf("%splay [song_name]%s\n", RED, WHITE);
    printf("\tPlays a song from the main library by its name.\n\n");

    printf("%splay playlist [playlist_name]%s\n", RED, WHITE);
    printf("\tLoads and plays all songs from the specified playlist.\n\n");

    printf("%spause%s\n", RED, WHITE);
    printf("\tPauses the currently playing audio.\n\n");

    printf("%sresume%s\n", RED, WHITE);
    printf("\tResumes the paused audio.\n\n");

    printf("%sstop%s\n", RED, WHITE);
    printf("\tStops the currently playing audio.\n\n");

    printf("%snext%s\n", RED, WHITE);
    printf("\tPlays the next song in the current queue (e.g., playlist).\n\n");
    
    printf("%sprevious%s\n", RED, WHITE);
    printf("\tPlays the previous song in the current queue (e.g., playlist).\n\n");
    
    printf("%sprogress%s\n", RED, WHITE);
    printf("\tDisplays the current progress bar and timestamp of the playing audio.\n\n");

    // --- Main Song Library ---
    printf("%s%s--- Main Song Library ---%s\n\n", GREEN, RED, WHITE);
    printf("%sadd%s\n", RED, WHITE);
    printf("\tFollow the prompts to add a new song to the main library.\n\n");

    printf("%sdelete [song_name]%s\n", RED, WHITE);
    printf("\tDeletes a song from the main library.\n\n");

    printf("%slist%s\n", RED, WHITE);
    printf("\tLists all songs in the main library.\n\n");

    // --- Playlist Management ---
    printf("%s%s--- Playlist Management ---%s\n\n", GREEN, RED, WHITE);
    printf("%screate [playlist_name]%s\n", RED, WHITE);
    printf("\tCreates a new, empty playlist.\n\n");

    printf("%saddlist [playlist_name]%s\n", RED, WHITE);
    printf("\tFollow the prompt to add a song to the specified playlist.\n\n");

    printf("%slist album%s\n", RED, WHITE);
    printf("\tLists all available playlists.\n\n");

    printf("%slist [playlist_name]%s\n", RED, WHITE);
    printf("\tLists all songs within the specified playlist.\n\n");

    printf("%sdelete playlist [playlist_name]%s\n", RED, WHITE);
    printf("\tDeletes an entire playlist. ('album' also works: 'delete album [name]').\n\n");

    printf("%sdelete playlist [playlist_name] song [song_name]%s\n", RED, WHITE);
    printf("\tDeletes a specific song from a specific playlist.\n\n");

    // --- Other Commands ---
    printf("%s%s--- Other Commands ---%s\n\n", GREEN, RED, WHITE);
    printf("%sgoto [directory_path]%s\n", RED, WHITE);
    printf("\tSets the working directory path for 'playcd' (e.g., 'C:\\Music\\').\n\n");

    printf("%splaycd [song_name]%s\n", RED, WHITE);
    printf("\tPlays a song file directly from the 'goto' path (appends .mp3).\n\n");

    printf("%stest%s\n", RED, WHITE);
    printf("\tDiagnostic command to print the current song duration and timestamp.\n\n");

    printf("%sSpecial Note: All the commands are stored in log.txt file for future reference. %s\n\n",RED,WHITE);
}

void free_list_playlist(RootSong* head) {
    if(head==NULL)
    return;
    struct RootSong* current = head;
    struct RootSong* next_node;
    free(current);

    current = head->next;

    while (current != head&&current!=NULL) {
        next_node = current->next;
        free(current);
        current = next_node;
    }
}




void welcome() {
    printf(CYAN_BOLD "****************************************\n");
    printf(CYAN_BOLD "* *\n");
    printf(CYAN_BOLD "* Welcome to C Unplugged!         *\n");
    printf(CYAN_BOLD "* *\n");
    printf(WHITE_BOLD "* It's great to see you.          *\n" RESET);
    printf(CYAN_BOLD "* *\n");
    printf(CYAN_BOLD "* *Created by Avik :)");
    printf(CYAN_BOLD "* *\n");
    printf(CYAN_BOLD "****************************************\n" RESET);
    printf("\nType 'help' for a list of commands.\n\n");
}



void prog()
{
    float total = duration();
    float curr = currentTS();
    if(total<0||curr<0)
    return;
    printf("%f/%f seconds \n",curr,total);
    float fract = curr/total;
    int size = 100; 
    int fill = fract*size;
    char bar[size+3];
    memset(bar, ' ', size+3);
    bar[0] = '[';
    bar[size+2] = '\0';
    bar[size+1] = ']';

    for (int i = 1; i <= fill; i++) 
    {
        bar[i] = '#';
    }
    printf("%s",bar);
    printf("\n\n");

}