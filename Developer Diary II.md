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
