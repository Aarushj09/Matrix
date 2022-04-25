#include "../utils/libraries.h"

int cmd_pwd(int argc, char **argv)
{
    printf("%s\n",getcwd(NULL,0));
    return 1;
}