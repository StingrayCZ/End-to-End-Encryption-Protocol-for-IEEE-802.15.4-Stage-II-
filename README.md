# Konzultace 15.6.2020

## Ukázka prezentace

Prezentace ke stažení <a href="https://github.com/StingrayCZ/End-to-End-Encryption-Protocol-for-IEEE-802.15.4-Stage-II-/blob/master/Thesis%20presentation%202020.pdf">zde</a>. </a>

* Prezentace obsahuje obsahuje toho záměrně více, než se do 10 min vejde </p>
* Byla zde snaha maximálně využít vytvořených vývojových diagramů </p>
* Prosím o radu, co vyřadit a kde přidat více podrobností </p>
* Prezentace je logicky členěná dle toho, jak jednotlivé fáze přicházejí na řadu. </p>
* První část prezentace je zaměřena na vysvětlení algoritmu výměny (bez komunikace mezi deskami). </p>
* Druhá část je věnována impmentaci v rámci LWM. </p>
* Je zde pomocí vývojových digramu popsáno fungování **TaskHandleru** a přepínání mezi jednotlivýmy případy **case** </p>

# Prezentace

<p float="left">
  <img src="/Pictures (general)/Presentation ver1.03 FRAME/01.png" width="700" /> 
<p float="left"> </p> 

### Cíle práce
Tunto slide se mi zdá přebytečný. Komi se bude vědět, co je tématem.
<p float="left">
  <img src="/Pictures (general)/Presentation ver1.03 FRAME/02.png" width="700" /> 
<p float="left"> </p> 

### Obecné schéma výměny klíčů
Zde bych řekl, že výměnu klíčů je realizována ve třech fázích.
* Sestavení parametrů eliptické křivky (sortování modula, parametrů křivky, výpočet generátoru a řádu grupy) </p>
<p float="left">
  <img src="/Pictures (general)/Presentation ver1.03 FRAME/03.png" width="700" /> 
<p float="left"> </p> 

### Fáze A (slide 4 - 18)
Zde bude postupně popsána Fáze A, včetně komponent. Tuto část bych ovšem zestručnil. K podprogramům **TheFirstPoint**, **PointComp**, **VerifyOfPoint** bych věnoval jen jeden slide s popisem (ačkoliv u aplikace  **TheFirstPoint** je pro ukázku popsána detailně), co ta funkce umí a dál bych to nerozebíral. Ačkoliv to může být zajímavé, spotřebujeto nějaký čas, který bude chybět jinde. Na **slidu 18** je ukázka, jak pracuje fáze A, tj. výpočet grupy bodů na jednoduchém příkladu. Ten bych tam nechal. Je to důkaz, že ta spleť kódů funguje a generuje nějaké hodnoty.

<p float="left">
  <img src="/Pictures (general)/Presentation ver1.03 FRAME/04.png" width="700" /> 
<p float="left"> </p> 

<p float="left">
  <img src="/Pictures (general)/Presentation ver1.03 FRAME/05.png" width="700" /> 
<p float="left"> </p> 


<p float="left">
  <img src="/Pictures (general)/Presentation ver1.03 FRAME/06.png" width="700" /> 
<p float="left"> </p> 

<p float="left">
  <img src="/Pictures (general)/Presentation ver1.03 FRAME/07.png" width="700" /> 
<p float="left"> </p> 

<p float="left">
  <img src="/Pictures (general)/Presentation ver1.03 FRAME/08.png" width="700" /> 
<p float="left"> </p> 

<p float="left">
  <img src="/Pictures (general)/Presentation ver1.03 FRAME/09.png" width="700" /> 
<p float="left"> </p> 

<p float="left">
  <img src="/Pictures (general)/Presentation ver1.03 FRAME/10.png" width="700" /> 
<p float="left"> </p> 

<p float="left">
  <img src="/Pictures (general)/Presentation ver1.03 FRAME/11.png" width="700" /> 
