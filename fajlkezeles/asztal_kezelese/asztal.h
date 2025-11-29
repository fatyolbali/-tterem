#ifndef ASZTAL_H
#define ASZTAL_H

#include <stdbool.h>
#include "../../strukturak/strukturak.h"

// Megnézi, hogy létezik-e az asztalok.txt fájl
bool asztal_letezik(void);

// Új asztal létrehozása
AsztalElem *asztal_letrehoz(AsztalElem *lista, int id, int ferohely, int sor, int oszlop, int foglalt);

AsztalElem *asztal_kitorol(AsztalElem *lista, int id);

// Asztalok beolvasása fájlból
AsztalElem *asztal_beolvas(void);

// Asztalok felszabadítása
void asztal_felszabadit(AsztalElem *lista);

// Asztalok kiírása
void kiiroasztalok(AsztalElem *lista);

// Szabad hely keresése
AsztalElem *szabad_hely_keres(AsztalElem *lista, int letszam);

// Asztalok között keresés
AsztalElem *asztal_kereso(AsztalElem *lista, int id);

AsztalElem *asztal_eldonto(AsztalElem *lista);

void asztalok_elment(AsztalElem *lista);

int maxsor(AsztalElem *lista);

int maxoszlop(AsztalElem *lista);

#endif