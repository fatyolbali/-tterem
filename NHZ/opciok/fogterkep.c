#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../debug/debugmalloc.h"
#include "../strukturak/strukturak.h"
#include "../fajlkezeles/menu_kezelese/menu.h"
#include "../fajlkezeles/asztal_kezelese/asztal.h"
#include "../fajlkezeles/asztal_kezelese/rendeles.h"
#include "../fomenu/fomenu.h"

void foglaltsagiterkep(AsztalElem *lista)
{
    printf("\n======FOGLATSAGI TERKEP======\n");

    int max_sor = maxsor(lista);
    int max_oszlop = maxoszlop(lista);

    for (int i = 1; i <= max_sor; i += 1)
    {
        for (int j = 1; j <= max_oszlop; j += 1)
        {
            AsztalElem *iter = lista;
            bool talalt = false;

            while (iter != NULL)
            {
                AsztalElem *kov = iter->kov;
                if (iter->sor == i && iter->oszlop == j)
                {
                    printf("%d. [] foglalt:%d", iter->id, iter->foglalt);
                    talalt = true;
                    break;
                }
                iter = kov;
            }

            if (!talalt)
            {
                printf("       .       ");
            }
            if (j < max_oszlop)
                printf("\t\t");
        }
        printf("\n\n");
    }
}