#include "termNote/commands.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>

static const char FILE_NAME[] = "notes";
static const char FILE_DIR[]  = "/termNote/";

char* GetDataPath()
{
    const char* XDG_DATA_HOME = getenv("XDG_DATA_HOME");
    char* dataPath;
    if (XDG_DATA_HOME != NULL)
    {
        size_t xdg_len = strlen(XDG_DATA_HOME);

        size_t maxLen = xdg_len + 1;
        maxLen += strlen(FILE_DIR);
        maxLen += strlen(FILE_NAME);

        dataPath = (char*) malloc(maxLen + 1);
        strcat(dataPath, XDG_DATA_HOME);
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
        strcat(dataPath, HOME);
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


void list()
{
    char* filePath = GetFilePath();
    FILE* noteFile = fopen(filePath, "r");

    if (noteFile == NULL)
        return;

    char line[256];
    int i = 0;
    while (fgets(line, sizeof(line), noteFile))
    {
        printf("[%d] - %s", i, line);
        i++;
    }

    fclose(noteFile);
    free(filePath);
}

void add(const char* note_message)
{
    /* Check if Directory exists */
    char* dataDir = GetDataPath();
    DIR* dir = opendir(dataDir);
    if (dir == NULL)
        mkdir(dataDir, 0777);

    char* filePath = GetFilePath();

    FILE* noteFile = fopen(filePath, "a+");

    fprintf(noteFile, "%s\n", note_message);

    fclose(noteFile);
    free(filePath);
}