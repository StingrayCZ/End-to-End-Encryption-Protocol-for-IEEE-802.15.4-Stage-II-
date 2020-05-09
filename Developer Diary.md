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

### Spustitelny main
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
### Knihovna "Lib.h"
```sh
# define SOUCET +
# define ODECET -
# define ERROR {printf("Toto je chyba");}
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

## Přetypování proměnné

```sh
#include <stdio.h>
#include <stdlib.h>

int main()
{

    int a = 2;
    char *b = 3;

    int c = a + (int)b;

    printf("%d", c);


```

## Ověření velikosti proměnnné (Sizeof)

```sh
#include <stdio.h>
#include <stdlib.h>

float a;

int main()
{
    printf("%d\n", sizeof(a));

    return 0;
}
```
## Typy parametrů

<p float="left">
  <img src="/Pictures (general)/Type of Parameters.PNG" width="1200" />
</p>

<p float="left">
  <img src="/Pictures (general)/Type of Parameters verB.PNG" width="600" />
</p>

## promene v hlavicce podprogramu

Hlavicka funkce obsahuje nusledujici promenenne **void prohod(int a, int b){}**, ktere jsou zastoupeny pri volni funkce **prohod(cislo1, cislo2);**.

```sh
#include <stdio.h>
#include <stdlib.h>

int main()
{
    int a, b;

    a = 20;
    b = 30;

    math(&a, &b);

    printf("Cislo a je %d", a);

}


void math(int *x, int *y){

    *x = *x + *y;
}

```

## Práce s řetězci <string.h>

<p float="left">
  <img src="/Pictures (general)/StringCommands.PNG" width="700" />
</p>


## 2D Arrays & Nested Loops (part 1)

```sh
#include <stdio.h>
#include <stdlib.h>

int main()
{

    int nums[20][2] = {
    {1, 2}, {2, 3}, {3, 4}, {5, 6}
    };

    printf("%d\n", nums[3][1]);

    printf("%d\n", nums[4][1]);

    nums [4][1] = 5;


    printf("%d\n", nums[4][1]);

    return 0;
}
```
## 2D Arrays & Nested Loops (part 2)

```sh
#include <stdio.h>
#include <stdlib.h>

int main()
{

    int nums[20][2] = {
    {1, 2}, {1, 2}, {3, 4}, {5, 6}
    };


    if(nums[0][0] == nums[1][0] && nums[0][1] == nums[1][1]) {
       printf("Ano\n");
    }
    else{
        printf("Ne\n");
    }

    return 0;
}
```
## Operátory přiřazení
<p float="left">
  <img src="/Pictures (general)/AssignmentOperators.PNG" width="700" />
</p>

Zjednodušený příklad na operátoty přiřazení.

```sh
#include <stdio.h>
#include <stdlib.h>

int main()
{

    int a = 5;
    int b = 25;


//    a *= a;   // vysldek je 25
//    a *= a + b; // (a+b)*a = (5+10)*5 = 75

    return 0;
}

```

Příklad přiřazeni v příkladu s ukazateli (pointery).
```sh
#include <stdio.h>
#include <stdlib.h>

int getSum(int *array_val, int size)
{
    int sum = 0;
    for(int i = 0; i < size; i++)
    {
        sum += array_val[i];                        // operator prirazeni  +=  ekvi. sum = sum + array_val[];
        return sum;
    }
}

int main ()
{
    int my_array[4] = {10, 20, 30, 40};
    int mySum = getSum(my_array, 4);                // proc tu neni ampersand?

    printf("the value of my sum is %d", mySum);
}
```

## String (řetězce)

### Example A

```sh
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{

    char my_string[6] = {'H','E','L','L','O'};         // puvodni
    char my_string_uprage[] = {'H','E','L','L','O'};   // zmena

    char other_string[6] = "Hello";  // zmena
    char other_string_uprage[] = "Hello";   // puvodni


    printf("My string value is %s\n", my_string);
    printf("My string value is %s\n", my_string_uprage);

    printf("Other string value is %s \n", other_string);
    printf("Other string value is %s \n", other_string_uprage);

    return 0;
}
```

:white_check_mark: supported
:x: NOT supported

### Example A (extended ver)

```sh
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{

    char stringA[12] = "Alpha";
    char stringB[12] = "Bravo";
    char stringC[12] = "Charlie";

    char stringD[12] = "Delta";
    char stringE[12] = "Echo";



    // *** Strcpy ***
    strcpy(stringB, stringC);   // strcpy(dest., source);
    strcpy(stringA, stringB);   // strcpy(dest., source);


    // *** Strcat ***
    strcat(stringD, stringE);   // Add StringB to String C, like a strcpy(dest., source);

    // *** Strlen ***
    int lenght_stringA = strlen(stringA);



    printf("strcpy = %s \n", stringA);          // result of stringA: Charlie
    printf("stracat = %s \n", stringD);         // result of stringD: DeltaEcho
    printf("strlen = %d \n", lenght_stringA);   //

    return 0;
}
```
## Alternativní zadání proměnných (na jeden řádek)

```sh
#include <stdio.h>
#include <stdlib.h>

int main()
{
    int a = 5, b = 3, c = 2, d;

    d = a + b + c;

    printf("Ze zadani int a = 5, b = 3, c = 2, d; je vysledek: %d", d);

    return 0;
}

```

## Multivlaknovy program

Program, který se skládá ze **dvou souborů .c** a jednoho **souboru .h**

### Main()
```sh
// Toto je hlavni program main(){}

#include <stdio.h>
#include <stdlib.h>
#include "Serial.h"

int e;


int main()
{
    int a = 5, b = 3, c = 2, d, e;    // definice promennych na jednom radku

    d = a PLUS b MINUS c;             // pouziti define prikazu z headeru

#ifdef SERIAL_H                       // cast kodu aktiv/deaktiv z headeru
    e = prog(&a, &b);                 // naliti vysledku (navratova hodnota) do promenne e
    printf("hodnota e je %d", e);
#endif

#ifdef PRGB
    printf("\nAhoj");
#endif // PRG


    return 0;
}
```

### Podprogram

```sh
// Toto je podprogram.c obsahujici funkci prog

int prog(int *x, int *y)
{
    int prog;            // je nutna znovu definice v tele funkce, prog neni globalni
    prog = *x + *y;
    return prog;
}
```

### Header file

```sh
// Toto je soubor Serial.h

#define PLUS +          // defeinice funkce plus
#define MINUS -         // defeinice funkce minus

#define SERIAL_H        // aktivace podprogramu, #ifdef/#endif
#define PRGB            // aktivace podprogramu, #ifdef/#endif

```
## Return

```sh
#include <stdio.h>
#include <stdlib.h>

int Product(int a, int b){
    return (a * b);
}

int main()
{
    int sum = Product(5,6) + 20;
    printf("Vysledek je %d", sum);
    return 0;
}
```
## Pointery (rozdíl, kdy je Nepoužiji a kdy je použiji)

Ukázka, jak proč používat ukazatele. Příklad na promíchání čísel. Převzato ze stánke ČVUT, odkaz <a href="http://kmlinux.fjfi.cvut.cz/~fabiadav/cecko/poznamky-k-jazyku-c/ukazatele">zde </a>.


```sh
#include <stdio.h>
void swap (int a, int b)
{
  int c = a;
  a = b;
  b = c;
}

int main (void)
{
  int a = 3, b = 2;
  swap(a, b);
  printf("%d, %d\n", a, b);
  return 0;
}
```

Očekávaným výstupem je **2, 3**. Ale ve skutečnosti je je to **3, 2**. Proto je nutné, viz níže použít pointery. Jak je to možné? Funkce swap() totiž pracuje s parametrem předávaným hodnotou, tzn., že se při volání funkce vytvoří lokální kopie všech parametrů. V našem případě se tedy vytvoří kopie parametru a a b, ty se mezi sebou přehodí a na konci funkce se zničí. Původní hodnoty proměnných zůstanou nezměněné. Abychom dosáhli svého, musíme se na data dostat nepřímo. Zde nacházejí uplatnění ukazatele.

```sh
#include <stdio.h>
void swap (int *a, int *b)    //  int *a = &a  ukazatel na typ int, do ktere jsme ulozili adresu promene a
{
  int c = *a;
  *a = *b;
  *b = c;
}

int main (void)
{
  int a = 3, b = 2;
  swap(&a, &b);
  printf("%d, %d\n", a, b);
  return 0;
}
```
## Pointers - How it works

```sh
int i, *p_i1, *p_i2;
```

<p float="left">
  <img src="/Pictures (general)/DedicationOfPointers.PNG" width="600" />
</p>

## Pointery (tisk adresy)

```sh
int main()
{
    int i, *p_i = &i;

    printf("%p\n%p", &i, p_i);

    return 0;
}
```

## Printf (decimal number)

```sh
#include <stdio.h>
#include <stdlib.h>

int main()
{

    double a = 2.37;

    printf("Vypis %f, %e, %g", a, a, a);

    return 0;
}
```

<p float="left">
  <img src="/Pictures (general)/PrintfDeciamlNumber.PNG" width="450" />
</p>

## ATOI

Změna  pole/řetězcr na integer...

```sh
#include <stdio.h>
#include <stdlib.h>

int main()
{

    char numA[34] = "123";
    char numB = 15;

    int IntegerA = atoi(numA);

    printf("Vypis %d\n", IntegerA);
}
```

## ITOA (Integer To Array)

Změna integeru na pole/řetězec...

```sh
#include <stdio.h>
#include <stdlib.h>

int main()
{

    int MyInteger = 88;
    char String[10] = {};
    itoa(MyInteger, String, 10);     \\ je pot5eba zadat velikost retezce

    printf("Vypis A: %d\n", String);
    printf("Vypis B: %c\n", String);
    printf("Vypis C: %s\n", String);

    return 0;
}

```

