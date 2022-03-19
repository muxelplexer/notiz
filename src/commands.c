#include "termNote/commands.h"
#include "termNote/utils.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>

#define MAX_NOTE_LENGTH 4069


void list()
{
    char* filePath = GetFilePath();
    FILE* noteFile = fopen(filePath, "r");

    if (noteFile == NULL)
    {
        free(filePath);
        return;
    }

    char line[MAX_NOTE_LENGTH];
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
    free(dataDir);
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

    char line[MAX_NOTE_LENGTH];
    char deletedLine[MAX_NOTE_LENGTH];

    int i = 0;
    while(fgets(line, sizeof(line), noteFile))
    {
        if (i == id)
        {
            i++;
            size_t lineLen = strlen(line);
            strncpy(deletedLine, line, lineLen - 1);
            continue;
        }
        fprintf(tmp, "%s", line);
        i++;
    }
    fclose(noteFile);
    fclose(tmp);



    remove(filePath);
    rename(tmpFile, filePath);

    printf("Succesfully deleted Note \"[%ld] - %s\"\n", id, deletedLine);

    free(tmpFile);
    free(filePath);
}
