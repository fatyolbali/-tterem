#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../debug/debugmalloc.h"
#include "../strukturak/strukturak.h"
#include "../fajlkezeles/menu_kezelese/menu.h"
#include "../fajlkezeles/asztal_kezelese/asztal.h"
#include "../fajlkezeles/asztal_kezelese/rendeles.h"
#include "../opciok/ujvendeg.h"
#include "../opciok/meglevovendeg.h"
#include "../opciok/fogterkep.h"
#include "../opciok/menukez.h"
#include "../opciok/asztalkez.h"

void buffer_tisztitas()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
    {
    }
}

int egybekeres(void)
{
    int szam = 0;
    while (true)
    {
        printf("Valasztas: ");
        if (scanf("%d", &szam) != 1)
        {
            printf("Helytelen formatum! Kerem, egesz szamot adjon meg 0 es 4 kozott.\n");
            buffer_tisztitas();
        }
        else
        {
            break;
        }
    }
    return szam;
}

void opciok(AsztalElem **lista, MenuElem **etelek, int sorszam)
{
    switch (sorszam)
    {
    case 1:
        ujvendeg(*lista);
        break;
    case 2:
        meglevovendeg(*lista, *etelek);
        break;
    case 3:
        foglaltsagiterkep(*lista);
        break;
    case 4:
        menukezelese(etelek);
        break;
    case 5:
        asztalkezelese(lista);
        break;
    }
}

void fomenu(AsztalElem **lista, MenuElem **etelek)
{
    int sorszam = 0;
    do
    {
        printf("\n============FOMENU============\n");

        printf("\n1. Uj vendeg\n2. Meglevo vendegek\n3. Foglaltsagi terkep\n4. Menu kezelese\n5. Asztalok kezelese\n9. Kilepes\n");
        sorszam = egybekeres();

        opciok(lista, etelek, sorszam);
    } while (sorszam != 9);

    menu_elment(*etelek);
    asztalok_elment(*lista);

    asztal_felszabadit(*lista);
    menu_felszabadit(*etelek);
}

int main(void)
{
    MenuElem *elejem = NULL;
    AsztalElem *elejea = NULL;

    elejem = menu_eldonto(elejem);
    elejea = asztal_eldonto(elejea);

    fomenu(&elejea, &elejem);

    return 0;
}