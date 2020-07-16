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
