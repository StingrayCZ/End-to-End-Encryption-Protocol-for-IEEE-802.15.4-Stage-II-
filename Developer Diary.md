## Preprocesor (#define SOMETHING) - basic

```sh
#include <stdio.h>
#include <stdlib.h>
#define JE_VETSI  >
#define JE_MENSI  <
#define AND  &&
#define PLUS +
#define MIN -
#define PI 3.14
#define DVE_PI (2 * PI)
#define SET printf("\nZdarJakBRNO");

int main()
{

    int a, b, c;

    a = 20;
    b = 20;

    if(a JE_VETSI b)               // pouziti preprocesoru
    {
        printf("Je vetsi\n");
    }
    else if(a JE_MENSI b)           // pouziti preprocesoru
    {
        printf("Je mensi\n");
    }
    else
    {
        printf("jsou stejne\n");      
    }


    float d = DVE_PI;                // pouziti preprocesoru
    printf("Vytiskni cislo: %f", d);


    return 0;

}
```
