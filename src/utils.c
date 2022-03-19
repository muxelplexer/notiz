#include "notiz/utils.h"
#include <stdlib.h>
#include <string.h>
#include <dirent.h>

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
