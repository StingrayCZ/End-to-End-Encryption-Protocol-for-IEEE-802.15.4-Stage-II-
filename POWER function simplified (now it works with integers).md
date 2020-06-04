## POWER function simplified

```c
#include <stdio.h>
#include <stdlib.h>

int main()
{
    int a, num, powernum;

    // Using typecasting for
    // integer result

    num = -7;
    powernum = 2;


    a = (int)(round(pow(num, powernum)));


    printf("%d", a);

    return 0;

}

```
