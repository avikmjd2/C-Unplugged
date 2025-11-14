#ifndef STRUCTURES_H
#define STRUCTURES_H
#define MAX_PLAYLIST_NAME 100
#define MAX_SONG_NAME 256


typedef struct Song
{
    char name[200];
    char singer[200];
    char date[20];
    char file_path[500];
    char lyrics[20000];
    int duration;
}Song;

typedef struct RootSong
{
    Song* ptr;
    struct RootSong* prev;
    struct RootSong* next;
}RootSong;


typedef struct Playlist
{
    int sr;
    char name[200];
    char file_path[500];
    Song* RootSong;
    struct Playlist* next;
    char author[200];

}Playlist;


// typedef struct Library
// {  
//     Song* song;
//     struct Library* next;

// }Library;


typedef struct User
{
    char name[200];
    int pwd;
}User;


typedef struct Lib
{
    Song* point;
    struct Lib* next;
}Lib;


typedef struct PlaylistEntry {
    char playlistName[MAX_PLAYLIST_NAME];
    char songName[MAX_SONG_NAME];
}PlaylistEntry;



#endif
