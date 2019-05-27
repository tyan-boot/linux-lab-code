#include <math.h>
#include <stdio.h>


int main()
{
    double input;
    int calc_type;
    int input_type;

    printf("输入数值\n");
    scanf("%lf", &input);

    printf("类型： 1）角度， 2）弧度:\n");
    scanf("%d", &input_type);

    printf("计算： 1） sin， 2）cos， 3） all:\n");
    scanf("%d", &calc_type);

    if (input_type == 1)
    {
        input = input * M_PI / 180;
    }

    switch (calc_type)
    {
        case 1:
            printf("sin(%lf) = %lf\n", input, sin(input));
            break;
        case 2:
            printf("cos(%lf) = %lf\n", input, cos(input));
            break;
        case 3:
            printf("sin(%lf) = %lf\n", input, sin(input));
            printf("cos(%lf) = %lf\n", input, cos(input));
            break;

        default:
            break;
    }
}