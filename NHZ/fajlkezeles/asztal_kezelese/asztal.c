#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "../../debug/debugmalloc.h"
#include "asztal.h"
#include "../../strukturak/strukturak.h"
#include "rendeles.h"

// Megnézi, hogy létezik-e már a asztalok.txt fájl

bool asztal_letezik(void)
{
    FILE *asztal = fopen("asztalok.txt", "r");
    if (asztal == NULL)
        return false;
    fclose(asztal);
    return true;
}

// hogyha nem létezik még a asztalok.txt fájl, akkor felhasználótól adatokat kér be

AsztalElem *asztal_letrehoz(AsztalElem *lista, int id, int ferohely, int sor, int oszlop, int foglalt)
{
    AsztalElem *uj;
    uj = (AsztalElem *)malloc(sizeof(AsztalElem));
    uj->id = id;
    uj->ferohely = ferohely;
    uj->foglalt = foglalt;
    uj->sor = sor;
    uj->oszlop = oszlop;
    uj->rendelesek = NULL;
    uj->kov = lista;

    return uj;
}

AsztalElem *asztal_kitorol(AsztalElem *lista, int id, bool *talalt)
{
    *talalt = false;
    AsztalElem *mozgo = lista;
    AsztalElem *lemarado = NULL;

    while (mozgo != NULL && mozgo->id != id)
    {
        lemarado = mozgo;
        mozgo = mozgo->kov;
    }

    if (mozgo == NULL)
    {
        return lista;
    }

    *talalt = true;

    if (mozgo->rendelesek != NULL)
    {
        rendeles_felszabadit(mozgo->rendelesek);
        mozgo->rendelesek = NULL;
    }

    if (lemarado == NULL)
    {
        AsztalElem *ujeleje = mozgo->kov;
        free(mozgo);
        return ujeleje;
    }
    else
    {
        lemarado->kov = mozgo->kov;
        free(mozgo);
        return lista;
    }
}

// hogyha létezik a asztalok.txt fájl, akkor azt beolvassa majd elmenti a láncolt listába

AsztalElem *asztal_beolvas(void)
{
    FILE *asztal = fopen("asztalok.txt", "r");
    if (asztal == NULL)
    {
        printf("Hiba: nem lehet megnyitni az asztalok.txt fájlt!\n");
        return NULL;
    }
    char bufferRendelesek[500];
    int asztalid;
    int ferohely;
    int sor;
    int oszlop;
    int foglalt;

    AsztalElem *lista = NULL;

    while (fscanf(asztal, "%d;%d;%d;%d;%d;%499[^\n]\n", &asztalid, &ferohely, &sor, &oszlop, &foglalt, bufferRendelesek) == 6)
    {
        AsztalElem *ujelem;
        ujelem = (AsztalElem *)malloc(sizeof(AsztalElem));
        if (foglalt == 0)
            ujelem->rendelesek = NULL;
        else
        {
            if (strcmp(bufferRendelesek, "null") == 0)
                ujelem->rendelesek = NULL;
            else
                ujelem->rendelesek = rendelesek_beolvas(bufferRendelesek);
        }
        ujelem->sor = sor;
        ujelem->oszlop = oszlop;
        ujelem->id = asztalid;
        ujelem->ferohely = ferohely;
        ujelem->foglalt = foglalt;
        ujelem->kov = lista;
        lista = ujelem;
    }

    fclose(asztal);
    return lista;
}

void asztal_felszabadit(AsztalElem *lista)
{
    AsztalElem *iter = lista;
    while (iter != NULL)
    {
        AsztalElem *kov = iter->kov;
        rendeles_felszabadit(iter->rendelesek);
        free(iter);
        iter = kov;
    }
}

