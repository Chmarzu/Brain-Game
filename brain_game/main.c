#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <time.h>

//Wymiary tabeli tab_mapa
#define WIERSZ 5
#define KOLUMNA 23
#define GLEBOKOSC 2

int ekran_powitalny(int linia, int tab);

void gra(int linia, int tab, int *pzwrot, int *ptab_stat);
void inic_mapa(int i, char *ptab_mapa);
void ekran_gry(int i, int j, int k, int linia, int ruch, int *ptab_stat, char *ptab_mapa);
void reakcja(int i, int j, int k, int linia, int tab, int *pzwrot, int *pruch, int *ptab_stat, char *ptab_mapa);
void instrukcja(int i, int linia, int tab, int *ptab_legenda);
void atrybut();
void test(int i, int j, int *pzwrot, int *pruch, char *ptab_mapa);

void ekran_koncowy(int linia, int tab, int *ptab_stat);

void suwak(int linia);
void tabulator(int tab);

int main() {

    //Sekcja zmiennych
    /*
     zwrot - wynik funkcji "ekran_powitalny"
     linia - ilosc przesuwanych linijek w funkcji "suwak"
     tab - ilosc wykonywanych tabulacji w funkcji "tabulator"
    */
    int zwrot, *pzwrot, linia = 3, tab = 3;
    pzwrot = &zwrot;

    /*
    Tablica z wartościami statystyk oraz jej wskaznik
    Kolejnosc: Inteligencja, Empatia, Sprawnosc, Pamiec, Wyobraznia, Urok
     */
    int tab_stat[6] = {0, 0, 0, 0, 0, 0}, *ptab_stat;
    ptab_stat = &tab_stat[0];

    srand(time(NULL));

    //Ekran powitalny
    zwrot = ekran_powitalny(linia, tab);
    if (!zwrot) {
        ekran_koncowy(linia, tab, ptab_stat);
        return 0;
    }

    //Gra
    zwrot = 1;
    gra(linia, tab, pzwrot, ptab_stat);

    //Ekran koncowy
    ekran_koncowy(linia, tab, ptab_stat);

    return 0;
}

int ekran_powitalny(int linia, int tab) {
    char bug;

    suwak(linia);
    tabulator(tab);
    printf("Witaj w Mapie Mozgu!\n");
    tabulator(tab);
    printf("Gra ta jest inspirowana mini gra z Growing Up.");
    suwak(linia);
    tabulator(tab);
    printf("Aby przejsc dalej, wcisnij Enter...");

    bug = getchar();
    linia = 40;
    suwak(linia);

    if (bug != '\n') {
        while (bug != '\n') bug = getchar();

        tabulator(tab);
        printf("Nie ladnie psuc gre!\n");
        tabulator(tab);
        printf("Masz ostatnia szanse.");
        linia = 3;
        suwak(linia);
        tabulator(tab);
        printf("Aby przejsc dalej, wcisnij Enter...");

        bug = getchar();
        linia = 40;
        suwak(linia);

        if (bug == '\n') return 1;
        else return 0;
    }
}

void gra(int linia, int tab, int *pzwrot, int *ptab_stat) {
    /*
     * i, j, k - zmienne obslugujace petle
     * zuzyte - warunek przy sprawdzaniu zuzycia elementow
     * ruch - mechanika punktow ruchu
     */
    int i = 0, j = 0, k = 0, *pruch;
    static int ruch = 30;
    pruch = &ruch;

    //Tablica dla elementow wyswietlanych na mapie gry oraz jej wskaznik
    char tab_mapa[WIERSZ][KOLUMNA][GLEBOKOSC], *ptab_mapa;
    ptab_mapa = &tab_mapa[0][0][0];

    do {
        //Inicjalizacja tablicy tab_mapa
        if (*pzwrot == 1) inic_mapa(i, ptab_mapa);

        //Ekran gry
        ekran_gry(i, j, k, linia, ruch, ptab_stat, ptab_mapa);

        //Sekcja interaktywna
        reakcja(i, j, k, linia, tab, pzwrot, pruch, ptab_stat, ptab_mapa);

        //Test mapy gry
        if (*pzwrot == 2) test(i, j, pzwrot, pruch, ptab_mapa);

        linia = 40;
        suwak(linia);

    }
    while (*pzwrot > 0);
}

