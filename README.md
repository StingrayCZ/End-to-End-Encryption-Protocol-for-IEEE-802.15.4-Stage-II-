# Konzultace 4.6.2020

## Text práce

## Aplikace ECDH

Pro přetypování na typ **int64_t** funguje i s velkými čísly. Přpravena na implentaci do stacku. Zbývá jen sjednotit některé drobné odchylky ve společných proměnných, které budou obsaženy v **main.c**. Imho, tímto je aplikace na výměnu klíče hotova.

Je seskupena do čtyř bloků pro všechny tři fáze výměny klíče:

* výběr vstupních hodnot -> **Phase I**
* Generování tajného klíče a výpočet bodu pro sdílení s protistranou -> **Phase II A** a **Phase II B**
* Výpočet společného klíče -> **Phase III**

**Otázka:** Zítra bych na kozultaci pořešil, jak sprvně vytvořit vhodný klíč z bodu, který je výstupem z bloku **PHASE 3**. Mohl bych použít svoji padding aplikaci nebo nějakou metodu součtu (dle Vaší rady). To se poradíme na konzultaci.

### PHASE 1

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

### PHASE 2 A

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

### PHASE 2 B

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

-----------------------------------------------------------------------------------------------------------------

## Padding APP

<p float="left">
  <img src="/Pictures (general)/Cons 2.6.2020/padding.PNG" width="300" /> 
<p float="left"> </p> 
* *Zatatím nepřetypováno a netestováno na uin64_t*

```c

int main()
{
    static int num, result;

    while (1){

    printf("\n\rZadej hondotu:\n\r");
    scanf("%d", &num);


    Padding(&num, &result);


    }
}


void Padding(int *num, int *res)
{


    static int number, size;
    static int i;
    static int result;
    int array[16];   // storage for numbers

    number = *num;
    size = 0;

    // Computing how many positions it has
    while (number != 0)
    {
        number /= 10;
        size++;
    }

    // when result is 0, this is considered as position 1
    if (size == 0)
    {
        size = 1;
    }

    printf("\nCislo obsazuje %d", size);

    size -= 1; // array starts from 0

    // DIVISION ARRAY INTO INDIVIDUAL DIGITS
    number = *num;

    i = size;



    while (number != 0)
    {
        array[i] = number % 10;
        number /= 10;
        i--;
    }

    // Test Print
//    for(int j = size; j >= 0; j--)
//    {
//        printf("\n\rpole [%d] = %d", j, array[j]);
//    }


    // PADDING
    for(int k = (size + 1); k < 16; k++){

        array[k] = 1;
    }


    EMPTYLINE

    // Test Print
    for(int t = 0; t < 16; t++)
    {
        printf("\n\rpole [%2d] = %d", t, array[t]);
    }
    
    //////////////////
    // Skladani cisla
    for (int g = 0; g < 15; g++){
        result = 10 * result + array[g];
    }

    EMPTYLINE

    printf("\n\rNum is %d", result);

}
```
