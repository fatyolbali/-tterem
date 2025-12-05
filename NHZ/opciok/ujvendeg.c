#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../debug/debugmalloc.h"
#include "../strukturak/strukturak.h"
#include "../fajlkezeles/menu_kezelese/menu.h"
#include "../fajlkezeles/asztal_kezelese/asztal.h"
#include "../fajlkezeles/asztal_kezelese/rendeles.h"
#include "../fomenu/fomenu.h"

void ujvendeg(AsztalElem *lista)
{
    printf("\n===========UJ VENDEG==========\n");

    int vendegszam;

    while (true)
    {
        printf("Hanyan jottek? (0 a kilepeshez): ");
        if (scanf("%d", &vendegszam) != 1)
        {
            printf("Helytelen formatum! Kerem, egesz szamot adjon meg.\n");
            buffer_tisztitas();
        }
        else
        {
            break;
        }
    }

    AsztalElem *szabad = szabad_hely_keres(lista, vendegszam);
    while (szabad == NULL && vendegszam != 0)
    {
        printf("Nincsen szabad hely!\n");

        while (true)
        {
            printf("Hanyan jottek? (0 a kilepeshez): ");
            if (scanf("%d", &vendegszam) != 1)
            {
                printf("Helytelen formatum! Kerem, egesz szamot adjon meg.\n");
                buffer_tisztitas();
            }
            else
            {
                break;
            }
        }

        szabad = szabad_hely_keres(lista, vendegszam);
    }
    if (vendegszam != 0)
        printf("Van szabad hely onoknek. A %d. asztalhoz le is ulhetnek.\n", szabad->id);
}