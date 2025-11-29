#ifndef RENDELES_H
#define RENDELES_H

#include "../../strukturak/strukturak.h"

// beolvassa egy adott asztal rendeléseit
RendelesElem *rendelesek_beolvas(char *rendeles);

// Egy asztal minden rendelését hozzáadja a láncolt listához
RendelesElem *rendeles_hozzaad(RendelesElem *lista, char *etel_neve, int darabszam);

void kiirorendelesek(RendelesElem *lista);

RendelesElem *rendeles_kereso(RendelesElem *lista, char *keresett);

void rendeles_felszabadit(RendelesElem *lista);

#endif