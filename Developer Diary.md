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

## Define / undef

```sh
#include <stdio.h>
#include <stdlib.h>

#define POCET 10
#undef  POCET
#define POCET 20



int main()
{

    printf("Vytiskni cislo: %d\n", POCET);
    printf("Vytiskni cislo: %d\n", POCET);


    return 0;

}
```

## Makro jako chybová hláška

```sh
#include <stdio.h>
#include <stdlib.h>


#define JE_VETSI >
#define JE_MENSI <


#define POSITIVE {printf("Spravne");}
#define ERROR {printf("Chyba!");}

int main()
{

    int a, b;

    a = 30;
    b = 20;

    if(a JE_VETSI b) POSITIVE   // pouziti dvou maker. Jedno jako podminka, druhe jako operace k provedeni

    else ERROR                  // makro jako operace k provedeni


    return 0;

}

```
## Spuštění podprogramu pomocí makra

```sh
#include <stdio.h>
#include <stdlib.h>

#define SPUST_PROGRAM test();    // Volaci makro podpogramu

int main()
{


    printf("Hello world!\n");

    SPUST_PROGRAM

    return 0;
}


int test()   // Definice podpogramu
{
    printf("Program jede\n");
}
```

## Pomíněný překlad #ifdef

```sh
#include <stdio.h>
#include <stdlib.h>

#define SPUST_PROGRAM;   // pokud zakomentuji, program ve vlakne #ifdef nebude proveden

int main()
{


    printf("Hello world!\n");

    #ifdef SPUST_PROGRAM

    printf("Test\n");  // TEST podprogramu

    #endif // SPUST_PROGRAM


    return 0;
}

```
## Rekurze

```sh
#include <stdio.h>


int fakt(int n)
{
    return ((n <= 0) ? 1 : n * fakt(n - 1));
    
    /*
    If Condition is true ? then value X : otherwise value Y
    */
}

int main()
{
    int i;
    printf("Zadadej cislo: ");
    scanf("%d", &i);

    printf("Faktorial je %d\n", fakt(i));  // rekurze funkce pro vypocet faktorialu
    
    /*
    If Condition is true ? then value X : otherwise value Y
    */

    return 0;
}

```

## Příklad použití BREAK

```sh
#include <stdio.h>

int main()
{
    int a, b;

    a = 1;


 for(int i = 1; i <= 50; i++){

    printf("Cislo je %d\n", a);
    a++;

    if(a == 31) break;
  }

}
```

## Příklad použití Switch (integer)

```sh
#include <stdio.h>
#include <stdlib.h>

int main()
{

    int  grade = 4;

    switch(grade)
    {

    case 1 :
        printf("You did great");
        break;

    case 2 :
        printf("You did second");
        break;

    case 3 :
        printf("You did third");
        break;

    default :
        printf("Niiic");
        break;
    }


    return 0;
}

```

## Příklad použití Switch (char)

```sh
#include <stdio.h>
#include <stdlib.h>

int main()
{
    char pismeno;

    printf("Zadej pismeno\n");
    scanf("%c", &pismeno);


    switch(pismeno)
    {

    case 'A' :                       // Ukonceni retezce
        printf("You did great");     // Vnorena operace
        break;                       // Ukonceni retezce

    case 'B' :
        printf("You did second");
        break;

    case 'C' :
        printf("You did third");
        break;

    default :                         // neco jako funkce else
        printf("Niiic");
        break;
    }


    return 0;
}

```

## Tvorba knihovny .h

```sh
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "lib.h"

int main()
{
    int x = 20;

    x = 222 ODECET 2;

    printf("Napi vysledek %d \n", x);

    ERROR
}

```

## Different between char object[10]; and char object

```sh
   char s[] = "geeksquiz";
   char *s  = "geeksquiz";
```

<p float="left">
  <img src="/Pictures (general)/CharVariableArray.png" width="600" />
</p>

## Struktura [struct], práce s řetězci
```sh
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct Student
{
    char name[50];
    char major[50];
    int age;
    double gpa;
};

int main()
{
    //****** Student 1 ******
    struct Student student1;
    student1.age = 22;
    student1.gpa = 3.2;
    strcpy(student1.name, "Jim");
    strcpy(student1.major, "Bussiness");

    //****** Student 2 ******
    struct Student student2;
    student2.age = 32;
    student2.gpa = 5.2;
    strcpy(student2.name, "Bob");
    strcpy(student2.major, "Plumber");

    strcat(student1.major, student2.major);  // Spojeni retezcu
    printf("%s\n", student1.major);

    int ret = strcmp(student1.major, student2.major);  // Porovnavani dvou retezcu
    printf("%d\n", ret);

    // Vyprintovani hodnoty retezce student1.gpa
    printf("%f", student1.gpa);

    return 0;
}
```
<p float="left">
  <img src="/Pictures (general)/Snippets/Snip_000001.PNG" width="600" />
</p>
