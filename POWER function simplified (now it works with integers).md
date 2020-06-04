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
# Ready for immpemented
```c
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int64_t Power();

int main()
{
    int64_t a, b, c;

    a = -2;
    b = 9;

    c = Power(&a, &b);

    printf("Result is %d", c);

}




int64_t Power(int64_t *Num, int64_t *PowerNum)
{
    int64_t num, powernum, result;

    num = *Num;
    powernum = *PowerNum;

    result = (int64_t)(round(pow(num, powernum)));

    return result;

}

```
