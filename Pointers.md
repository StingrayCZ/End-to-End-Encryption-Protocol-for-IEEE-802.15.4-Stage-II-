# Pointers (examples)

## Example 1

```sh
#include <stdio.h>
#include <stdlib.h>

void getValue(int *my_pointer)
{
    *my_pointer = 1000;
    return;
}

int main()
{
    int get_the_value;
    getValue(&get_the_value);

    printf("The value of get_the_value is %d", get_the_value);
}
```
