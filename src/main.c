#include "termNote/cli-input.h"
#include "config.h"


int main(int argc, char** argv)
{
    struct CLI_Args cli = parse_input(argc, argv);
    switch (cli.cmd)
    {
        case CMD_LIST:
            printf("Listing Prototype.\n");
            break; 
        default:
            break;
    }

    return 0;
}