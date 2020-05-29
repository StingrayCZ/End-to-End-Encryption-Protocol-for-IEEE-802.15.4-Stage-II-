## Niiccc


```c
#include <stdio.h>
#include <stdlib.h>
#include "function.h"


int main ()
{
    int mod, a, b;  // pseudorandom INput
    int X, Y, O;    // OUTput


    ObtainPointComplex(&mod, &a, &b, &X, &Y, &O);

    printf("\n\rVstupni hodnoty jsou: mod = %d, parametry jsou %d a %d", mod, a, b);
    printf("\n\r[%d, %d], Order is %d", X, Y, O);



}

```
