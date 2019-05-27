#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>

int main()
{
    long begin = 0, sec = 0, stop = 0;
    struct timeval tv1, tv2;
    struct timezone tz;
    char tmp;

    printf("计时器程序\n");
    printf("b (begin)\n");
    printf("w (watch)\n");
    printf("r (reset)\n");
    printf("s (stop)\n");
    printf("e (end)\n");

    while (1)
    {
        scanf("%c", &tmp);

        if (tmp == 'b')
        {
            if (begin == 1 && stop == 0)
            {
                printf("已经启动\n");
            }

            if (begin == 0 && stop == 0)
            {
                printf("启动\n");

                gettimeofday(&tv1, &tz);

                sec = 0;
                begin = 1;
            }

            if (stop == 1)
            {
                gettimeofday(&tv1, &tz);
                stop = 0;
                printf("暂停结束\n");
            }
        }

        if (tmp == 'w')
        {
            if (stop == 0)
            {
                gettimeofday(&tv2, &tz);
                printf("已经计时 %ld 秒\n", sec + tv2.tv_sec - tv1.tv_sec);
            }

            if (stop == 1)
            {
                printf("已经计时 %ld 秒\n", sec);
            }
        }

        if (tmp == 's')
        {
            if (stop == 1)
                printf("计时已经暂停\n");

            if (stop == 0)
            {
                gettimeofday(&tv2, &tz);
                sec = sec + tv2.tv_sec - tv1.tv_sec;
                printf("计时暂停， 已经计时 %ld 秒\n", sec);
                stop = 1;
            }
        }

        if (tmp == 'r')
        {
            gettimeofday(&tv2, &tz);
            printf("已经计时 %ld 秒\n", sec);
            printf("重置\n");


            begin = 0;
            stop = 0;
            sec = 0;

            printf("计时器程序\n");
            printf("b (begin)\n");
            printf("w (watch)\n");
            printf("r (reset)\n");
            printf("s (stop)\n");
            printf("e (end)\n");


        }

        if (tmp == 'e') break;
    }
}