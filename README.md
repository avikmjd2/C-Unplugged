🎵 C-Unplugged

**Complie Command:**  gcc main.c audio.c song.c global.c doc.c libplay.c -o C-Unplugged.exe


ATTENTION: Make sure to use commands the C-Unplugged is in the same folder as the audiofiles.

A command-line music player and management system written entirely in C. C-Unplugged provides a simple, fast, and lightweight interface for managing your song library, creating custom playlists, and handling audio playback.

✨ Features

Core Audio Playback: Play, pause, resume, stop, and skip tracks.

Song Library: Add, delete, and list all songs from a central songs.csv database.

Playlist Management:

Create new playlists.

Add songs to any playlist.

Delete entire playlists.

Delete specific songs from a playlist.

Persistent Storage: Playlists are saved to a binary file (playlist.dat) and the song library is loaded from songs.csv.

User-Friendly CLI: A colored, interactive prompt that shows the current user.

Command Logging: All commands are logged to log.txt for history and debugging.

🚀 Getting Started

Prerequisites

A C compiler (like gcc)

The make build tool (optional, but recommended)

Any audio libraries required by audio.h and libplay.h (e.g., SDL_mixer, BASS, fmod, etc.). You will need to link these.

Building the Project

Clone the repository:

git clone https://github.com/avikmjd2/C-Unplugged
cd c-unplugged


If a Makefile is provided:

make


Usage

Run the compiled executable from your terminal:

./unplugged


You will be greeted by the C-Unplugged prompt. Type help to see a list of commands.

Enter User: user_name
user_name@C-Unplugged: help


📖 Command Reference

Here are all the available commands and their descriptions.

Core Commands

Command

Description

help

Displays the full help menu.

user [name]

Changes the username shown in the prompt.

quit

Exits the C-Unplugged application.

log

All commands are automatically logged in log.txt.

Playback Controls

Command

Description

play [song_name]

Plays a song from the main library.

play playlist [name]

Loads and plays all songs from the specified playlist.

pause

Pauses the currently playing audio.

resume

Resumes the paused audio.

stop

Stops playback completely.

next

Plays the next song in the current queue.

previous

Plays the previous song in the current queue.

progress

Shows the playback progress of the current song.

Main Song Library

Command

Description

add

Starts an interactive prompt to add a new song to the main library.

delete [song_name]

Deletes a song from the main library (songs.csv).

list

Lists all songs in the main library.

Playlist Management

Command

Description

create [name]

Creates a new, empty playlist.

addlist [name]

Prompts for a song name to add to the specified playlist.

list album

Lists all available playlists.

list [name]

Lists all songs inside a specific playlist.

delete playlist [name]

Deletes an entire playlist and all its song entries.

delete playlist [name] song [song_name]

Deletes a single song from a specific playlist.

Other Commands

Command

Description

goto [path]

Sets the working directory for the playcd command (e.g., C:\Music\).

playcd [filename]

Plays a file directly from the goto path (appends .mp3).

test

A diagnostic command to check duration and timestamps.

📁 File Structure

main.c: Main application entry point and command parser.

playlist.h / .c: Contains functions for managing playlist.dat.

song.h / .c: Contains functions for managing the songs.csv library.

audio.h / .c: Wrapper for the core audio playback functions.

libplay.h / .c: Low-level audio library implementation (e.g., fmod, BASS).

structures.h: Holds the struct definitions for Song, PlaylistEntry, etc.

songs.csv: The main database of all songs (Comma-Separated Values).

playlist.dat: A binary file that stores all user-created playlists and their songs.

log.txt: A plain text file that logs all commands entered by the user.

⚖️ License

This project is licensed under the MIT License - see the LICENSE.md file for details.
