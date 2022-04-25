#include "../utils/libraries.h"

int cmd_echo(int argc, char **argv)
{
    for(int x=1;x<argc;x++)
        printf("%s ",argv[x]);
    printf("\n");
    return 1;
}