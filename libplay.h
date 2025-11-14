void liblist();
void list(char* name);
void listplay();
void next();
void prev();
void loadPlaylist(char* targetPlaylistName);
void createPlayList(char* targetPlaylistName);
void add_song_to_playlist(const char* playlistName, const char* songName);
void setpointertonull();

void delete_song_from_playlist(char* playlistName, char* songName);
void delete_playlist(char* playlistName);