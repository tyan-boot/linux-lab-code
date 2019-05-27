#include <stdio.h>
#include <stdlib.h>

int cmp(const void *lhs, const void *rhs)
{
    return *((int *) lhs) - *((int *) rhs);
}

int main()
{
    int *arr = calloc(10, sizeof(int));
    int idx, input;

    printf("input: ");
    for (idx = 0; idx < 10; ++idx)
    {
        scanf("%d", &input);
        arr[idx] = input;
    }

    qsort(arr, 10, sizeof(int), cmp);

    printf("max = %d, min = %d", arr[0], arr[9]);

    free(arr);
}