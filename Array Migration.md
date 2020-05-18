## Algorithm for array migration 

```sh
#include <stdio.h>

int* fun(int *iterace, int *arr)
{
    int iter = *iterace;
    int number = 1;

    for(int i = 1; i <= iter; i++)
    {
        arr[i] = number * 2;
        number++;
    }

    /* Some operations on arr[] */
//    arr[0] = 00;
//    arr[1] = 10;
//    arr[2] = 20;
//    arr[3] = 30;
//    arr[4] = 40;


    return arr;
}

int main()
{
    int iteration = 5;

    int pole[iteration];
    int* ptr = fun(&iteration, pole);

    for(int i = 1; i <= iteration; i++)
    {
        printf("%d\n\r", ptr[i]);
    }

    return 0;
}

```