void inic_mapa(int i, char *ptab_mapa) {
    /*
    los - decyduje ktory atrybut ma zostac zainicjalizowany
    odkryte - ogranicza liczbe odkrytych zwyklych atrybutow
     */
    int los, odkryte = 0;
    char *ptab_mapa2; //dodatkowy wskaznik na tablice tab_mapa

    ptab_mapa2 = ptab_mapa;
    ptab_mapa2++;
    for (i = 0; i < (WIERSZ * KOLUMNA); i++) {
        if (i > 0) {
            ptab_mapa += 2;
            ptab_mapa2 += 2;
        }

        los = rand() % 24 + 0;

        switch (los) {
            case 0:
                *ptab_mapa = 'i';
                break;
            case 1:
                *ptab_mapa = 'e';
                break;
            case 2:
                *ptab_mapa = 's';
                break;
            case 3:
                *ptab_mapa = 'p';
                break;
            case 4:
                *ptab_mapa = 'w';
                break;
            case 5:
                *ptab_mapa = 'u';
                break;
            case 6:
                *ptab_mapa = 'I';
                break;
            case 7:
                *ptab_mapa = 'E';
                break;
            case 8:
                *ptab_mapa = 'S';
                break;
            case 9:
                *ptab_mapa = 'P';
                break;
            case 10:
                *ptab_mapa = 'W';
                break;
            case 11:
                *ptab_mapa = 'U';
                break;
            case 12:
                *ptab_mapa = 'a';
                break;
            case 13:
                *ptab_mapa = 'b';
                break;
            case 14:
                *ptab_mapa = 'c';
                break;
            case 15:
                *ptab_mapa = 'd';
                break;
            case 16:
                *ptab_mapa = 'f';
                break;
            case 17:
                *ptab_mapa = 'g';
                break;
            case 18:
                *ptab_mapa = '$';
                break;
            case 19:
                *ptab_mapa = '^';
                break;
            case 20:
                *ptab_mapa = '#';
                break;
            case 21:
                *ptab_mapa = '@';
                break;
            case 22:
                *ptab_mapa = '+';
                break;
            default:
                *ptab_mapa = ' ';
                break;
        }

        //Usunac do update'a
        *ptab_mapa2 = 'O';
        //if (i == 0) *ptab_mapa2 = 'O';
        /*
        if (*ptab_mapa == ' ') *ptab_mapa2 = 'O';
        else if (odkryte < 3) {
            if (*ptab_mapa == 'i' || *ptab_mapa == 'e' || *ptab_mapa == 's' ||
                *ptab_mapa == 'p' || *ptab_mapa == 'w' || *ptab_mapa == 'u') {
                *ptab_mapa2 = 'O';
                odkryte++;
            }
        } else *ptab_mapa2 = 'Z';
        */
    }
}

