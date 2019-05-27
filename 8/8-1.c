#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAXLINE 100


int main()
{
    char line[MAXLINE];
    FILE *fpin;

    if ((fpin = popen("./input", "r")) == NULL)
    {
        fputs("popen error\n", stdout);
    }

    for (;;)
    {
        fputs("prompt > ", stdout);
        fflush(stdout);

        if (fgets(line, MAXLINE, fpin) == NULL)
        {
            break;
        }

        if (fputs(line, stdout) == EOF)
        {
            fputs("fputs errro ro pipe", stdout);
        }
    }

    if (pclose(fpin) == -1)
    {
        fputs("pclose error to pipe", stdout);
    }

    puts("");

    exit(0);
}