# End-to-End-Encryption-Protocol-for-IEEE-802.15.4
 
• Algoritmus na výměnu klíču je hotov. Ukázka části pro generování (obsauje i zpětnou kontrolu vygenerované grupy) <a href="https://github.com/StingrayCZ/End-to-End-Encryption-Protocol-for-IEEE-802.15.4-Stage-II-/blob/master/Prototype%2025.5.2020.md">zde</a>.</p>
• Ukázka aplikace pro výpočet společného bodu <a href="https://github.com/StingrayCZ/End-to-End-Encryption-Protocol-for-IEEE-802.15.4-Stage-II-/blob/master/Prototype%2025.5.2020%20(mutual%20point).md">zde</a>.</p>
• Spustitelná výměna klíčů (manuální vstup) v .exe formátu ke stažení <a href="https://github.com/StingrayCZ/End-to-End-Encryption-Protocol-for-IEEE-802.15.4-Stage-II-/blob/master/KeyExchange%20app.exe">zde</a>.</p>
• Spustitelná výměna klíčů (psaudorandom vstup) v .exe formátu ke stažení <a href="https://github.com/StingrayCZ/End-to-End-Encryption-Protocol-for-IEEE-802.15.4-Stage-II-/blob/master/Points%20Generator%20(AUTO).exe">zde</a>.</p>
• Oproti algoritmu ze zimního semestru funguje s jakýmkoliv vstupem (nehodící vstupy jsou automaticky sortovány pomocí podmínek)</p>
• Je kompletně vytvořen softwaru CodeBlocks. Je ale koncipován modulárně, není problém jej snadno přenést do stacku (mám již vyzkoušeno), v pondělí budu prezentovat</p>

• Na případné podělní konzultaci bych rád pořešil komunikaci sítě 802.15.4 se sítí internet.</p>

## Flowchart Diagram výměny klíčů (zelená pole jsou hotova a odzkoušena)
Pro prvotní výměnu vstpu, bude nutné zvolit **implicitní tajný klíč** pro AES blok.

<p float="left">
  <img src="/Pictures (general)/ECDH flowchart 2020_1.png" width="600" /> 
<p float="left">
 

## Generování bodů (na základě modula a parametrů a a b)
Toto je starší verze s "manuálním" vstupem hodnot.
<p float="left">
  <img src="/Pictures (general)/ECHD.PNG" width="350" /> 
<p float="left">
 
 ## Psudonáhodné vstupy
Generování pseudonáhodných vstupů na základě času (v další verzi zaměním za generátor přímo z LWM). Proměnná throttle má za úkol omezovat pseudonáhodná čísla v rozsahu 0 - 300. Algoritmus je testován i na 2000. Funguje, nicméně generování klíčů je pomalejší, resp. čas je více proměnlivý (dle náhodně zvoleného vstupu).

```sh
// Generator of random numbers
    srand((unsigned int) time(NULL));
    int Throttle = 300;                 // Throttle of power
```
```sh
a = rand() % Throttle;
b = rand() % Throttle;
```

## Návěstí (dotaz na konzultaci)
```sh
#include <stdio.h>
#include <stdlib.h>

int main()
{
    int number = 5;


    if (number > 10)
    {
        goto SEND_ACK;
    }
    if (number > 20)
    {
        goto SEND_MESSAGE;
    }
    else
    {
        goto SEND_END;
    }


SEND_ACK:

    printf("\nCislo je vetsi nez 10, ale mensi nez 20");
    return 0;

SEND_MESSAGE:
    printf("\nJe versi nez 20");
    return 0;


SEND_END:
    printf("\nCislo je mensi nez 10");
    return 0;

}
```

## Prezentace
<p float="left">
  <img src="/Pictures (general)/Presentation/ECHD algorithm_01.png" width="900" /> 
<p float="left">
  
<p float="left">
  <img src="/Pictures (general)/Presentation/ECHD algorithm_02.png" width="900" /> 
<p float="left">
  
<p float="left">
  <img src="/Pictures (general)/Presentation/ECHD algorithm_03.png" width="900" /> 
<p float="left">
  
<p float="left">
  <img src="/Pictures (general)/Presentation/ECHD algorithm_04.png" width="900" /> 
<p float="left">
  
<p float="left">
  <img src="/Pictures (general)/Presentation/ECHD algorithm_05.png" width="900" /> 
<p float="left">
  
<p float="left">
  <img src="/Pictures (general)/Presentation/ECHD algorithm_06.png" width="900" /> 
<p float="left">
  
<p float="left">
  <img src="/Pictures (general)/Presentation/ECHD algorithm_07.png" width="900" /> 
<p float="left">
  
<p float="left">
  <img src="/Pictures (general)/Presentation/ECHD algorithm_08.png" width="900" /> 
<p float="left">
  
<p float="left">
  <img src="/Pictures (general)/Presentation/ECHD algorithm_09.png" width="900" /> 
<p float="left">
  
<p float="left">
  <img src="/Pictures (general)/Presentation/ECHD algorithm_10.png" width="900" /> 
<p float="left">
    
<p float="left">
  <img src="/Pictures (general)/Presentation/ECHD algorithm_11.png" width="900" /> 
<p float="left">
  
<p float="left">
  <img src="/Pictures (general)/Presentation/ECHD algorithm_12.png" width="900" /> 
<p float="left">
  
<p float="left">
  <img src="/Pictures (general)/Presentation/ECHD algorithm_13.png" width="900" /> 
<p float="left">
  
<p float="left">
  <img src="/Pictures (general)/Presentation/ECHD algorithm_14.png" width="900" /> 
<p float="left">
  
  
  
  
  
  