void ekran_gry(int i, int j, int k, int linia, int ruch, int *ptab_stat, char *ptab_mapa) {
    int pom = 1; //odpowiada za pomocnicze liczby wokol mapy gry
    char *ptab_mapa2; //dodatkowy wskaznik na tablice tab_mapa
    ptab_mapa2 = ptab_mapa;
    ptab_mapa2++;
    //Statystyki
    printf("\tTwoje statystyki:\n");
    for (i = 0; i < 6; i++) {
        printf("\t");
        switch (i) {
            case 0:
                printf("Inteligencja %d", *ptab_stat);
                break;
            case 1:
                printf("Empatia %d", *ptab_stat);
                break;
            case 2:
                printf("Sprawnosc %d", *ptab_stat);
                break;
            case 3:
                printf("Pamiec %d", *ptab_stat);
                break;
            case 4:
                printf("Wyobraznia %d", *ptab_stat);
                break;
            case 5:
                printf("Urok %d", *ptab_stat);
                break;
            default:
                break;
        }
        ptab_stat++;
    }
    printf("\n\tPozostale punkty ruchow: %d\n", ruch);
    linia = 2;
    suwak(linia);

    //Mapa gry
    for (i = 0; i < (WIERSZ + 4); i++) {
        printf("\t\t");
        //Pomocnicze liczby w poziomie
        if (!i || i == 1 || i == (WIERSZ + 3)) pom = 1;
        if (!i || i == (WIERSZ + 3)) {
            for (j = 0; j < (KOLUMNA); j++) {
                if (!j) for (k = 0; k < 6; k++) printf(" ");
                if (pom < 9) printf("%d   ", pom);
                else printf("%d  ", pom);
                pom++;
            }
            //Rama mapy w poziomie
        } else if (i == 1 || i == (WIERSZ + 2)) {
            for (j = 0; j < (4 * KOLUMNA + 6); j++) {
                if (j < 3) printf(" ");
                else printf("-");
            }
        } else {
            for (j = 0; j < (KOLUMNA + 4); j++) {
                //Pomocnicze liczby w pionie
                if (!j) {
                    if (pom < 10) printf(" %d ", pom);
                    if (pom >= 10) printf("%d ", pom);
                } else if (j == (KOLUMNA + 3)) {
                    printf("%d", pom);
                    pom++;
                } else if (j == 1 || j == (KOLUMNA + 2)) printf("| "); //Rama mapy w pionie
                    //Atrybuty
                else {
                    if (*ptab_mapa2 == 'Z') printf("[*] ");
                    else if (*ptab_mapa == ' ' || *ptab_mapa > 96 && *ptab_mapa < 104 && *ptab_mapa != 'e' || *ptab_mapa == '#') {
                        switch (*ptab_mapa) {
                            case 32:
                                printf("    ");
                                break;
                            case 97:
                                printf("{i} ");
                                break;
                            case 98:
                                printf("{e} ");
                                break;
                            case 99:
                                printf("{s} ");
                                break;
                            case 100:
                                printf("{p} ");
                                break;
                            case 102:
                                printf("{w} ");
                                break;
                            case 103:
                                printf("{u} ");
                                break;
                            case 35:
                                printf("{^} ");
                                break;
                            default:
                                break;
                        }
                    } else printf("[%c] ", *ptab_mapa);
                    ptab_mapa += 2;
                    ptab_mapa2 += 2;
                }
            }
        }
        printf("\n");
    }
    printf("\n\tWybierz element (podaj numer wiersza, a potem kolumny: ""x x"").\n\tAby przejsc do instrukcji, wpisz: ""i"".\n\tJesli chcesz opusic gre, wcisnij Enter...\n");
}

void reakcja(int i, int j, int k, int linia, int tab, int *pzwrot, int *pruch, int *ptab_stat, char *ptab_mapa) {
    /*
     * ptab_mapa2 - pomocniczy wskaznik na tablice tab_mapa
     * tekst - przechowuje tekst wpisany przez gracza
     */
    char tekst = ' ', *ptab_mapa2;

    /*
     * wiersz, kolumna - polozenie elementu wybranego przez gracza
     * odwiersz, odkolumna - przesuniecia indeksu elementu wybranego przez gracza, uzyte przy odkrywaniu nowych elementow na mapie
     */
    int wiersz, kolumna, odwiersz, odkolumna;

    //Tablica dla legendy atrybutow i jej wskaznik
    //Kolejnosc: zwykly atrybut, super atrybut, mega atrybut, hiper atrybut, oko, super oko, zacmienie, bonusowe pkt ruchu
    //{bonus, koszt}
    int tab_legenda[][2] = {{1, 1},
                            {5, 3},
                            {0, 4},
                            {3, 5},
                            {0, 3},
                            {0, 7},
                            {0, 5},
                            {5, 0}};
    int *ptab_legenda;
    ptab_legenda = &tab_legenda[0][0];

    //Modul interaktywny (petla w razie pomylki)

    for (i = 0; i < 3; i++) {
        printf("\t");
        tekst = getchar();

        //Wyjscie z gry
        if (tekst == '\n') {
            *pruch = 0;
            break;
        }
            //Instrukcja
        else if (tekst == 'i' || tekst == 'I') {
            while (tekst != '\n') tekst = getchar();
            instrukcja(i, linia, tab, ptab_legenda);
            break;
        }
            //Wybor atrybutu
        else if (isdigit(tekst) && tekst != '0') {
            for (j = 0; j < 5; j++) {
                switch (j) {
                    case 0:
                        wiersz = tekst - 48;
                        break;
                    case 1:
                        if (isdigit(tekst) && tekst != '0') wiersz = (wiersz * 10) + (tekst - 48);
                        else if (tekst != ' ') break;
                        else j = 5;
                        break;
                    case 2:
                        if (isdigit(tekst) && tekst != '0') kolumna = tekst - 48;
                        if (tekst != ' ');
                        else j = 5;
                        break;
                    case 3:
                        if (isdigit(tekst) && tekst != '0') kolumna = tekst - 48;
                        else j = 5;
                        break;
                    case 4:
                        kolumna = (kolumna * 10) + tekst - 48;
                        j = 5;
                        break;
                    default:
                        j = 5;
                        break;
                }
                tekst = getchar();
            }
            tekst = '\n';
            if (tekst == '\n') {
                wiersz = 2;
                kolumna = 2;
                //tab_mapa[wiersz - 1][kolumna - 1][0];
                ptab_mapa += 2 * ((wiersz - 1) * KOLUMNA + (kolumna - 1));
                ptab_mapa2 = ptab_mapa;
                ptab_mapa2++;
                printf("%c %c", *ptab_mapa, *ptab_mapa2);
                if (*ptab_mapa == ' ' || *ptab_mapa2 == 'Z' ||
                    wiersz > WIERSZ || kolumna > KOLUMNA)
                    printf("\tTen element jest niedostepny!\n");
                else {
                    i = 3;
                    //atrybut();
                }
            }
            else {
                printf("\tBledne wartosci!\n");
                while (tekst != '\n') tekst = getchar();
            }
        }
        else if (tekst == 'p') {
            *pzwrot = 1;
            break;
        }
        else {
            printf("\tBledne wartosci!\n");
            while (tekst != '\n') tekst = getchar();
        }
    }
    if (tekst != 'p') *pzwrot = 2;
    else while (tekst != '\n') tekst = getchar();
}

