# Aplicație Management Cadouri Grădiniță

Această aplicație permite gestionarea unei liste de cadouri pentru copiii de grădiniță. 

## Demonstrație de funcționare

Link către video: [YoutubeVideo](https://www.youtube.com/watch?v=0mmmugvGWEk&feature=youtu.be)

## Cerințe

Pentru a rula aplicația, trebuie mai întâi să o compilați. Aplicația este scrisă în C++ și poate fi compilată folosind `g++`.

## Instrucțiuni de compilare și rulare

1. Deschideți terminalul în directorul unde se află fișierul sursă (`program.cpp`).
2. Compilați aplicația utilizând comanda `g++`:

        
       g++ program.cpp -o gestionare_cadouri

   Această comandă va crea un fișier executabil numit `gestionare_cadouri`.

3. Rulați aplicația folosind comanda:

       ./gestionare_cadouri

## Funcționalități

Aplicația oferă următoarele funcționalități principale:
- Afișarea cadourilor.
- Crearea unui cadou nou (aliment sau jucărie).
- Căutarea cadourilor după diferite criterii (nume cadou, nume destinatar, aromă, culoare).
- Actualizarea atributelor unui cadou existent.
- Ștergerea cadourilor.

## Cerințe specifice

Aplicația este realizată conform următoarelor cerințe:

-  Adăugarea de cadouri în listă (de la tastatură, element cu element) și afișarea acestora.
-  Căutarea unei jucării după culoare.
-  Ștergerea unui cadou după denumire.
-  Modificarea cantității (+/-1) pentru alimentele care sunt dulci (dacă la scădere se ajunge la 0, trebuie să se sesizeze utilizatorul).
-  Aplicația include și o comandă pentru ieșirea din aplicație.
