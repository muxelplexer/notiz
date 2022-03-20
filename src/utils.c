#include "notiz/utils.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <ctype.h>

static const char FILE_NAME[] = "notes";
static const char FILE_DIR[]  = "/notiz/";


char* GetDataPath()
{
    const char* XDG_DATA_HOME = getenv("XDG_DATA_HOME");
    char* dataPath = "";
    if (XDG_DATA_HOME != NULL)
    {
        size_t xdg_len = strlen(XDG_DATA_HOME);

        size_t maxLen = xdg_len + 1;
        maxLen += strlen(FILE_DIR);
        maxLen += strlen(FILE_NAME);

        dataPath = (char*) malloc(maxLen + 1);
        strcpy(dataPath, XDG_DATA_HOME);
        if (XDG_DATA_HOME[xdg_len - 1] == '/')
            strcat(dataPath, &FILE_DIR[1]);
        else
            strcat(dataPath, FILE_DIR);

    } else
    {
        const char* HOME = getenv("HOME");
        const char* subDir = "/.local/share";

        size_t home_len = strlen(HOME);

        size_t maxLen = home_len + 1;
        maxLen += strlen(subDir);
        maxLen += strlen(FILE_NAME);
        maxLen += strlen(FILE_DIR);

        dataPath = (char*) malloc(maxLen + 1);
        strcpy(dataPath, HOME);
        strcat(dataPath, subDir);
        strcat(dataPath, FILE_DIR);
    }
    return dataPath;
}

char* GetFilePath()
{
    char* dataPath = GetDataPath();
    char* filePath = malloc(strlen(dataPath) + strlen(FILE_NAME));

    strcpy(filePath, dataPath);
    free(dataPath);

    strcat(filePath, FILE_NAME);
    return filePath;
}

int GetNoteCount()
{
    char* filePath = GetFilePath();
    FILE* noteFile = fopen(filePath, "r");

    if (noteFile == NULL)
    {
        free(filePath);
        return 0;
    }

    char line[MAX_NOTE_LENGTH];
    int i = 0;
    while (fgets(line, sizeof(line), noteFile))
    {
        i++;
    }

    fclose(noteFile);
    free(filePath);
    return i;
}

int parseIDS(int* ids, char* args)
{
    size_t len = strlen(args);
    int ids_cnt = 0;

    char numbuf[2048];
    numbuf[0] = '\0';
    int nbCnt = 0;

    for(size_t i = 0; i < len; i++)
    {
        if(isdigit(args[i]))
        {
            numbuf[nbCnt] = args[i];
            nbCnt++;
        }
        if(args[i] == ',')
        {
            numbuf[nbCnt + 1] = '\0';
            ids[ids_cnt] = atoi(numbuf);
            ids_cnt++;
            nbCnt = 0;
            numbuf[0] = '\0';
        }
    }
    if (numbuf[0] != '\0')
    {
        ids[ids_cnt] = atoi(numbuf);
        ids_cnt++;
    }
    return ids_cnt;
}

int* allocIDs()
{
    int maxSize = GetNoteCount();
    
    return (int*)malloc(maxSize * sizeof(int));
}