<p float="left"> </p> 

<p float="left">
  <img src="/Pictures (general)/Presentation ver1.03 FRAME/12.png" width="700" /> 
<p float="left"> </p> 

<p float="left">
  <img src="/Pictures (general)/Presentation ver1.03 FRAME/13.png" width="700" /> 
<p float="left"> </p> 

<p float="left">
  <img src="/Pictures (general)/Presentation ver1.03 FRAME/14.png" width="700" /> 
<p float="left"> </p> 

<p float="left">
  <img src="/Pictures (general)/Presentation ver1.03 FRAME/15.png" width="700" /> 
<p float="left"> </p> 

<p float="left">
  <img src="/Pictures (general)/Presentation ver1.03 FRAME/16.png" width="700" /> 
<p float="left"> </p> 

<p float="left">
  <img src="/Pictures (general)/Presentation ver1.03 FRAME/17.png" width="700" /> 
<p float="left"> </p> 


<p float="left">
  <img src="/Pictures (general)/Presentation ver1.03 FRAME/18.png" width="700" /> 
<p float="left"> </p> 


### Fáze B (slide 19 - 21)
Úvodní stránka Fáze B, ke které řeknu, že má za úkol volbu tajného klíče a výpočet sdíleného klíče. Pro odesilatele a příjemce se liší, protože příjemce si musí z obdržených hodnot *p*, *a* a *b* spočítat generátor a řád. V dalším **20** slidu bych jen řekl, že aplikace je vytvořena jako samostatný blok, který umožňuje snadnou implementaci. Ke slidu **21** bych jen dodat, že aplikace je osahuje funkci (nebo spíše vnořenou aplikaci), která pseudonáhodně vybírá tajný klíč a je zde ošetření proti nulovému výsledků.
<p float="left">
  <img src="/Pictures (general)/Presentation ver1.03 FRAME/19.png" width="700" /> 
<p float="left"> </p> 

<p float="left">
  <img src="/Pictures (general)/Presentation ver1.03 FRAME/20.png" width="700" /> 
<p float="left"> </p> 

<p float="left">
  <img src="/Pictures (general)/Presentation ver1.03 FRAME/21.png" width="700" /> 
<p float="left"> </p> 

### Fáze C (slide 22 - 24)
Opět prezentace dle schématu Fáze B. Říct jen, že tato fáze slouží k výpočtu společného bodů. Obsahuje podaplikakci (další slide), která rozpozná z obdrženého bodu od protistrant tajný klíč (na základš pořadí v grupě).
<p float="left">
  <img src="/Pictures (general)/Presentation ver1.03 FRAME/22.png" width="700" /> 
<p float="left"> </p> 

<p float="left">
  <img src="/Pictures (general)/Presentation ver1.03 FRAME/23.png" width="700" /> 
<p float="left"> </p> 

<p float="left">
  <img src="/Pictures (general)/Presentation ver1.03 FRAME/24.png" width="700" /> 
<p float="left"> </p> 

### Implementace do LWM stacku (slide 25 - 28)
Tady jsem umístil vývojové diagramy, které popisují zapínání jednotlivých fází ve stacku a odesílání dat.

<p float="left">
  <img src="/Pictures (general)/Presentation ver1.03 FRAME/25.png" width="700" /> 
<p float="left"> </p> 

<p float="left">
  <img src="/Pictures (general)/Presentation ver1.03 FRAME/26.png" width="700" /> 
<p float="left"> </p> 

<p float="left">
  <img src="/Pictures (general)/Presentation ver1.03 FRAME/27.png" width="700" /> 
<p float="left"> </p> 

<p float="left">
  <img src="/Pictures (general)/Presentation ver1.03 FRAME/28.png" width="700" /> 
<p float="left"> </p> 


<p float="left">
  <img src="/Pictures (general)/Presentation ver1.03 FRAME/29.png" width="700" /> 
<p float="left"> </p> 
