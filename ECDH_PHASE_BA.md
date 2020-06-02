## ECDH PHASE BA

```c
void ECDH_PHASE_BA(int *Order, int *Xf, int *Yf, int *a, int *mod, int array[])
{

    static int OrderG, SecKey;
    static int X, Y, a_asymptote, modulus, iterator;
    int container[2];

    OrderG = *Order;
	X = *Xf;
	Y = *Yf;
	a_asymptote = *a;
	modulus = *mod;

	SecretKey(&OrderG, &SecKey);

	iterator = SecKey;
    iterator += 1;


	PointComp(&X, &Y, &a_asymptote, &modulus, &iterator, container);


	array[0] = container[0];
	array[1] = container[1];
	array[2] = SecKey;


}

```
