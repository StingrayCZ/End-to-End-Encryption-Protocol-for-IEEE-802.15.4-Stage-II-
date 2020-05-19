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