void instrukcja(int i, int linia, int tab, int *ptab_legenda) {
    int *ptab_legenda2;
    ptab_legenda2 = ptab_legenda;
    ptab_legenda2++;
    char tekst;

    linia = 40;
    suwak(linia);
    tabulator(tab);
    printf("Instrukcja:\n");
    for (i = 0; i < 8; i++) {
        printf("\t");
        switch (i) {
            case 0:
                printf("[x]: ");
                break;
            case 1:
                printf("[X]: ");
                break;
            case 2:
                printf("{x}: ");
                break;
            case 3:
                printf("[$]: ");
                break;
            case 4:
                printf("[^]: ");
                break;
            case 5:
                printf("{^}: ");
                break;
            case 6:
                printf("[@]: ");
                break;
            case 7:
                printf("[+]: ");
                break;
            default:
                printf("[ ]: ");
                break;
        }
        if (i == 3)
            printf("+%d pkt wszystkich umiejetnosci, -%d pkt ruchu\n", *ptab_legenda,
                   *ptab_legenda2);
        else {
            if (*ptab_legenda && *ptab_legenda2)
                printf("+%d pkt umiejetnosci, -%d pkt ruchu\n", *ptab_legenda, *ptab_legenda2);
            else if (*ptab_legenda) printf("+%d pkt umiejetnosci\n", *ptab_legenda);
            else printf("-%d pkt ruchu\n", *ptab_legenda2);
        }
    }
    printf("\n\tAby wrocic do gry, wcisnij Enter...");
    tekst = getchar();
    while (tekst != '\n') tekst = getchar();
}

