## Hash

```sh
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


int main ()
{

    int X = 10;
    int Y = 13;


    int velikost = 10;
    char StringA[velikost];
    char StringB[velikost];

    itoa (X, StringA, velikost);
    itoa (Y, StringB, velikost);

    strcat (StringA, StringB);

     printf("Vypis C: %s\n", StringA);

//      int array[] = { 0, 1, 2, 3, 4, 5, 6 };
//
   printf("Length of array: %d\n", (int)( sizeof(StringA) / sizeof(StringA[0]) ));
//


// printf ("%s", name);

    return 0;
}

```
