## Fáze generování 32 bitového čísla

```c
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
    int randNUM, SUM;

    srand((unsigned int) time(NULL));

    for(int i = 0; i < 128; i ++){

            randNUM = (rand()*rand()*rand());
            printf("%d\n\r", randNUM);

            SUM += randNUM;
    }

    printf("%d\n\r",SUM);


    return 0;
}
```