/*void atrybut() {
    //Zmiana statystyk i dezaktywacja elementu
    switch (tab_mapa[wiersz - 1][kolumna - 1][0]) {
        //Zwykle atrybuty
        case 105:
            if (ruch < tab_legenda[0][1]) {
                printf("Za malo punktow ruchu!\n");
                i = 0;
            } else {
                ruch -= tab_legenda[0][1];
                tab_stat[0] += tab_legenda[0][0];
                tab_mapa[wiersz - 1][kolumna - 1][0] = ' ';
            }
            break;
        case 101:
            if (ruch < tab_legenda[0][1]) {
                printf("Za malo punktow ruchu!\n");
                i = 0;
            } else {
                ruch -= tab_legenda[0][1];
                tab_stat[1] += tab_legenda[0][0];
                tab_mapa[wiersz - 1][kolumna - 1][0] = ' ';
            }
            break;
        case 115:
            if (ruch < tab_legenda[0][1]) {
                printf("Za malo punktow ruchu!\n");
                i = 0;
            } else {
                ruch -= tab_legenda[0][1];
                tab_stat[2] += tab_legenda[0][0];
                tab_mapa[wiersz - 1][kolumna - 1][0] = ' ';
            }
            break;
        case 112:
            if (ruch < tab_legenda[0][1]) {
                printf("Za malo punktow ruchu!\n");
                i = 0;
            } else {
                ruch -= tab_legenda[0][1];
                tab_stat[3] += tab_legenda[0][0];
                tab_mapa[wiersz - 1][kolumna - 1][0] = ' ';
            }
            break;
        case 119:
            if (ruch < tab_legenda[0][1]) {
                printf("Za malo punktow ruchu!\n");
                i = 0;
            } else {
                ruch -= tab_legenda[0][1];
                tab_stat[4] += tab_legenda[0][0];
                tab_mapa[wiersz - 1][kolumna - 1][0] = ' ';
            }
            break;
        case 117:
            if (ruch < tab_legenda[0][1]) {
                printf("Za malo punktow ruchu!\n");
                i = 0;
            } else {
                ruch -= tab_legenda[0][1];
                tab_stat[5] += tab_legenda[0][0];
                tab_mapa[wiersz - 1][kolumna - 1][0] = ' ';
            }
            break;
            //Super atrybuty
        case 73:
            if (ruch < tab_legenda[1][1]) {
                printf("Za malo punktow ruchu!\n");
                i = 0;
            } else {
                ruch -= tab_legenda[1][1];
                tab_stat[0] += tab_legenda[1][0];
                tab_mapa[wiersz - 1][kolumna - 1][0] = ' ';
            }
            break;
        case 69:
            if (ruch < tab_legenda[1][1]) {
                printf("Za malo punktow ruchu!\n");
                i = 0;
            } else {
                ruch -= tab_legenda[1][1];
                tab_stat[1] += tab_legenda[1][0];
                tab_mapa[wiersz - 1][kolumna - 1][0] = ' ';
            }
            break;
        case 83:
            if (ruch < tab_legenda[1][1]) {
                printf("Za malo punktow ruchu!\n");
                i = 0;
            } else {
                ruch -= tab_legenda[1][1];
                tab_stat[2] += tab_legenda[1][0];
                tab_mapa[wiersz - 1][kolumna - 1][0] = ' ';
            }
            break;
        case 80:
            if (ruch < tab_legenda[1][1]) {
                printf("Za malo punktow ruchu!\n");
                i = 0;
            } else {
                ruch -= tab_legenda[1][1];
                tab_stat[3] += tab_legenda[1][0];
                tab_mapa[wiersz - 1][kolumna - 1][0] = ' ';
            }
            break;
        case 87:
            if (ruch < tab_legenda[1][1]) {
                printf("Za malo punktow ruchu!\n");
                i = 0;
            } else {
                ruch -= tab_legenda[1][1];
                tab_stat[4] += tab_legenda[1][0];
                tab_mapa[wiersz - 1][kolumna - 1][0] = ' ';
            }
            break;
        case 85:
            if (ruch < tab_legenda[1][1]) {
                printf("Za malo punktow ruchu!\n");
                i = 0;
            } else {
                ruch -= tab_legenda[1][1];
                tab_stat[5] += tab_legenda[1][0];
                tab_mapa[wiersz - 1][kolumna - 1][0] = ' ';
            }
            break;
            //Mega atrybuty
        case 97:
            if (ruch < tab_legenda[2][1]) {
                printf("Za malo punktow ruchu!\n");
                i = 0;
            } else {
                ruch -= tab_legenda[2][1];
                for (j = 0; j < WIERSZ; ++j) {
                    for (int k = 0; k < KOLUMNA; ++k) {
                        if (tab_mapa[j][k][1] == 'O') {
                            if (tab_mapa[j][k][0] == 'i') {
                                tab_stat[0] += tab_legenda[0][0];
                                tab_mapa[j][k][0] = ' ';
                            }
                        }
                    }
                }
                tab_mapa[wiersz - 1][kolumna - 1][0] = ' ';
            }
            break;
        case 98:
            if (ruch < tab_legenda[2][1]) {
                printf("Za malo punktow ruchu!\n");
                i = 0;
            } else {
                ruch -= tab_legenda[2][1];
                for (j = 0; j < WIERSZ; ++j) {
                    for (int k = 0; k < KOLUMNA; ++k) {
                        if (tab_mapa[j][k][1] == 'O') {
                            if (tab_mapa[j][k][0] == 'e') {
                                tab_stat[1] += tab_legenda[0][0];
                                tab_mapa[j][k][0] = ' ';
                            }
                        }
                    }
                }
                tab_mapa[wiersz - 1][kolumna - 1][0] = ' ';
            }
            break;
        case 99:
            if (ruch < tab_legenda[2][1]) {
                printf("Za malo punktow ruchu!\n");
                i = 0;
            } else {
                ruch -= tab_legenda[2][1];
                for (j = 0; j < WIERSZ; ++j) {
                    for (int k = 0; k < KOLUMNA; ++k) {
                        if (tab_mapa[j][k][1] == 'O') {
                            if (tab_mapa[j][k][0] == 's') {
                                tab_stat[2] += tab_legenda[0][0];
                                tab_mapa[j][k][0] = ' ';
                            }
                        }
                    }
                }
                tab_mapa[wiersz - 1][kolumna - 1][0] = ' ';
            }
            break;
        case 100:
            if (ruch < tab_legenda[2][1]) {
                printf("Za malo punktow ruchu!\n");
                i = 0;
            } else {
                ruch -= tab_legenda[2][1];
                for (j = 0; j < WIERSZ; ++j) {
                    for (int k = 0; k < KOLUMNA; ++k) {
                        if (tab_mapa[j][k][1] == 'O') {
                            if (tab_mapa[j][k][0] == 'p') {
                                tab_stat[3] += tab_legenda[0][0];
                                tab_mapa[j][k][0] = ' ';
                            }
                        }
                    }
                }
                tab_mapa[wiersz - 1][kolumna - 1][0] = ' ';
            }
            break;
        case 102:
            if (ruch < tab_legenda[2][1]) {
                printf("Za malo punktow ruchu!\n");
                i = 0;
            } else {
                ruch -= tab_legenda[2][1];
                for (j = 0; j < WIERSZ; ++j) {
                    for (int k = 0; k < KOLUMNA; ++k) {
                        if (tab_mapa[j][k][1] == 'O') {
                            if (tab_mapa[j][k][0] == 'w') {
                                tab_stat[4] += tab_legenda[0][0];
                                tab_mapa[j][k][0] = ' ';
                            }
                        }
                    }
                }
                tab_mapa[wiersz - 1][kolumna - 1][0] = ' ';
            }
            break;
        case 103:
            if (ruch < tab_legenda[2][1]) {
                printf("Za malo punktow ruchu!\n");
                i = 0;
            } else {
                ruch -= tab_legenda[2][1];
                for (j = 0; j < WIERSZ; ++j) {
                    for (int k = 0; k < KOLUMNA; ++k) {
                        if (tab_mapa[j][k][1] == 'O') {
                            if (tab_mapa[j][k][0] == 'u') {
                                tab_stat[5] += tab_legenda[0][0];
                                tab_mapa[j][k][0] = ' ';
                            }
                        }
                    }
                }
                tab_mapa[wiersz - 1][kolumna - 1][0] = ' ';
            }
            break;
            //Hiper atrybut
        case 36:
            if (ruch < tab_legenda[3][1]) {
                printf("Za malo punktow ruchu!\n");
                i = 0;
            } else {
                ruch -= tab_legenda[3][1];
                for (j = 0; j < 6; ++j) tab_stat[j] += tab_legenda[3][0];
                tab_mapa[wiersz - 1][kolumna - 1][0] = ' ';
            }
            break;
            //Oko
        case 94:
            if (ruch < tab_legenda[4][1]) {
                printf("Za malo punktow ruchu!\n");
                i = 0;
            } else {
                ruch -= tab_legenda[4][1];
            }
            break;
            //Super oko
        case 35:
            if (ruch < tab_legenda[5][1]) {
                printf("Za malo punktow ruchu!\n");
                i = 0;
            } else {
                ruch -= tab_legenda[5][1];
            }
            break;
            //Zacmienie
        case 64:
            if (ruch < tab_legenda[6][1]) {
                printf("Za malo punktow ruchu!\n");
                i = 0;
            } else {
                ruch -= tab_legenda[6][1];
                tab_mapa[wiersz - 1][kolumna - 1][0] = ' ';
            }
            break;
            //Bonus do punktow ruchu
        case 43:
            ruch += tab_legenda[7][0];
            tab_mapa[wiersz - 1][kolumna - 1][0] = ' ';
            break;
        default:
            break;
    }
    //Odkrywanie elementow wokol wybranego
    if (tab_mapa[wiersz - 1][kolumna - 1][0] == ' ') {
        for (j = 0; j < 8; ++j) {
            if (!j) {
                odwiersz = -1;
                odkolumna = -1;
            } else if (j == 3 || j == 5) {
                odwiersz++;
                odkolumna = -1;
            } else if (j == 4) odkolumna += 2;
            else odkolumna++;
            if (tab_mapa[(wiersz - 1) + odwiersz][(kolumna - 1) + odkolumna][1] != 'O' &&
                (wiersz - 1) + odwiersz >= 0 && (kolumna - 1) + odkolumna >= 0 &&
                (wiersz - 1) + odwiersz <= WIERSZ - 1 &&
                (kolumna - 1) + odkolumna <= KOLUMNA - 1)
                tab_mapa[(wiersz - 1) + odwiersz][(kolumna - 1) + odkolumna][1] = 'O';
        }
    }
        //Odkrywanie elementow dla oka
    else if (tab_mapa[wiersz - 1][kolumna - 1][0] == '^') {
        for (j = 0; j < 24; ++j) {
            if (!j) {
                odwiersz = -2;
                odkolumna = -2;
            } else if (j == 5 || j == 10 || j == 14 || j == 19) {
                odwiersz++;
                odkolumna = -2;
            } else if (j == 12) odkolumna += 2;
            else odkolumna++;
            if (tab_mapa[(wiersz - 1) + odwiersz][(kolumna - 1) + odkolumna][1] != 'O' &&
                (wiersz - 1) + odwiersz >= 0 && (kolumna - 1) + odkolumna >= 0 &&
                (wiersz - 1) + odwiersz <= WIERSZ - 1 &&
                (kolumna - 1) + odkolumna <= KOLUMNA - 1)
                tab_mapa[(wiersz - 1) + odwiersz][(kolumna - 1) + odkolumna][1] = 'O';
        }
        tab_mapa[wiersz - 1][kolumna - 1][0] = ' ';
    }
        //Odkrywanie elementow dla super oka
    else {
        for (j = 0; j < WIERSZ; j++) {
            for (k = 0; k < KOLUMNA; k++) {
                if (tab_mapa[j][k][1] == 'Z') tab_mapa[j][k][1] = 'O';
            }
        }
        tab_mapa[wiersz - 1][kolumna - 1][0] = ' ';
    }
}*/

