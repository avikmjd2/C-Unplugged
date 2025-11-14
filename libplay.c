#include "libplay.h"
#include "global.h"
#include "structures.h"
#include <stdio.h>
#include "audio.h"
#include "song.h"
#include "doc.h"
#include<string.h>
#include <stdlib.h>


char *WHITE = "\033[0m";
char* BLUE = "\033[1;34m";
void liblist()
{
    Lib* temp;
    temp = headerLib;
    while(temp!=NULL)
    {
        printf("%s\n",temp->point->name);
        temp = temp->next;
    }
}


void list(char* targetPlaylistName)
{
    FILE* file = fopen("playlist.dat", "rb");
    struct PlaylistEntry entry;
    int k=0;
    // int songCount = 0;

    while (fread(&entry, sizeof(struct PlaylistEntry), 1, file) == 1) 
    {
        
        if (strcmp(entry.playlistName, targetPlaylistName) == 0) {
            k=1;
            
            printf("->%s%s%s\n",BLUE,entry.songName,WHITE);
        }
    }
    fclose(file);
    if(k==0)
    printf("%s%s%s\n",BLUE,"PLAYLIST NOT FOUND",WHITE);

}


void listplay()
{
    FILE* file = fopen("playlist.dat", "rb");
    struct PlaylistEntry entry;
    char name[200];
    name[0]='\0';
    while (fread(&entry, sizeof(struct PlaylistEntry), 1, file) == 1) 
    {
        if(strcmp(name,entry.playlistName)==0)
        continue;
        else
        printf("%s%s%s\n",BLUE,entry.playlistName,WHITE);
        strcpy(name, entry.playlistName);
    }
    fclose(file);
}

void next()
{
    if(playlistHead!=NULL)
    {
        if(currentSong->next!=NULL)
        {
            currentSong = currentSong->next;
            playSong(currentSong->ptr->file_path);
        }
    }
    // else
    // {
    //     playSong()
    // }
}

void prev()
{
    if(playlistHead!=NULL)
    {
        if(currentSong->prev!=NULL)
        {
            currentSong = currentSong->prev;
            playSong(currentSong->ptr->file_path);
        }
    }
    // else
    // {
    //     playSong()
    // }
}

void loadPlaylist(char* targetPlaylistName)
{
    free_list_playlist(playlistHead);
    playlistHead = NULL;
    playlistTail= NULL;
    currentSong = NULL;
    FILE* file = fopen("playlist.dat", "rb");
    struct PlaylistEntry entry;
    int songCount = 0;
    RootSong* temp=NULL;

    while (fread(&entry, sizeof(struct PlaylistEntry), 1, file) == 1) {
        
        if (strcmp(entry.playlistName, targetPlaylistName) == 0) {
            
            // printf("  -> %s\n", entry.songName);
            Song* song;
            song = findSong(entry.songName,headerLib);
            // printf("%s\n",song->file_path);

            RootSong* new_node = malloc(sizeof(RootSong));
            new_node->ptr = song;
            new_node->next = NULL;
            new_node->prev = temp;

            if (playlistHead == NULL) {
                playlistHead = new_node;
                playlistTail = new_node;
            } 
            else {
                playlistTail->next = new_node;
                playlistTail = new_node;
            }
            new_node->next = playlistHead;
            playlistHead->prev = new_node;
            temp = new_node;

            
            songCount++;
        }
    }


    if (playlistHead != NULL) 
    {
        // printf("Good to go");
        currentSong = playlistHead;
        playSong(playlistHead->ptr->file_path);
    } 
    else
    printf("Playlist '%s' not found or is empty.\n", targetPlaylistName);


    fclose(file);
}

int check_playlist_exists(const char* playlistName) {
    FILE* file = fopen("playlist.dat", "rb");
    if (file == NULL) {
        return 0; // File doesn't exist, so playlist can't exist
    }

    struct PlaylistEntry entry;
    int found = 0;

    // Read every entry in the file
    while (fread(&entry, sizeof(struct PlaylistEntry), 1, file) == 1) {
        if (strcmp(entry.playlistName, playlistName) == 0) {
            found = 1; // We found at least one song for this playlist
            break;     // No need to search anymore
        }
    }

    fclose(file);
    return found; // 1 if found, 0 if not
}

void add_song_to_playlist(const char* playlistName, const char* songName) {
    
    // Open in "append binary" mode (adds to the end of the file)
    FILE* file = fopen("playlist.dat", "ab");
    if (file == NULL) {
        printf("Error: Could not open playlist.dat for writing.\n");
        return;
    }

    struct PlaylistEntry newEntry;
    
    // Safely copy the names into the struct
    strncpy(newEntry.playlistName, playlistName, MAX_PLAYLIST_NAME - 1);
    strncpy(newEntry.songName, songName, MAX_SONG_NAME - 1);
    
    // Ensure null-termination
    newEntry.playlistName[MAX_PLAYLIST_NAME - 1] = '\0';
    newEntry.songName[MAX_SONG_NAME - 1] = '\0';

    // Write the new entry to the end of the file
    fwrite(&newEntry, sizeof(struct PlaylistEntry), 1, file);
    fclose(file);
}





