# Záverečný projekt
Projekt se bude věnovat hardwaru, konkrétně pak tanku na dálkové ovládání.
# Úvod
Rozhodl jsem vytvořit vozidlo na dálkové ovládání, protože mě práce s Arduino moduly vždy zajímala a vždy jsem chtěl vytvářet modely historických vozidel, primárně pak tanků. 

Hlavním cílem mého projektu bylo vytvoření funkčního tanku, který bude modelově odpovídat předloze historického tanku Tiger I. Tank je vytvořený za pomocí programu Inventor přeložený do formátu gcode a vytištěný na 3D tiskárně. Program tanku je v jazyce Arduino, který je kombinací jazyků C a C++.  

Uživatel se připojí k tanku pomocí ovladače a může si vybrat mezi dvěma módy ovládání, poté již bezstarostně ovládá pohyb tanku a otáčení věže.

> Pro prohlížení souborů doporučuju používat [AUTODESK Viewer](https://360.autodesk.com/viewer "AUTODESK Viewer")

## Rozdělení projektu na branche

1. Základní funkce
   - [x] Kód na pohyb motorů pomocí drátem zapojeným joystickem
   - [x] Schéma zapojení komponentů
   - [x] Video obsahující ukázku funkčnosti
   - [x] Reference
   
2. Prototyp 3D modelu "auta"
   - [x] Samotné části prototypu
   - [x] Screenshoty prototypu
   - [x] Využité technologie

## Cíle

1. Nákup komponentů a diskuze s učiteli
   - [x] Nákup komponentů
   - [X] Diskuze

2. Navrhnout a sestrojit prototip základny
   - [x] Prototyp V1

3. Zprovoznění zařízení BLUETOOTH
   - [x] Vlastnit komponent
   - [x] Zprovoznit komunikaci s mobilem
   - [x] Přehodnocení a konečné rozhodnutí zhotovit vlastní kontroler místo mobilu
   - [x] Návrh kontroleru
   - [ ] Komunikace mezi dvěmi arduino
   - [x] Konstrukce kontroleru
   - [ ] Celkové ovládání modelu skrz kontroler
   
4. Navrhnout kód na pohyb koly
   - [x] Základní Kód
   - [x] Funkce kol
   - [x] Využití joysticku na ovládání kol

5. Navrhnout konečný model tanku
   - [x] Pásy
   - [x] Ozubené kola
   - [x] Systém odpružení pro ostatní kola
   - [x] Dolní část modelu
   - [x] Horní část modelu
   - [x] Věž
   - [X] Dělo
   - [x] Prostory pro moduly v modelu
   - [ ] Detaily modelu
6. Navrhnout finální kód pro controller
   - [X] Funkčnost Joysticků
   - [X] Funkčnost tlačítka/tlačítek (dle potřeby)
   - [X] Funkce dvou rozdílných módů ovládání
   - [X] Funkce Bluetooth
   - [ ] úspěšný test
   - [ ] funkční
7. Navrhnout finální kód pro model
   - [ ] Funkčnost ovládání motorů skrze bluetooth
   - [ ] Funkčnost ovládání serva skrze bluetooth
   - [x] Fungující odpojování baterie
   - [x] Funkce vypnutí celého modelu
   - [ ] úspěšný test
   - [ ] funkční
   
## rozvržení času
- Osobně bych řekl, že jsem na projektu strávil něco mezi 130 - 200 hodin.
