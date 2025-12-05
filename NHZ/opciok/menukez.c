#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../debug/debugmalloc.h"
#include "../strukturak/strukturak.h"
#include "../fajlkezeles/menu_kezelese/menu.h"
#include "../fajlkezeles/asztal_kezelese/asztal.h"
#include "../fajlkezeles/asztal_kezelese/rendeles.h"
#include "../fomenu/fomenu.h"

void menukezelese(MenuElem **lista)
{
    int sorszam = 0;
    char buffernev[100];
    int ar = 0;
    do
    {
        printf("\n======MENU KEZELESE======\n");
        printf("1. Hozzaadas\n2. Torles\n3. Valtoztatas\n4. Kiiras\n0. Vissza\n");

        sorszam = egybekeres();

        switch (sorszam)
        {
        case 1:
            printf("Uj etel neve es ara: ");
            if (scanf("%99s %d", buffernev, &ar) != 2)
            {
                printf("Helytelen formatum! Kerem egy etel/ital nevet es arat adja meg (Pl: Langos 3000)\n");
                buffer_tisztitas();
            }
            else
            {
                if (etel_kereso(*lista, buffernev))
                {
                    printf("Ez az etel mar letezik! Hasznald a 'Valtoztatas' menupontot!\n");
                }
                else
                {
                    *lista = menu_letrehoz(*lista, buffernev, ar);
                    printf("Uj etel sikeresen hozzaadva: %s (%d Ft)\n", buffernev, ar);
                }
            }
            break;
        case 2:
            printf("Torlendo etel neve: ");
            if (scanf("%99s", buffernev) != 1)
            {
                printf("Helytelen formatum! Kerem egy etel/ital nevet adja meg (Pl: Pizza)\n");
                buffer_tisztitas();
            }
            else
            {
                MenuElem *regi_lista = *lista;
                *lista = menu_kitorol(*lista, buffernev);
                if (*lista == regi_lista && *lista != NULL)
                {
                    printf("Nincs ilyen nevu etel a menuben: %s\n", buffernev);
                }
                else
                {
                    printf("Az etel (%s) sikeresen torolve!\n", buffernev);
                }
            }
            break;
        case 3:
            printf("Melyik etel arat akarod valtoztatni es mennyire: ");
            if (scanf("%99s %d", buffernev, &ar) != 2)
            {
                printf("Helytelen formatum!\n");
                buffer_tisztitas();
            }
            else
            {
                MenuElem *eredmeny = menu_valtoztat(*lista, buffernev, ar);
                if (eredmeny == NULL)
                {
                    printf("Nincs ilyen nevu etel a menuben: %s\n", buffernev);
                }
                else
                {
                    printf("Az etel (%s) ara sikeresen %d Ft-ra modositva.\n", buffernev, ar);
                }
            }
            break;
        case 4:
            kiiromenu(*lista);
            break;
        }
    } while (sorszam != 0);
}
