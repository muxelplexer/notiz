#include "notiz/cli-input.h"
#include "notiz/commands.h"
#include "config.h"


int main(int argc, char** argv)
{
    struct CLI_Args cli = parse_input(argc, argv);
    switch (cli.cmd)
    {
        case CMD_LIST:
            list();
            break;
        case CMD_ADD:
            add(cli.note);
            break;
        case CMD_DEL:
            delete(cli.id);
            break;
        default:
            break;
    }

    return 0;
}
