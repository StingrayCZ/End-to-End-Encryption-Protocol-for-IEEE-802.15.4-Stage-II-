## Method for return multiple values

```sh
#include <stdio.h>


void function(int A, int B, int pole[]){

    A *= 2;
    B *= 4;

    pole[0] = A;
    pole[1] = B;


}


// Driver code
int main()
{

    int a, b;
    int arr[2];

    printf("Enter two numbers: \n");
    scanf("%d%d", &a, &b);

    function(a, b, arr);


    printf("Cisla jsou %d, %d", arr[0], arr[1]);



    return 0;
}

```

## Method for return multiple values (variables + array)

```sh
#include <stdio.h>
#include <stdlib.h>


// PROTOTYPE
void ValReturn();

int main()
{

    int x, y;
    int pole[1000];

    ValReturn(&x, &y, pole);

    printf("Hodnota X je %d\n\r", x);
    printf("Hodnota Y je %d\n\r", y);

    printf("Hodnota pole je %d\n\r", pole[0]);
    printf("Hodnota pole je %d\n\r", pole[1]);

    return 0;
}



void ValReturn(int *A, int *B, int array[]){

    *A = 10;
    *B = 20;

    array[0] = 40;
    array[1] = 50;

}
```
