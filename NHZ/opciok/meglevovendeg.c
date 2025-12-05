#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../debug/debugmalloc.h"
#include "../strukturak/strukturak.h"
#include "../fajlkezeles/menu_kezelese/menu.h"
#include "../fajlkezeles/asztal_kezelese/asztal.h"
#include "../fajlkezeles/asztal_kezelese/rendeles.h"
#include "../fomenu/fomenu.h"

AsztalElem *rendeles(MenuElem *lista, AsztalElem *egyasztal)
{
    char etel[100];
    int db;
    while (true)
    {
        printf("Melyik etelbol szeretne fogyaszatni es mennyit? (END 0 a kilepeshez): ");
        if (scanf("%99s %d", etel, &db) != 2)
        {
            printf("Helytelen formatum! Kerem, adja meg az etel nevet es a darabszamot (pl. Pizza 2).\n");
            buffer_tisztitas();
        }
        else
        {
            break;
        }
    }

    while (!etel_kereso(lista, etel) && db != 0)
    {
        printf("Nem talaltam ilyen etelt!\n");

        while (true)
        {
            printf("Melyik etelbol szeretne fogyaszatni es mennyit? (END 0 a kilepeshez): ");
            if (scanf("%99s %d", etel, &db) != 2)
            {
                printf("Helytelen formetum! Kerem, adja meg az etel nevet es a darabszamot (pl. Pizza 2).\n");
                buffer_tisztitas();
            }
            else
            {
                break;
            }
        }
    }

    RendelesElem *meglevo = rendeles_kereso(egyasztal->rendelesek, etel);

    if (meglevo != NULL)
    {
        meglevo->darab += db;
    }
    else
    {
        egyasztal->rendelesek = rendeles_hozzaad(egyasztal->rendelesek, etel, db);
    }

    return egyasztal;
}

void szamla(MenuElem *etelek, AsztalElem *egyasztal)
{
    printf("\n============SZAMLA============\n");
    if (egyasztal->rendelesek == NULL)
        printf("Nincs rendeles.\n");

    int vegosszeg = 0;
    RendelesElem *iter = egyasztal->rendelesek;
    while (iter != NULL)
    {
        RendelesElem *kov = iter->kov;
        MenuElem *etel = etel_ar(etelek, iter->rendelesnev);
        if (etel != NULL)
        {
            int osszeg = etel->ar * iter->darab;
            printf("%ddb %s: %dFt.\n", iter->darab, iter->rendelesnev, osszeg);
            vegosszeg += osszeg;
        }
        iter = kov;
    }
    printf("------------------------------\n");
    printf("Vegosszeg: %dFt.\n", vegosszeg);
    printf("==============================\n");

    rendeles_felszabadit(egyasztal->rendelesek);
    egyasztal->rendelesek = NULL;
    egyasztal->foglalt = 0;
}

void almenu(int asztalid, AsztalElem *egyasztal, MenuElem *etelek, AsztalElem *lista)
{
    int sorszam = 0;
    if (asztalid != 0)
    {
        do
        {
            printf("\n============ALMENU============\n");
            printf("6. Rendeles\n7. Szamla\n0. Vissza\n");
            sorszam = egybekeres();

            switch (sorszam)
            {
            case 6:
                egyasztal = rendeles(etelek, egyasztal);
                kiirorendelesek(egyasztal->rendelesek);
                break;
            case 7:
                szamla(etelek, egyasztal);
                break;
            }
        } while (sorszam != 0);
    }
}

void meglevovendeg(AsztalElem *lista, MenuElem *etelek)
{
    printf("\n=======MEGLEVO VENDEGEK=======\n");

    int asztalid;
    while (true)
    {
        printf("Melyik asztal (0 a kilepeshez)?: ");
        if (scanf("%d", &asztalid) != 1)
        {
            printf("Helytelen formatum! Kerem, egesz szamot adjon meg.\n");
            buffer_tisztitas();
        }
        else
        {
            break;
        }
    }

    AsztalElem *asztal = asztal_kereso(lista, asztalid);
    while (asztal == NULL && asztalid != 0)
    {
        printf("Nem letezo vagy ures asztal azonositojat adtad meg!\n");

        while (true)
        {
            printf("Melyik asztal (0 a kilepeshez)?: ");
            if (scanf("%d", &asztalid) != 1)
            {
                printf("Helytelen formatum! Kerem, egesz szamot adjon meg.\n");
                buffer_tisztitas();
            }
            else
            {
                break;
            }
        }

        asztal = asztal_kereso(lista, asztalid);
    }

    almenu(asztalid, asztal, etelek, lista);
}