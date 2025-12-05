#ifndef STRUKTURAK_H
#define STRUKTURAK_H

// Menü struktúra
typedef struct MenuElem
{
    char *nev;
    int ar;
    struct MenuElem *kov;
} MenuElem;

typedef struct RendelesElem
{
    int darab;
    char *rendelesnev;
    struct RendelesElem *kov;
} RendelesElem;

// Asztal struktúra
typedef struct AsztalElem
{
    int id;
    int ferohely;
    int sor;
    int oszlop;
    int foglalt;
    RendelesElem *rendelesek;
    struct AsztalElem *kov;
} AsztalElem;

#endif