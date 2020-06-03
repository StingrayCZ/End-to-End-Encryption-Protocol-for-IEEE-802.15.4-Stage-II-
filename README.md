# Konzultace 4.6.2020

## PHASE 1

**Input:** the application chooses the values by itself  </p>
**Output:** modulus, a parameter, b parameter, XFirst, YFirst, GOrder </p>

```c
// PROTOTYPE
void ECDH_PHASE_A();
```
```c
int64_t mod, a_parameter, b_parameter, X_first, Y_first, G_Order;

ECDH_PHASE_A(&mod, &a_parameter, &b_parameter, &X_first, &Y_first, &G_Order);
```

## PHASE 2 A

**Input:** Order, XFirst, YFirst, a parameter, modulus </p>
**Output:** coordinates of Point for sharing, MySecretKey *(all values are stored in array)* </p>

```c
// PROTOTYPE
void ECDH_PHASE_BA();
```
```c
int64_t Order, Xf, Yf, a, mod;
int64_t container[3];

ECDH_PHASE_BA(&Order, &Xf, &Yf, &a, &mod, container);
```

## PHASE 2 B

**Input:** modulus, a parameter, a parameter </p>
**Output:** coordinates of Point for sharing, MySecretKey *(all values are stored in array)* </p>

```C
// PROTOTYPE
void ECDH_PHASE_BB();
```
```C
int64_t mod, a, b;
int64_t container[3];

ECDH_PHASE_BB(&mod, &a, &b, container);
```

## PHASE 3

**Input:** MySecretKey, XFirst, YFirst, modulus, a parameter, order </p>
**Output:**  MutualKey, MutualPoint *(in array)* </p>

```c
// PROTOTYPE
void ECDH_PHASE_C();
```
```c
int64_t MSKey, XF, YF, XO, YO, mod, a, order, MutKEY;
int64_t container[2];

void ECDH_PHASE_C(&MSKey, &XF, &YF, &XO, &YO, &mod, &a, &order, &MutKEY, container);
```
