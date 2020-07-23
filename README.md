# Konzultace 23.7.2020
## Test prvočíselnosti

### Utility function to do modular exponentiation (x^y) % p 
```C
#include <stdio.h>
#include <stdlib.h>

int main()
{

    int x, y, p;
    x = 174;
    y = 110;
    p = 221;


    int result = power(x, y, p);

    printf("%d", result);

}


int power(int x, unsigned int y, int p)
{
    int res = 1;      // Initialize result
    x = x % p;  // Update x if it is more than or
                // equal to p
    while (y > 0)
    {
        // If y is odd, multiply x with result
        if (y & 1)
            res = (res*x) % p;

        // y must be even now
        y = y>>1; // y = y/2
        x = (x*x) % p;
    }
    return res;
}

```