void kiiroasztalok(AsztalElem *lista)
{
    AsztalElem *iter = lista;
    while (iter != NULL)
    {
        AsztalElem *kov = iter->kov;
        printf("%d %d %d %d %d", iter->id, iter->ferohely, iter->sor, iter->oszlop, iter->foglalt);
        kiirorendelesek(iter->rendelesek);
        printf("\n");
        iter = kov;
    }
}

AsztalElem *szabad_hely_keres(AsztalElem *lista, int letszam)
{
    AsztalElem *iter = lista;
    while (iter != NULL)
    {
        AsztalElem *kov = iter->kov;
        if (iter->ferohely == letszam && iter->foglalt == 0)
        {
            iter->foglalt = 1;
            return iter;
        }
        iter = kov;
    }
    return NULL;
}

AsztalElem *asztal_kereso(AsztalElem *lista, int id)
{
    AsztalElem *iter = lista;
    while (iter != NULL)
    {
        AsztalElem *kov = iter->kov;
        if (iter->id == id && iter->foglalt == 1)
        {
            return iter;
        }
        iter = kov;
    }
    return NULL;
}

bool asztal_letezik_id(AsztalElem *lista, int id)
{
    AsztalElem *iter = lista;
    while (iter != NULL)
    {
        if (iter->id == id)
            return true;
        iter = iter->kov;
    }
    return false;
}

AsztalElem *asztal_eldonto(AsztalElem *lista)
{
    if (asztal_letezik())
    {
        lista = asztal_beolvas();
    }
    else
    {
        int id_buffer, ferohely_buffer, sor, oszlop;

        printf("Asztalok letrehozasa (0 ferohely a befejezeshez):\n");
        while (true)
        {
            printf("Asztal sorszama, ferohelyek szama, sor, oszlop: ");
            if (scanf("%d %d %d %d", &id_buffer, &ferohely_buffer, &sor, &oszlop) != 4)
            {
                break;
            }
            if (ferohely_buffer == 0)
            {
                break;
            }
            lista = asztal_letrehoz(lista, id_buffer, ferohely_buffer, sor, oszlop, 0);
        }
    }

    return lista;
}

void asztalok_elment(AsztalElem *lista)
{
    FILE *asztalokment = fopen("asztalok.txt", "w");
    if (asztalokment == NULL)
    {
        printf("Nem lehet menteni az asztalok.txt fájlt!\n");
        return;
    }

    AsztalElem *iter = lista;
    while (iter != NULL)
    {
        char rendeles_str[500] = "";
        RendelesElem *r_iter = iter->rendelesek;
        bool elso = true;

        while (r_iter != NULL)
        {
            if (!elso)
                strcat(rendeles_str, ",");
            char temp[150];
            sprintf(temp, "%s:%d", r_iter->rendelesnev, r_iter->darab);
            strcat(rendeles_str, temp);
            elso = false;
            r_iter = r_iter->kov;
        }
        if (strcmp(rendeles_str, "") == 0)
            fprintf(asztalokment, "%d;%d;%d;%d;%d;null\n",
                    iter->id, iter->ferohely, iter->sor,
                    iter->oszlop, iter->foglalt);
        else
            fprintf(asztalokment, "%d;%d;%d;%d;%d;%s\n",
                    iter->id, iter->ferohely, iter->sor,
                    iter->oszlop, iter->foglalt, rendeles_str);

        iter = iter->kov;
    }
    fclose(asztalokment);
}

int maxsor(AsztalElem *lista)
{
    AsztalElem *iter = lista;
    int max = iter->sor;
    while (iter != NULL)
    {
        AsztalElem *kov = iter->kov;
        if (iter->sor > max)
            max = iter->sor;
        iter = kov;
    }
    return max;
}

int maxoszlop(AsztalElem *lista)
{
    AsztalElem *iter = lista;
    int max = iter->oszlop;
    while (iter != NULL)
    {
        AsztalElem *kov = iter->kov;
        if (iter->oszlop > max)
            max = iter->oszlop;
        iter = kov;
    }
    return max;
}