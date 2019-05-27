#include <string.h>
#include <stdio.h>
#include <ctype.h>


int main()
{
    int c;
    while ((c = getchar()) != EOF)
    {
        if (isupper(c))
        {
            c = tolower(c);
        }

        if (putchar(c) == EOF)
        {
            fputs("output error\n", stdout);
        }

        if (c == '\n')
        {
            fflush(stdout);
        }
    }

    return 0;
}