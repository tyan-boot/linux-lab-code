#include <stdlib.h>
#include <time.h>
#include <stdio.h>


int main()
{
    time_t t = time(NULL);

    struct tm *t_gmt = gmtime(&t);
    printf("UTC: %s", asctime(t_gmt));


    struct tm *t_local = localtime(&t);
    printf("UTC+8: %s", asctime(t_gmt));

    return 0;
}