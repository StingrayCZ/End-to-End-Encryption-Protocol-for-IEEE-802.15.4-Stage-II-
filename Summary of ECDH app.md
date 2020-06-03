#  Summary of ECDH app

## PHASE A


## PHASE C

**Input:** MySecretKey, XFirst, YFirst, modulus, a parameter, order;
*Output:**  MutualKey, MutualPoint *(in array)* 

```c
int64_t MSKey, XF, YF, XO, YO, mod, a, order, MutKEY, container;

void ECDH_PHASE_C(&MSKey, &XF, &YF, &XO, &YO, &mod, &a, &order, &MutKEY, container);

```