void createPlayList(char* targetPlaylistName) 
{
    if (check_playlist_exists(targetPlaylistName)) {
        
        // 2. If it exists, print an error and stop.
        printf("Error: Playlist '%s' already exists.\n", targetPlaylistName);
        printf("To add a song to it, use 'add song' instead.\n");
    
    } 
    else 
    {
        
        // 3. If it doesn't exist, prompt for the first song.
        char firstSongName[MAX_SONG_NAME];
        printf("Creating new playlist '%s'...\n", targetPlaylistName);
        printf("Please enter the name of the first song to add: ");
        
        if (fgets(firstSongName, sizeof(firstSongName), stdin) == NULL) {
            printf("Error reading song name.\n");
            return;
        }
        
        firstSongName[strcspn(firstSongName, "\n")] = 0;

        if (firstSongName[0] == '\0') {
            printf("Playlist creation cancelled. A playlist must have at least one song.\n");
            return;
        }

        // 4. Add the first song.
        //    This officially "creates" the playlist in the file.
        add_song_to_playlist(targetPlaylistName, firstSongName);
        printf("Added '%s' as the first song.\n", firstSongName);
    }
}


void setpointertonull()
{
    playlistHead = NULL;
    playlistTail = NULL;
}





void delete_song_from_playlist(char* playlistName, char* songName) {
    
    FILE* originalFile = fopen("playlist.dat", "rb");
    if (originalFile == NULL) {
        printf("Info: playlist.dat not found. Nothing to delete.\n");
        return;
    }

    FILE* tempFile = fopen("playlist.tmp", "wb");
    if (tempFile == NULL) {
        printf("Error: Could not create temporary file.\n");
        fclose(originalFile); // Close the file we successfully opened
        return;
    }

    struct PlaylistEntry currentEntry;
    int itemsDeleted = 0;

    while (fread(&currentEntry, sizeof(struct PlaylistEntry), 1, originalFile) == 1) {
        
    
        if (strcmp(currentEntry.playlistName, playlistName) == 0 &&
            strcmp(currentEntry.songName, songName) == 0) {
            
            itemsDeleted++;

        } else {
            fwrite(&currentEntry, sizeof(struct PlaylistEntry), 1, tempFile);
        }
    }

    fclose(originalFile);
    fclose(tempFile);


    if (remove("playlist.dat") != 0) {
        printf("Error: Could not delete the original playlist.dat.\n");
        return;
    }

    if (rename("playlist.tmp", "playlist.dat") != 0) {
        printf("Error: Could not rename playlist.tmp to playlist.dat.\n");
        return;
    }

    if (itemsDeleted > 0) {
        printf("Successfully deleted %d instance(s) of '%s' from '%s'.\n", itemsDeleted, songName, playlistName);
    } else {
        printf("Song '%s' was not found in playlist '%s'.\n", songName, playlistName);
    }
}




void delete_playlist(char* playlistName) {
    
    FILE* originalFile = fopen("playlist.dat", "rb");
    if (originalFile == NULL) {
        printf("Info: playlist.dat not found. Nothing to delete.\n");
        return;
    }

    FILE* tempFile = fopen("playlist.tmp", "wb");
    if (tempFile == NULL) {
        printf("Error: Could not create temporary file.\n");
        fclose(originalFile);
        return;
    }

    struct PlaylistEntry currentEntry;
    int songsRemoved = 0;

    while (fread(&currentEntry, sizeof(struct PlaylistEntry), 1, originalFile) == 1) {
        

        if (strcmp(currentEntry.playlistName, playlistName) == 0) {
            

            songsRemoved++;

        } else {
        
            fwrite(&currentEntry, sizeof(struct PlaylistEntry), 1, tempFile);
        }
    }


    fclose(originalFile);
    fclose(tempFile);


    if (remove("playlist.dat") != 0) {
        printf("Error: Could not delete the original playlist.dat.\n");
        return;
    }

    if (rename("playlist.tmp", "playlist.dat") != 0) {
        printf("Error: Could not rename playlist.tmp to playlist.dat.\n");
        return;
    }

    if (songsRemoved > 0) {
        printf("Successfully deleted playlist '%s' (removed %d song entries).\n", playlistName, songsRemoved);
    } else {
        printf("Playlist '%s' was not found.\n", playlistName);
    }
}