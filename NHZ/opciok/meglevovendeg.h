#ifndef MEGLEVOVENDEG_H
#define MEGLEVOVENDEG_H

#include "../strukturak/strukturak.h"

AsztalElem *rendeles(MenuElem *lista, AsztalElem *egyasztal);

void szamla(MenuElem *etelek, AsztalElem *egyasztal);

void almenu(int asztalid, AsztalElem *egyasztal, MenuElem *etelek, AsztalElem *lista);

void meglevovendeg(AsztalElem *lista, MenuElem *etelek);

#endif