## 31rd July

### Maxima

**4 bit**  => 0-15   1111  </br>
**8 bit**  => 0-255  1111 1111  </br>
**16 bit** => 0-65535  1111 1111 1111 1111  </br>
**32 bit** => 0-4294967296 1111 1111 1111 1111 1111 1111 1111 1111  </br>

### Vyprintovani velkeho cisla
```C
#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

int main()
{
    long long a = 489675628213660;

    printf("%llu\n",a);

    return 0;
}

```

## Post 27th July

### Ver B
```c
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define EMPTYLINE printf("\n");

int main()
{
    srand((unsigned int) time(NULL));

    int RandNUM;
    int res;
    int num = 4;
    char buffer [4];
    char bufferTOTAL [4];


    for(int i = 0; i < 2; i++)
    {

        printf("Davka %d\n", num);

        RandNUM = rand() % 16;
        printf("Rand DEC %d\n", RandNUM);

        itoa (RandNUM,buffer,2);
        printf ("Rand BIN: %s\n",buffer);

        res += (RandNUM << num);

        num -= 4;

        EMPTYLINE


    }


    printf("Total %d\n", res);

    itoa (res,bufferTOTAL,2);

    printf("Total %s\n", bufferTOTAL);


    return 0;
}
```

### Ver A

```c
#include <stdio.h>
#include <stdlib.h>

int main()
{
    int a, b, c, d, e, f, g, res;

    a = 3;
    b = 14;
    c = 6;
    d = 2;
    e = 0;
    f = 6;
    g = 0;

    res = (a << 24) + (b << 20) + (c << 16) + (d << 12) + (e << 8) + (f << 4) + g;    

    printf("Cislo je %d", res);   // vysledek je 654313216

    return 0;
}

```

### Ver B

```c
#include <stdio.h>
#include <stdlib.h>

int main()
{
    int a, b, c, d, e, f, g, h, res;

    a = 2;  // 0010
    b = 7;  // 0111
    c = 0;  // 0000
    d = 0;  // 0000
    e = 0;  // 0000
    f = 7;  // 0111
    g = 0;  // 0000
    h = 0;  // 0000

    res = (a << 28) + (b << 24) + (c << 20) + (d << 16) + (e << 12) + (f << 8) + (g << 4) + h;

    printf("Cislo je %d", res);   // vysledek je 654313216

    return 0;
}

```

# new code

```c
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>

int main()
{

    uint8_t a;

    srand((unsigned int) time(NULL));

//    for(int i = 0; i < 12; i++)
//    {

    while(a == 0)
    {
        uint8_t a = rand()%16;
    }

    printf("Decadic value = %d\n", a);
    
    
//    char buffer[10];
//
//    itoa(a,buffer,2);
//    printf("Binary value = %s\n", buffer);


//    }


    return 0;
}

```


# Advice
I work in crypto and distributed systems. <br />
This concept is called Bignum. <br />
Just like there are 2 digits in binary, 10 digits in decimal, 16 in hex, first choose any base number with N bit length. Say an unsigned int, which is 32-bit on most systems. So total digits will be 2^32. Then an array of 16 ints will represent your Bignum, in 16 digits. Then implement two files, bignum.h and bignum.c. <br />
The .h file will declare a structure called bignum with 16 int array and a single unsigned char (8-bit) to consider for overflow. <br />
Why overflow? Because while adding two 512 bit numbers, the worst case is a 513 bit number. Similarly a multiplication of two 512 bit numbers is worst case a 1024 bit number. Then implement addition, substraction, multiplication, division, and modulo operations. First three should be doable, next two are tricky. Attempt the first three and I can help with the rest. Let me post an addition program in some time for inspiration. Hope this helps.
