#include <stdlib.h>
#include <time.h>
#include <stdio.h>


int main()
{
    srand(time(NULL));

    int n = 1 + rand() / ((RAND_MAX + 1u) / 1000);
    int lives = 20;
    int input;

    printf("input: ");
    scanf("%d", &input);

    while (lives--)
    {
        if (input < n)
        {
            printf("small\n");
        } else if (input > n)
        {
            printf("large\n");
        } else
        {
            printf("success!\n");
            exit(0);
        }

        printf("input: ");
        scanf("%d", &input);
    }

    printf("you lose\n");
    exit(1);
}