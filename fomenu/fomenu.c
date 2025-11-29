#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../debug/debugmalloc.h"
#include "../strukturak/strukturak.h"
#include "../fajlkezeles/menu_kezelese/menu.h"
#include "../fajlkezeles/asztal_kezelese/asztal.h"
#include "../fajlkezeles/asztal_kezelese/rendeles.h"

void buffer_tisztitas()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
    {
    }
}

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
                printf("Helytelen formátum! Kérem, egész számot adjon meg.\n");
                buffer_tisztitas();
            }
            else
            {
                break;
            }
        }

        szabad = szabad_hely_keres(lista, vendegszam);
    }
    if (vendegszam == 0)
        printf("");
    else
        printf("Van szabad hely onoknek. A %d. asztalhoz le is ulhetnek.\n", szabad->id);
}

AsztalElem *rendeles(MenuElem *lista, AsztalElem *egyasztal)
{
    char etel[100];
    int db;
    while (true)
    {
        printf("Melyik etelbol szeretne fogyaszatni es mennyit? (END 0 a kilepeshez): ");
        if (scanf("%s %d", etel, &db) != 2)
        {
            printf("Helytelen formátum! Kérem, adja meg az étel nevét ÉS a darabszámot (pl. Pizza 2).\n");
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
            if (scanf("%s %d", etel, &db) != 2)
            {
                printf("Helytelen formátum! Kérem, adja meg az étel nevét ÉS a darabszámot (pl. Pizza 2).\n");
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

void almenu(int asztalid, int sorszam, AsztalElem *egyasztal, MenuElem *etelek, AsztalElem *lista)
{
    if (asztalid == 0)
        printf("");
    else
    {
        do
        {
            printf("\n============ALMENU============\n");
            printf("6. Rendeles\n7. Szamla\n0. Vissza\n");
            while (true)
            {
                printf("Valasztas: ");
                if (scanf("%d", &sorszam) != 1)
                {
                    printf("Helytelen formátum! Kérem, egész számot adjon meg.\n");
                    buffer_tisztitas();
                }
                else
                {
                    break;
                }
            }

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
    int sorszam;
    while (true)
    {
        printf("Melyik asztal (0 a kilepeshez)?: ");
        if (scanf("%d", &asztalid) != 1)
        {
            printf("Helytelen formátum! Kérem, egész számot adjon meg.\n");
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
                printf("Helytelen formátum! Kérem, egész számot adjon meg.\n");
                buffer_tisztitas();
            }
            else
            {
                break;
            }
        }

        asztal = asztal_kereso(lista, asztalid);
    }

    almenu(asztalid, sorszam, asztal, etelek, lista);
}

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

void menukezelese(MenuElem **lista)
{
    int sorszam = 0;
    char buffernev[100];
    int ar = 0;
    do
    {
        printf("\n======MENU KEZELESE======\n");
        printf("1. Hozzaadas\n2. Torles\n3. Valtoztatas\n0. Vissza\n");

        while (true)
        {
            printf("Valasztas: ");
            if (scanf("%d", &sorszam) != 1)
            {
                printf("Helytelen formátum! Kérem, egész számot adjon meg.\n");
                buffer_tisztitas();
            }
            else
            {
                break;
            }
        }

        switch (sorszam)
        {
        case 1:
            printf("Új étel neve és ára: ");
            if (scanf("%s %d", buffernev, &ar) != 2)
            {
                printf("Helytelen formátum!\n");
                buffer_tisztitas();
            }
            else
            {
                *lista = menu_letrehoz(*lista, buffernev, ar);
            }
            break;
        case 2:
            printf("Törlendő étel neve: ");
            if (scanf("%s", buffernev) != 1)
            {
                printf("Helytelen formátum!\n");
                buffer_tisztitas();
            }
            else
            {
                *lista = menu_kitorol(*lista, buffernev);
            }
            break;
        case 3:
            printf("Melyik etel arat akarod valtoztatni es mennyire: ");
            if (scanf("%s %d", buffernev, &ar) != 2)
            {
                printf("Helytelen formátum!\n");
                buffer_tisztitas();
            }
            else
            {
                *lista = menu_valtoztat(*lista, buffernev, ar);
            }
            break;
        }
    } while (sorszam != 0);
}

void asztalkezelese(AsztalElem **lista)
{
    int sorszam = 0;
    int id = 0;
    int ferohely = 0;
    int sor = 0;
    int oszlop = 0;
    int foglalt = 0;
    do
    {
        printf("\n====ASZTALOK KEZELESE====\n");
        printf("1. Hozzaadas\n2. Torles\n0. Vissza\n");
        while (true)
        {
            printf("Valasztas: ");
            if (scanf("%d", &sorszam) != 1)
            {
                printf("Helytelen formátum! Kérem, egész számot adjon meg.\n");
                buffer_tisztitas();
            }
            else
            {
                break;
            }
        }

        switch (sorszam)
        {
        case 1:
            printf("Új asztal azonositoja, ferohely, sor, oszlop es hogy foglalt-e: ");
            if (scanf("%d %d %d %d %d", &id, &ferohely, &sor, &oszlop, &foglalt) != 5)
            {
                printf("Helytelen formátum! Kérem, 5 egész számot adjon meg.\n");
                buffer_tisztitas();
            }
            else
            {
                *lista = asztal_letrehoz(*lista, id, ferohely, sor, oszlop, foglalt);
            }
            break;
        case 2:
            printf("Törlendő asztal azonositoja: ");
            if (scanf("%d", &id) != 1)
            {
                printf("Helytelen formátum! Kérem, egész számot adjon meg.\n");
                buffer_tisztitas();
            }
            else
            {
                *lista = asztal_kitorol(*lista, id);
            }
            break;
        }
    } while (sorszam != 0);
}

int main(void)
{
    MenuElem *elejem = NULL;
    AsztalElem *elejea = NULL;

    elejem = menu_eldonto(elejem);
    elejea = asztal_eldonto(elejea);
    int sorszam = 0;
    do
    {
        printf("\n============FOMENU============\n");

        printf("\n1. Uj vendeg\n2. Meglevo vendegek\n3. Foglaltsagi terkep\n4. Menu kezelese\n5. Asztalok kezelese\n9. Kilepes\n");
        while (true)
        {
            printf("Valasztas: ");
            if (scanf("%d", &sorszam) != 1)
            {
                printf("Helytelen formátum! Kérem, egész számot adjon meg.\n");
                buffer_tisztitas();
            }
            else
            {
                break;
            }
        }

        switch (sorszam)
        {
        case 1:
            ujvendeg(elejea);
            break;
        case 2:
            meglevovendeg(elejea, elejem);
            break;
        case 3:
            foglaltsagiterkep(elejea);
            break;
        case 4:
            menukezelese(&elejem);
            break;
        case 5:
            asztalkezelese(&elejea);
            break;
        }
    } while (sorszam != 9);

    menu_elment(elejem);
    asztalok_elment(elejea);

    asztal_felszabadit(elejea);
    menu_felszabadit(elejem);
    return 0;
}