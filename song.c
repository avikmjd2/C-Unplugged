#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "audio.h"
#include "structures.h"
#include "global.h"


#ifndef strsep
char* strsep(char** stringp, const char* delim) {
    if (*stringp == NULL) {
        return NULL;
    }
    char* start = *stringp;
    char* p = start;
    while (*p != '\0') {
        const char* d = delim;
        while (*d != '\0') {
            if (*p == *d) {
                *p = '\0'; 
                *stringp = p + 1; 
                return start;
            }
            d++;
        }
        p++;
    }
    *stringp = NULL;
    return start;
}
#endif


int addSong(char* name, char* singer, char* date, char* path, char* lyrics, int duration)
{
    FILE* file_pointer = fopen("songs.csv", "a");
    if (file_pointer == NULL)
    {
        return(1);
    }

    fprintf(file_pointer, "%s,%s,%d,%s,%s,%d\n", name, singer, date,path,lyrics,duration);
    fclose(file_pointer);
    Song* ptrsong = (Song*)malloc(sizeof(Song));
    strcpy(ptrsong->name,name);
    strcpy(ptrsong->singer,singer);
    strcpy(ptrsong->date,date);
    strcpy(ptrsong->file_path,path);
    strcpy(ptrsong->lyrics,lyrics);
    ptrsong->duration = duration;

    Lib *new = (Lib*)malloc(sizeof(Lib));
    new->next = NULL;
    new->point = ptrsong;
    tailLib->next = new;
    tailLib = new;


}


int deleteSong(char* name)
{
    char* original_file = "songs.csv";
    char* temp_file = "temp.csv";

    char* data_to_delete = name;
    FILE* f_in = fopen(original_file, "r");
    FILE* f_out = fopen(temp_file, "w");
    if (f_in == NULL || f_out == NULL)
    return(1);

    char line[2000];
    while (fgets(line, sizeof(line), f_in))
    {
        if (strstr(line, data_to_delete) == NULL) 
        {
            fprintf(f_out, "%s", line);
        }
    }
    fclose(f_in);
    fclose(f_out);

    remove(original_file);
    rename(temp_file,original_file);

    return(0);
    


}





Lib* loadAllSong(char* filePath)
{
    FILE* f_in = fopen(filePath, "r");
    Lib* head = NULL;
    Lib* tail = NULL;
    // Lib* temp =head;
    
    char line[1000];
    while (fgets(line, sizeof(line), f_in))
    {
        char* lineptr = line;
        char* val = strsep(&lineptr,",\n\r");
        Song* ptrsong = (Song*)malloc(sizeof(Song));
        strcpy(ptrsong->name,val);
        val = strsep(&lineptr,",\n\r");
        if(val) strcpy(ptrsong->singer,val);
        val = strsep(&lineptr,",\n\r");
        if(val) strcpy(ptrsong->date,val);
        val = strsep(&lineptr,",\n\r");
        if(val) strcpy(ptrsong->file_path,val);
        val = strsep(&lineptr,",\n\r");
        if(val) strcpy(ptrsong->lyrics,val);
        val = strsep(&lineptr,",\n\r");
        if(val) ptrsong->duration = atoi(val);
        
        Lib* new= (Lib*)malloc(sizeof(Lib));
        new->next = NULL;
        new->point = ptrsong;
        if (head == NULL) {
            head = new;
            tail = new;
        } 
        else {
            tail->next = new;
            tail = new;
        }    


        
    }
    fclose(f_in);
    tailLib = tail;
    return(head);

}


Song* findSong(char name[200], Lib* head)
{
    while(head!=NULL)
    {
        if(strcmp(((head->point)->name),name)==0)
        {
            return(head->point);
        }
        else
        head= head->next;

    }
    return(NULL);
}