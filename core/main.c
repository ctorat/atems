/*
 * Copyright (c) 2026, Apollo Telephone Laboratories.
 * Provided under the BSD-3 clause.
 */

#include <stdio.h>
#include <unistd.h>

static void
help(void)
{
    printf("-- APTEL Emulation Suite --\n");
    printf("usage: ./atems [flags]\n");
    printf("[-h]    Display this help menu\n");
}

int
main(int argc, char **argv)
{
    int opt;

    if (argc < 2) {
        printf("fatal: too few arguments\n");
        help();
        return -1;
    }

    if (argc < 2) {
        printf("fatal: too few arguments\n");
        return -1;
    }

    while ((opt = getopt(argc, argv, "h")) != -1) {
        switch (opt) {
        case 'h':
            help();
            return 0;
        }
    }

    return 0;
}
