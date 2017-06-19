#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "xed/xed-interface.h"

enum Arch
{
    X86,
    X64,
    DEFAULT,
};

struct CmdOpt
{
    char *insn;
    size_t size;
    enum Arch arch;
};

void help(char *progName)
{
    printf("[Usage] %s [Options...]", progName);
}

bool sanitize(char *insn)
{
    int i;

    if (strlen(insn) % 2 != 0)
    {
        return false;
    }

    for (i = 0; i < strlen(insn); i++)
    {
        if (!((insn[i] >= '0' && insn[i] <= '9') ||
                    (insn[i] >= 'a' && insn[i] <= 'f')))
        {
            return false;
        }
    }

    return true;
}

struct CmdOpt *parse(int argc, char **argv)
{
    struct CmdOpt *option = calloc(1, sizeof(struct CmdOpt));
    int opt;

    option->insn = NULL;
    option->size = 0;
    option->arch = DEFAULT;

    while (1)
    {
        opt = getopt(argc, argv, "i:s:a:");
        if (opt == -1) break;

        switch (opt)
        {
            case 'i':
                if (option->insn != NULL)
                {
                    free(option->insn);
                    free(option);
                    exit(-1);
                }
                option->insn = strdup(optarg);
                if (!sanitize(option->insn))
                {
                    free(option->insn);
                    free(option);
                    exit(-1);
                }
                break;
            case 's':
                if (option->size != 0)
                {
                    free(option->insn);
                    free(option);
                    exit(-1);
                }
                option->size = atoi(optarg);
                if (option->size == 0)
                {
                    free(option->insn);
                    free(option);
                    exit(-1);
                }
                break;
            case 'a':
                if (option->arch != DEFAULT)
                {
                    free(option->insn);
                    free(option);
                    exit(-1);
                }
                if (!strcmp(optarg, "x86"))
                {
                    option->arch = X86;
                }
                else if (!strcmp(optarg, "x64"))
                {
                    option->arch = X64;
                }
                else
                {
                    free(option->insn);
                    free(option);
                    exit(-1);
                }
                break;
            default:
                help(argv[0]);
                free(option->insn);
                free(option);
                exit(-1);
        }
    }

    return option;
}

int main(int argc, char **argv)
{
    struct CmdOpt *option = parse(argc, argv);

    return 0;
}
