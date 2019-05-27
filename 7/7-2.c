#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <syslog.h>
#include <signal.h>
#include <sys/param.h>
#include <sys/stat.h>


int main()
{
    pid_t child1, child2;
    int i;

    child1 = fork();

    if (child1 > 0)
    {
        exit(0);
    } else if (child1 < 0)
    {
        perror("Create child error\n");
        exit(1);
    }

    setsid();
    chdir("/");
    umask(0);

    for (i = 0; i < NOFILE; ++i)
    {
        close(i);
    }

    openlog("6-10 程序信息", LOG_PID, LOG_DAEMON);

    child2 = fork();

    if (child2 == -1)
    {
        perror("Create child error\n");
        exit(1);
    } else if (child2 == 0)
    {
        syslog(LOG_INFO, "child 2 sleep 5 sec");
        sleep(5);
        syslog(LOG_INFO, "child 5 stop");

        exit(0);
    } else
    {
        waitpid(child2, NULL, 0);
        syslog(LOG_INFO, "wait for child 2");

        closelog();

        while (1)
        {
            sleep(10);
        }
    }
}