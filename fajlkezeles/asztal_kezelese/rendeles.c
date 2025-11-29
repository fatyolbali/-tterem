#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "../../debug/debugmalloc.h"
#include "asztal.h"
#include "../../strukturak/strukturak.h"

RendelesElem *rendelesek_beolvas(char *rendeles)
{
    if (rendeles == NULL || strcmp(rendeles, "") == 0 || strlen(rendeles) == 0)
        return NULL;

    char *rendeles_cpy = (char *)malloc((strlen(rendeles) + 1) * sizeof(char));
    strcpy(rendeles_cpy, rendeles);

    RendelesElem *lista = NULL;
    char *token = strtok(rendeles_cpy, ",");

    while (token != NULL)
    {
        char etel_buffer[100];
        int darab = 0;

        if (sscanf(token, "%99[^:]:%d", etel_buffer, &darab) == 2)
            lista = rendeles_hozzaad(lista, etel_buffer, darab);

        token = strtok(NULL, ",");
    }

    free(rendeles_cpy);
    return lista;
}

RendelesElem *rendeles_hozzaad(RendelesElem *lista, char *etel_neve, int darabszam)
{
    RendelesElem *uj = (RendelesElem *)malloc(sizeof(RendelesElem));
    uj->rendelesnev = (char *)malloc((strlen(etel_neve) + 1) * sizeof(char));
    strcpy(uj->rendelesnev, etel_neve);
    uj->darab = darabszam;
    uj->kov = lista;

    return uj;
}

void kiirorendelesek(RendelesElem *lista)
{
    RendelesElem *iter = lista;
    while (iter != NULL)
    {
        RendelesElem *kov = iter->kov;
        printf(" %s: %d", iter->rendelesnev, iter->darab);
        iter = kov;
    }
}

RendelesElem *rendeles_kereso(RendelesElem *lista, char *keresett)
{
    RendelesElem *iter = lista;
    while (iter != NULL)
    {
        RendelesElem *kov = iter->kov;
        if (strcmp(iter->rendelesnev, keresett) == 0)
            return iter;
        iter = kov;
    }
    return NULL;
}

void rendeles_felszabadit(RendelesElem *lista)
{
    RendelesElem *iter = lista;
    while (iter != NULL)
    {
        RendelesElem *kov = iter->kov;
        free(iter->rendelesnev);
        free(iter);
        iter = kov;
    }
}