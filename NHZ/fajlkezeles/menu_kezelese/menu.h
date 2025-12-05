#ifndef MENU_H
#define MENU_H

#include <stdbool.h>
#include "../../strukturak/strukturak.h"

// Megnézi, hogy létezik-e a menu.txt fájl
bool menu_letezik(void);

// Új menüelem létrehozása
MenuElem *menu_letrehoz(MenuElem *lista, char *neve, int ara);

MenuElem *menu_kitorol(MenuElem *lista, char *neve);

MenuElem *menu_valtoztat(MenuElem *lista, char *neve, int ara);

// Menü beolvasása fájlból
MenuElem *menu_beolvas(void);

// Menü felszabadítása
void menu_felszabadit(MenuElem *lista);

// Menü kiírása
void kiiromenu(MenuElem *lista);

MenuElem *menu_eldonto(MenuElem *lista);

void menu_elment(MenuElem *lista);

MenuElem *etel_ar(MenuElem *lista, char *keresett);

bool etel_kereso(MenuElem *lista, char *keresett);

#endif