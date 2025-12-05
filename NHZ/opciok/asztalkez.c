#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../debug/debugmalloc.h"
#include "../strukturak/strukturak.h"
#include "../fajlkezeles/menu_kezelese/menu.h"
#include "../fajlkezeles/asztal_kezelese/asztal.h"
#include "../fajlkezeles/asztal_kezelese/rendeles.h"
#include "../fomenu/fomenu.h"

void asztalkezelese(AsztalElem **lista)
{
    int sorszam = 0;
    int id = 0;
    int ferohely = 0;
    int sor = 0;
    int oszlop = 0;
    do
    {
        printf("\n====ASZTALOK KEZELESE====\n");
        printf("1. Hozzaadas\n2. Torles\n3. Kiiras\n0. Vissza\n");

        sorszam = egybekeres();

        switch (sorszam)
        {
        case 1:
            printf("Uj asztal azonositoja, ferohelye, sora es oszlopa: ");
            if (scanf("%d %d %d %d", &id, &ferohely, &sor, &oszlop) != 4)
            {
                printf("Helytelen formatum! Kerem, 4 egesz szamot adjon meg.\n");
                buffer_tisztitas();
            }
            else
            {
                if (asztal_letezik_id(*lista, id))
                {
                    printf("Ez az asztal ID mar letezik! Valassz mas azonositot!\n");
                }
                else
                {
                    *lista = asztal_letrehoz(*lista, id, ferohely, sor, oszlop, 0);
                    printf("Uj asztal sikeresen hozzaadva (ID: %d)\n", id);
                }
            }
            break;
        case 2:
            printf("Torlendo asztal azonositoja: ");
            if (scanf("%d", &id) != 1)
            {
                printf("Helytelen formatum!\n");
                buffer_tisztitas();
            }
            else
            {
                bool talalt = false;
                *lista = asztal_kitorol(*lista, id, &talalt);

                if (talalt)
                {
                    printf("Az asztal (ID: %d) sikeresen torolve!\n", id);
                }
                else
                {
                    printf("Nincs ilyen azonositoju asztal a listaban\n");
                }
            }
            break;
        case 3:
            kiiroasztalok(*lista);
            break;
        }
    } while (sorszam != 0);
}