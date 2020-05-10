## Comparison of two strings

### Solution #1

```sh
#include <stdio.h>
#include <stdlib.h>

int main()
{
    int length, lens1, lens2, result;

    char str1[] = "1988";
    char str2[] = "1988";

    lens1 = strlen(str1);
    lens2 = strlen(str2);

    length = lens1 <= lens2 ? lens1 : lens2;
    result = memcmp(str1,str2,length);

    if(result == 0)
    {
        printf("Result is %d. YES", length);
    }

    else
    {
        printf("Result is %d. NO", length);
    }

    return 0;
}

```

### Solution #2
