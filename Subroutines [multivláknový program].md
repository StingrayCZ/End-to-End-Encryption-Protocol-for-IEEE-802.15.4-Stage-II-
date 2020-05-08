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
    e = prog(&a, &b);
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

#define PLUS +
#define MINUS -

#define SERIAL_H
#define PRGB
```
