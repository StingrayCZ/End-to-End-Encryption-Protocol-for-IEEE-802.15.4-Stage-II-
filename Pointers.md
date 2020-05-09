# Pointers (examples)

<p float="left">
  <img src="/Pictures (general)/DedicationOfPointers.PNG" width="700" />
</p>

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

## Example 2

```sh
#include <stdio.h>
#include <stdlib.h>

int main()
{
    int a, *p_a;;

    a = 56;

    p_a = &a; // Uloží do p_a adresu proměnné a
    *p_a = 15; // Uloží hodnotu 15 na adresu v p_a



    printf("Promenna a s hodnotou %d je v pameti ulozena na adrese %p", a, &a);

    printf("\n");

    printf("Ukazatel p_a má hodnotu %d ukazuje na hodnotu %d", p_a, *p_a);

    /*    
    Zvykněte si pointery pojmenovávat vždy tak, aby začínaly na p_.
    Vyhnete se tak v budoucnu velkým problémům, protože pointery jsou
    poměrně nebezpečné, jak dále zjistíme, a měli bychom si srozumitelně
    označit, zda je proměnná pointerem či nikoli.
    
    Do ukazatele p_a (zatím bez hvězdičky) se uloží adresa proměnné a,
    kterou získáme pomocí referenčního operátoru &. Nyní chceme tam,
    kam ukazuje pointer p_a, uložit číslo 15. Použijeme dereferenční
    operátor (*) a tím neuložíme hodnotu do ukazatele, ale tam, kam
    ukazatel ukazuje.
    */

    return (EXIT_SUCCESS);
}

```

## Example 3

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

## Example 4 (based on book)

```sh
#include <stdio.h>
#include <stdlib.h>

int main()
{
    int i, *p_i;

    i = 5;

    // *p_i = &i;
    /* incializace adresou promenne i
    */



    p_i = &i;
    /* prirazovaci prikaz, ktery v programu provede
       prirazeni adresy promenne i do promenne (pointeru) p_i
    */

    printf("Cislo %d", *p_i);

}

```

## Example 5 (based on book)

```sh
#include <stdio.h>
#include <stdlib.h>

int main()
{
    int i, *p_i;

    p_i = &i;
    i = 5;
    *p_i = i;

    printf("Vytiskni %d", *p_i);

    return 0;
}

//  Vysledek kompilace je 5
```
