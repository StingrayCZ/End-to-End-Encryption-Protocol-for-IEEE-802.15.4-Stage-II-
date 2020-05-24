## Labels (návěští)

Příklad na přepínání jednotlivých stavů.

```sh
#include <stdio.h>

int main()
{
  int number = 50;
  

    if (number > 10){
        goto black;
    }
    else{
        
         printf("\nCislo je mensi nez 10");
         return;
    }
    
   
black:
    
    if (number > 20){
        goto white;
    }
    else{
        printf("\nCislo je vetsi nez 10, ale mensi nez 20");
    
        return;
    }

white:
    printf("\nJe versi nez 20");
    return;
}

```
