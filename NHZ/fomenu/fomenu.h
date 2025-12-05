#ifndef FOMENU_H
#define FOMENU_H

#include "../strukturak/strukturak.h"

void buffer_tisztitas();

void opciok(AsztalElem **lista, MenuElem **etelek, int sorszam);

void fomenu(AsztalElem **lista, MenuElem **etelek);

int egybekeres(void);

#endif