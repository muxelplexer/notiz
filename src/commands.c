#include "termNote/commands.h"
#include "termNote/utils.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>


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

void delete(long id)
{
    char* filePath = GetFilePath();
    const char* tmpFileName = "notes.tmp";

    char* dataPath = GetDataPath();
    char* tmpFile = (char*) malloc(strlen(dataPath) + strlen(tmpFileName) + 1);
    strcpy(tmpFile, dataPath);
    strcat(tmpFile, tmpFileName);
    free(dataPath);

    FILE* noteFile = fopen(filePath, "r");

    if (noteFile == NULL)
    {
        free(filePath);
        return;
    }

    FILE* tmp = fopen(tmpFile, "w+");

    char line[256];

    int i = 0;
    while(fgets(line, sizeof(line), noteFile))
    {
        if (i == id)
        {
            i++;
            continue;
        }
        fprintf(tmp, "%s", line);
        i++;
    }
    fclose(noteFile);
    fclose(tmp);



    remove(filePath);
    rename(tmpFile, filePath);

    free(tmpFile);
    free(filePath);
}