void test(int i, int j, int *pzwrot, int *pruch, char *ptab_mapa) {
    int zuzyte = 0;
    char *ptab_mapa2; //dodatkowy wskaznik na tablice tab_mapa
    ptab_mapa2 = ptab_mapa;
    ptab_mapa2++;

    //Sprawdzenie liczby pkt ruchu
    if (!*pruch) *pzwrot = 0;

        //Sprawdzenie liczby zuzytych elementow
    else {
        for (i = 0; i < WIERSZ; i++) {
            for (j = 0; j < KOLUMNA; j++) {
                if (*ptab_mapa2 == 'Z') break;
                else if (*ptab_mapa == ' ') zuzyte++;
            }
        }
        if (zuzyte == (WIERSZ * KOLUMNA)) *pzwrot = 0;
        else *pzwrot = 2;
    }
}

void ekran_koncowy(int linia, int tab, int *ptab_stat) {
    tab = 8;
    tabulator(tab);
    printf("Gratulacje!\n");
    tab = 7;
    tabulator(tab);
    printf("Oto twoj koncowy wynik:\n\n");
    tab = 3;
    tabulator(tab);

    for (int i = 0; i < 6; i++) {
        switch (i) {
            case 0:
                printf("Inteligencja %d", *ptab_stat);
                break;
            case 1:
                printf("Empatia %d", *ptab_stat);
                break;
            case 2:
                printf("Sprawnosc %d", *ptab_stat);
                break;
            case 3:
                printf("Pamiec %d", *ptab_stat);
                break;
            case 4:
                printf("Wyobraznia %d", *ptab_stat);
                break;
            case 5:
                printf("Urok %d", *ptab_stat);
                break;
            default:
                break;
        }
        printf("\t");
        ptab_stat++;
    }
}

//Funkcja "suwak" odpowiada za "czyszczenie ekranu" - przesuwanie tekstu tak, aby nie bylo widac wczesniejszych, niepotrzebnych komunikatow.
void suwak (int linia) {
    for (int i = 0; i < linia; i++) printf("\n");
}

//Funkcja "tabulator" odpowiada za wykonanie tabulacji tekstu
void tabulator (int tab) {
    for (int i = 0; i < tab; i++) printf("\t");
}