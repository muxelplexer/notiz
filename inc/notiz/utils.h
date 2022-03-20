#ifndef UTILS_H
#define UTILS_H

#define MAX_NOTE_LENGTH 4069
/*
    Needs to be free()'d
*/
char* GetDataPath();
char* GetFilePath();

int GetNoteCount();

int parseIDS(int* ids, char* args);

int* allocIDs();

#endif
