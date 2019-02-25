//
// Created by oxynux on 2/24/19.
//

#include "kernel/kshell.h"

int cmd_parse(char *buf)
{
    if (strncmp(buf, "reboot", 6) == 0)
    {
        reboot();
    }
    print_to_serial(buf);
}