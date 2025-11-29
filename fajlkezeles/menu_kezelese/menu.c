#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "../../debug/debugmalloc.h"
#include "menu.h"

bool menu_letezik(void)
{
    FILE *menu = fopen("../menu.txt", "r");
    if (menu == NULL)
        return false;
    fclose(menu);
    return true;
}

MenuElem *menu_letrehoz(MenuElem *lista, char *neve, int ara)
{
    MenuElem *uj = (MenuElem *)malloc(sizeof(MenuElem));
    uj->nev = (char *)malloc((strlen(neve) + 1) * sizeof(char));
    strcpy(uj->nev, neve);
    uj->ar = ara;
    uj->kov = lista;

    return uj;
}

MenuElem *menu_kitorol(MenuElem *lista, char *neve)
{
    MenuElem *lemarado = NULL;
    MenuElem *mozgo = lista;
    while (mozgo != NULL && strcmp(mozgo->nev, neve) != 0)
    {
        lemarado = mozgo;
        mozgo = mozgo->kov;
    }

    if (mozgo == NULL)
    {
    }
    else if (lemarado == NULL)
    {
        MenuElem *ujeleje = mozgo->kov;
        free(mozgo);
        lista = ujeleje;
    }
    else
    {
        lemarado->kov = mozgo->kov;
        free(mozgo);
    }

    return lista;
}

MenuElem *menu_valtoztat(MenuElem *lista, char *neve, int ara)
{
    MenuElem *iter = lista;
    while (iter != NULL)
    {
        MenuElem *kov = iter->kov;
        if (strcmp(iter->nev, neve) == 0)
        {
            iter->ar = ara;
            return lista;
        }
        iter = kov;
    }
    return NULL;
}

MenuElem *menu_beolvas(void)
{
    FILE *menu = fopen("../menu.txt", "r");
    if (menu == NULL)
    {
        printf("Hiba: nem lehet megnyitni a menu.txt fájlt!\n");
        return NULL;
    }

    char buffer[100];
    int etel_ara;
    MenuElem *lista = NULL;

    while (fscanf(menu, "%99[^;];%d", buffer, &etel_ara) == 2)
    {
        int c = fgetc(menu);
        if (c != '\n' && c != EOF)
            ungetc(c, menu);

        MenuElem *ujelem = (MenuElem *)malloc(sizeof(MenuElem));
        ujelem->nev = (char *)malloc((strlen(buffer) + 1) * sizeof(char));
        strcpy(ujelem->nev, buffer);
        ujelem->ar = etel_ara;
        ujelem->kov = lista;
        lista = ujelem;
    }

    fclose(menu);
    return lista;
}

void menu_felszabadit(MenuElem *lista)
{
    MenuElem *iter = lista;
    while (iter != NULL)
    {
        MenuElem *kov = iter->kov;
        free(iter->nev);
        free(iter);
        iter = kov;
    }
}

void kiiromenu(MenuElem *lista)
{
    MenuElem *iter = lista;
    while (iter != NULL)
    {
        MenuElem *kov = iter->kov;
        printf("%s %d\n", iter->nev, iter->ar);
        iter = kov;
    }
}

MenuElem *menu_eldonto(MenuElem *lista)
{
    if (menu_letezik())
    {
        lista = menu_beolvas();
    }
    else
    {
        char nev_buffer[100];
        int ar_buffer;

        printf("Menü létrehozása (0 ár a befejezéshez):\n");
        while (true)
        {
            printf("Étel neve és ára: ");
            if (scanf("%99s %d", nev_buffer, &ar_buffer) != 2)
            {
                break;
            }
            if (ar_buffer == 0)
            {
                break;
            }
            lista = menu_letrehoz(lista, nev_buffer, ar_buffer);
        }
    }

    return lista;
}

bool etel_kereso(MenuElem *lista, char *keresett)
{
    MenuElem *iter = lista;
    while (iter != NULL)
    {
        MenuElem *kov = iter->kov;
        if (strcmp(iter->nev, keresett) == 0)
        {
            return true;
        }
        iter = kov;
    }
    return false;
}

MenuElem *etel_ar(MenuElem *lista, char *keresett)
{
    MenuElem *iter = lista;
    while (iter != NULL)
    {
        MenuElem *kov = iter->kov;
        if (strcmp(iter->nev, keresett) == 0)
            return iter;
        iter = kov;
    }
    return NULL;
}

void menu_elment(MenuElem *lista)
{
    FILE *menument = fopen("../menu.txt", "w");
    MenuElem *iter = lista;
    while (iter != NULL)
    {
        MenuElem *kov = iter->kov;
        fprintf(menument, "%s;%d\n", iter->nev, iter->ar);
        iter = kov;
    }
    fclose(menument);
}