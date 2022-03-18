#ifndef CLI_INPUT_H
#define CLI_INPUT_H

#include <argp.h>

typedef enum {
    CMD_UNKNOWN = 0,
    CMD_LIST,
} COMMAND;

struct CLI_Args
{
    COMMAND cmd;
};

struct CLI_Args parse_input(int argc, char** argv);


#endif