## ECDH PHASE II B

```c

     static int mod, a, b;
    int container[3];

    mod = 7;
    a = 1;
    b = 6;


    ECDH_PHASE_BB(&mod, &a, &b, container);


    printf("\nTajny bod je [%d, %d], klic je %d", container[0], container[1], container[2]);

```

```c
void ECDH_PHASE_BB(int *mod, int *a, int *b, int array[])
{
    static int modulus, a_pam, b_pam;
    static int OrderG, SecKey;
    static int X, Y, iterator;
    static int voidValue;   // excess value
    int container[2];




    modulus = *mod;
    a_pam = *a;
    b_pam = *b;

    //Input: mod, a, b
    //Output: Xfirst, Yfirst, OrderG
    TheFirstPoint(&modulus, &a_pam, &b_pam, &X, &Y, &OrderG);

	SecretKey(&OrderG, &SecKey);

	iterator = SecKey;
    iterator += 1;


	PointComp(&X, &Y, &a_pam, &modulus, &iterator, container, &voidValue);


	array[0] = container[0];
	array[1] = container[1];
	array[2] = SecKey;

}
```
