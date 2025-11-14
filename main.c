#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "structures.h"
#include "playlist.h"
#include "song.h"
#include "audio.h"
#include "global.h"
#include "doc.h"
#include "libplay.h"

int main()
{    
    welcome();
    char name[200];

    char query[10];
    char command[100];
    // init();
    char *filename = "log.txt";
    
    User user;
    strcpy(user.name, "Test User");
    char *GREEN = "\033[1;32m";
    char *WHITE = "\033[0m";
    char* RED = "\033[1;31m";
    char path[200] = "";
    printf("%sEnter User:  %s",RED,WHITE);
    int playback=0;

    // 1. Read the user's input into the 'path' buffer
    if (fgets(path, sizeof(path), stdin)) {
        
        char* token = strtok(path, "\n\r"); 
        
        if (token) {
            strcpy(user.name, token);
        } else {
            strcpy(user.name, ""); 
        }
    }
    
    path[0] = '\0'; 

    headerLib = loadAllSong("songs.csv");
    FILE *file_ptr = fopen(filename,"a+");
    

    while(1)
    {   
        
        printf("%s%s@C-Unplugged:  %s",GREEN,user.name,WHITE);
        printf("",WHITE);
        // scanf("%s",query);
        
        if (fgets(command, sizeof(command), stdin) == NULL)
        continue;
        
        fprintf(file_ptr, "%s logged %s",user.name,command);
        fflush(file_ptr);
        char* query = strtok(command, " \n\r");


        if(query==NULL)
        continue;


        else if(strcmp(query,"delete")==0)
        {

            char* name = strtok(NULL, " \n\r");
            if(strcmp(name,"playlist")==0||strcmp(name,"album")==0)
            {
                char* albumname = strtok(NULL, " \n\r");
                char* next = strtok(NULL, " \n\r");
                if(next != NULL&&strcmp(next,"song")==0)
                {
                    char* s_name = strtok(NULL, " \n\r");
                    delete_song_from_playlist(albumname,s_name);

                }
                else{
                    delete_playlist(albumname);
                }
            }
            else
            deleteSong(name);
        }
        else if(strcmp(query,"addlist")==0)
        {
            char* playlist = strtok(NULL, " \n\r");
            
            printf("%sEnter Song Name to be added:  %s",RED,WHITE);
            char line[200];
            fgets(line, sizeof(line),stdin);
            char* name = strtok(line, " \n\r");
            add_song_to_playlist(playlist,name);


        }
        else if(strcmp(query,"add")==0)
        {
            char name[200];
            char singer[200];
            char date[50];
            char path[500];
            char lyrics[20000];
            int dur;

            char line[20000]; 
            char* token;

            printf("%sEnter Song Name:  %s",RED,WHITE);
            if (fgets(line, sizeof(line), stdin)) {
                token = strtok(line, "\n\r");
                if (token) strcpy(name, token); 
                else strcpy(name, ""); 
            }

            printf("%sEnter Singer Name:  %s",RED,WHITE);
            if (fgets(line, sizeof(line), stdin)) {
                token = strtok(line, "\n\r");
                if (token) strcpy(singer, token);
                else strcpy(singer, "");
            }

            printf("%sEnter Song date:  %s",RED,WHITE);
            if (fgets(line, sizeof(line), stdin)) {
                token = strtok(line, "\n\r");
                if (token) strcpy(date, token); 
                else strcpy(date, "");
            }


            printf("%sEnter File Path:  %s",RED,WHITE);
            if (fgets(line, sizeof(line), stdin)) {
                token = strtok(line, "\n\r");
                if (token) strcpy(path, token);
                else strcpy(path, "");
            }


            printf("%sEnter lyrics:  %s",RED,WHITE);
            if (fgets(line, sizeof(line), stdin)) {
                token = strtok(line, "\n\r");
                if (token) strcpy(lyrics, token);
                else strcpy(lyrics, "");
            }

            printf("%sEnter Song Duration in minutes  %s",RED,WHITE);
            if (fgets(line, sizeof(line), stdin)) {
                token = strtok(line, "\n\r");
                if (token) dur = atoi(token); 
                else dur = 0;
            }

            addSong(name, singer, date, path, lyrics, dur);         
            
        }
        else if(strcmp(query,"playcd")==0)
        {
            char* name = strtok(NULL, " \n\r");
            char pathtemp[500];
            strcpy(pathtemp, path);
            strcat(pathtemp, name);
            strcat(pathtemp, ".mp3");
            playSong(pathtemp);
        }
        else if(strcmp(query,"play")==0)
        {
            char* songname = strtok(NULL, " \n\r");
            if(strcmp(songname,"playlist")==0)
            {
                char* playlistname = strtok(NULL, " \n\r");
                if(playlistname==NULL)
                printf("INVALID PLAYLIST NAME\n",RED,WHITE);
                else
                loadPlaylist(playlistname);
            }
            else
            {
                Song* song = findSong(songname,headerLib);
                // printf("Song name: %s\n",song->name);
                // printf("Song singer: %s\n",song->singer);
                // printf("Song date: %s\n",song->date);
                // printf("Song filepa: %s\n",song->file_path);
                // printf("Song lyrics: %s\n",song->file_path);
                // printf("Song dur: %d\n",song->duration);
                if(song!=NULL)
                playSong(song->file_path);
                else
                printf("INVALID SONG NAME\n",RED,WHITE);

            }
        }
        else if(strcmp(query,"create")==0)
        {
            char* playListName = strtok(NULL, " \n\r");
            createPlayList(playListName);
        }

        else if(strcmp(query,"previous")==0)
        {
            prev();
        }
        
        else if(strcmp(query,"stop")==0)
        {
            // uninit();
            // init();
            setpointertonull();
            stop();
        }
        else if(strcmp(query,"goto")==0)
        {
            char* pathname = strtok(NULL, "\n");
            pathname = strcat(pathname,"\\");
            strcpy(path,pathname);


        }

        else if(strcmp(query,"user")==0)
        {
            char* username = strtok(NULL, "\n");
            strcpy(user.name,username);


        }

        else if(strcmp(query,"help")==0)
        {
            help();

        }

        else if(strcmp(query,"test")==0)
        {
            // printf("%s",headerLib->point->name);
            printf("%f\n",duration());
            printf("%f\n",currentTS());

        }
        
        else if(strcmp(query,"list")==0)
        {
            // printf("ENTEREDDDDD the first\n",GREEN,WHITE);
            char* albumname = strtok(NULL, "\n");
            // printf("ENTEREDDDDD the second\n",GREEN,WHITE);
            // printf("%s\n",albumname);

            if(albumname==NULL)
            {
                printf("The List Of Song is \n",GREEN,WHITE);
                liblist();
                continue;
            }

            else if(strcmp(albumname,"album")==0)
            listplay();
            else if(albumname!=NULL)
            list(albumname);
            else
            {
                printf("The List Of Song is \n",GREEN,WHITE);
                liblist();
            }


        }
        
        

        else if(strcmp(query,"next")==0)
        next();


        else if(strcmp(query,"progress")==0)
        prog();


        else if(strcmp(query,"quit")==0)
        exit(0);

        else if(strcmp(query,"pause")==0)
        {
            int flag = pause();
            if(flag==1)
            printf("%sNO AUDIO PLAYING. %s\n",RED,WHITE);            

        }

        else if(strcmp(query,"resume")==0)
        {
            int flag = resume();
            if(flag==1)
            printf("%sNO AUDIO PLAYING. %s\n",RED,WHITE);            

        }

        else
        {
            printf("%sCOMMAND NOT FOUND. Type help for more info. %s\n",RED,WHITE);
            continue;
        }
    }
    uninit();
    fclose(file_ptr);
}

