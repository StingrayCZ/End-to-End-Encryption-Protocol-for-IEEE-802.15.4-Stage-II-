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

            randNUM = (rand()*rand()*rand());           // dosazeni vetsiho cisla
            printf("%d\n\r", randNUM);

            SUM += randNUM;
    }

    printf("%d\n\r",SUM);


    return 0;
}
```

## Násobení pomocí bitových operací
```c
#include <stdio.h>
#include <stdlib.h>

int main()
{
    int j, i;

    j = 80;

    i = (j << 6) + (j << 4);    // vysledek je 6400

    printf("Cislo je %d", i);

    return 0;
}
```

## Spojení jednotlivých 32bit stringu do 512 stringu
```c
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main()
{

    int length;


    char pp [] = "57";
    char pq [] = "348";

    strcat(pp, pq);

    printf("%s\n", pq);

    length = strlen(pp);

    printf("Result is %d", length);


    return 0;
}
```
