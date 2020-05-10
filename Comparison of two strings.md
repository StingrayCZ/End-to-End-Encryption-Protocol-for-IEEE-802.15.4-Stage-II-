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

Toto řešení zahrnuje i vstup.

```sh
#include <stdio.h>
#include <stdlib.h>

#define CLEAR_LINE printf("\r\n");

int main()
{
    int nums1[2] = {5, 10};
    int nums2[2] = {0, 0};

    printf("Zadej cislo X: \r\n");
    scanf("%d", &nums2[0]);

    printf("Zadej cislo Y: \r\n");
    scanf("%d", &nums2[1]);

    CLEAR_LINE
    CLEAR_LINE

    if(memcmp(nums1, nums2, sizeof(nums1)) == 0)
    {
        printf("Rovnaji se");
    }
    else
    {
        printf("NE rovnaji se");
    }

    return 0;
}
```
