#include "notiz/cli-input.h"
#include "notiz/utils.h"

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

#include "config.h"


const char* argp_program_version = PRJ_VERSION_STRING;
const char* argp_program_bug_address = "<sebastian@muxel.dev>";
const char doc_text[] = "Manage and display your notes from the commandline.";


static struct argp_option options[] = {
    { "list", 'l', NULL, 0, "List all entries", 0 },
    { "add", 'a', "NOTE", 0, "Adds a entry", 0},
    { "delete", 'd', "ID", 0, "Deletes [n]th entry", 0},
    { "delete", 'd', "IDs", 0, "Deletes [n] entries", 0},

    { 0 }
};


static error_t parse_opt(int key, char* arg, struct argp_state* state)
{

    struct CLI_Args* args = state->input;

    switch(key)
    {
        case 'l':
            args->cmd = CMD_LIST;
            break;
        case 'a':
            args->cmd = CMD_ADD;
            args->note = arg;
            break;
        case 'd':
            args->cmd = CMD_DEL;
            args->id = allocIDs();
            args->idNum = parseIDS(args->id, arg);
            break;
        case ARGP_KEY_ARG:
            if (state->arg_num == 0)
                argp_usage(state);
            break;
        case ARGP_KEY_END:
            if (args->cmd == CMD_UNKNOWN)
                args->cmd = CMD_LIST;
            break;
        default:
            return ARGP_ERR_UNKNOWN;
    }
    return 0;
}

static struct argp argp = { options, parse_opt, NULL, doc_text, NULL, NULL, NULL};

struct CLI_Args parse_input(int argc, char** argv)
{
    struct CLI_Args args;
    args.cmd = CMD_UNKNOWN;
    args.idNum = 0;

    argp_parse(&argp, argc, argv, 0, 0, &args);

    return args;
}
