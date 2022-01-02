#include <stdio.h>
#include <ctype.h>

//Wymiary tabeli tab_mapa
#define WIERSZ 10
#define KOLUMNA 23
#define GLEBOKOSC 2

int linia = 3; //Zmienna globalna odpowiadajaca ilosci przesuwanych linijek w funkcji "suwak"
int tab = 3; //Zmienna globalna odpowiadajaca ilosci wykonywanych tabulacji w funkcji "tabulator"

void suwak();
void tabulator();

int main() {

    //Sekcja zmiennych
    //bug - przechowuje tekst wpisany przez gracza
    char bug;

    /*
    i, j, k - zmienne obslugujace petle
    odkryte - ogranicza liczbe odkrytych zwyklych atrybutow, warunek przy sprawdzaniu zuzycia elementow
    ruch - mechanika punktow ruchu, warunek petli glownej czesci gry
    pom - odpowiada za pomocnicze liczby wokol mapy gry
    wiersz, kolumna - polozenie elementu wybranego przez gracza
    odwiersz, odkolumna - przesuniecia indeksu elementu wybranego przez gracza, uzyte przy odkrywaniu nowych elementow na mapie
     */
    int i, j, k, odkryte = 0, ruch = 30, pom = 1, wiersz, kolumna, odwiersz, odkolumna;

    /*
    Tablica z wartościami statystyk
    Kolejnosc: Inteligencja, Empatia, Sprawnosc, Pamiec, Wyobraznia, Urok
     */
    int tab_stat[6] = {0, 0, 0, 0, 0, 0};

    //Tablica dla legendy atrybutow
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

    //Tablica dla elementow wyswietlanych na mapie gry
    char tab_mapa[WIERSZ][KOLUMNA][GLEBOKOSC];
    for (i = 0; i < WIERSZ; i++) {
        for (j = 0; j < KOLUMNA; j++) {
            for (k = 0; k < GLEBOKOSC; k++) {
                if (!k) {
                    switch (j) {
                        case 0:
                            tab_mapa[i][j][k] = 'i';
                            break;
                        case 1:
                            tab_mapa[i][j][k] = 'e';
                            break;
                        case 2:
                            tab_mapa[i][j][k] = 's';
                            break;
                        case 3:
                            tab_mapa[i][j][k] = 'p';
                            break;
                        case 4:
                            tab_mapa[i][j][k] = 'w';
                            break;
                        case 5:
                            tab_mapa[i][j][k] = 'u';
                            break;
                        case 6:
                            tab_mapa[i][j][k] = 'I';
                            break;
                        case 7:
                            tab_mapa[i][j][k] = 'E';
                            break;
                        case 8:
                            tab_mapa[i][j][k] = 'S';
                            break;
                        case 9:
                            tab_mapa[i][j][k] = 'P';
                            break;
                        case 10:
                            tab_mapa[i][j][k] = 'W';
                            break;
                        case 11:
                            tab_mapa[i][j][k] = 'U';
                            break;
                        case 12:
                            tab_mapa[i][j][k] = 'a';
                            break;
                        case 13:
                            tab_mapa[i][j][k] = 'b';
                            break;
                        case 14:
                            tab_mapa[i][j][k] = 'c';
                            break;
                        case 15:
                            tab_mapa[i][j][k] = 'd';
                            break;
                        case 16:
                            tab_mapa[i][j][k] = 'f';
                            break;
                        case 17:
                            tab_mapa[i][j][k] = 'g';
                            break;
                        case 18:
                            tab_mapa[i][j][k] = '$';
                            break;
                        case 19:
                            tab_mapa[i][j][k] = '^';
                            break;
                        case 20:
                            tab_mapa[i][j][k] = '#';
                            break;
                        case 21:
                            tab_mapa[i][j][k] = '@';
                            break;
                        case 22:
                            tab_mapa[i][j][k] = '+';
                            break;
                        default:
                            tab_mapa[i][j][k] = ' ';
                            break;
                    }
                } else {
                    if (tab_mapa[i][j][0] == ' ') tab_mapa[i][j][k] = 'O';
                    else if (odkryte < 3) {
                        if (tab_mapa[i][j][0] == 'i' || tab_mapa[i][j][0] == 'e' || tab_mapa[i][j][0] == 's' ||
                            tab_mapa[i][j][0] == 'p' || tab_mapa[i][j][0] == 'w' || tab_mapa[i][j][0] == 'u') {
                            tab_mapa[i][j][k] = 'O';
                            odkryte++;
                        }
                    } else tab_mapa[i][j][k] = 'Z';
                }
            }
        }
    }

    //Ekran powitalny
    suwak();
    tabulator();
    printf("Witaj w Mapie Mozgu!\n");
    tabulator();
    printf("Gra ta jest inspirowana mini gra z Growing Up.");
    suwak();
    tabulator();
    printf("Aby przejsc dalej, wcisnij Enter...");
    bug = getchar();
    linia = 40;
    suwak();
    if (bug != '\n') {
        while (bug != '\n') bug = getchar();
        tabulator();
        printf("Nie ladnie psuc gre!\n");
        tabulator();
        printf("Masz ostatnia szanse.");
        linia = 3;
        suwak();
        tabulator();
        printf("Aby przejsc dalej, wcisnij Enter...");
        bug = getchar();
        if (bug == '\n') {
            linia = 40;
            suwak();
        } else return 0;
    }

    //Wlasciwa gra
    do {

        //Statystyki
        printf("\tTwoje statystyki:\n");
        printf("\tInteligencja %d\tEmpatia %d\tSprawnosc %d\tPamiec %d\tWyobraznia %d\tUrok %d\n",
               tab_stat[0], tab_stat[1], tab_stat[2], tab_stat[3], tab_stat[4], tab_stat[5]);
        printf("\tPozostale punkty ruchow: %d\n\n", ruch);

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
                        if (tab_mapa[(i - 2)][(j - 2)][1] == 'Z') printf("[*] ");
                        else if (tab_mapa[(i - 2)][(j - 2)][0] > 96 && tab_mapa[(i - 2)][(j - 2)][0] < 104 &&
                                 tab_mapa[(i - 2)][(j - 2)][0] != 101 || tab_mapa[(i - 2)][(j - 2)][0] == 35) {
                            switch (tab_mapa[(i - 2)][(j - 2)][0]) {
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
                        } else printf("[%c] ", tab_mapa[(i - 2)][(j - 2)][0]);
                    }
                }
            }
            printf("\n");
        }

        //Modul interaktywny
        printf("\n\tWybierz element (podaj numer wiersza, a potem kolumny: ""x x"").\n\tAby przejsc do instrukcji, wpisz: ""i"".\n\tJesli chcesz opusic gre, wcisnij Enter...\n");

        //Petla wyboru gracza (w razie pomylki)
        for (i = 0; i < 3; i++) {
            printf("\t");
            bug = getchar();
            //Wyjscie z gry
            if (bug == '\n') {
                ruch = 0;
                break;
                //Instrukcja
            } else if (bug == 'i' || bug == 'I') {
                while (bug != '\n') bug = getchar();
                suwak();
                tabulator();
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
                        printf("+%d pkt wszystkich umiejetnosci, -%d pkt ruchu\n", tab_legenda[i][0],
                               tab_legenda[i][1]);
                    else {
                        if (tab_legenda[i][0] && tab_legenda[i][1])
                            printf("+%d pkt umiejetnosci, -%d pkt ruchu\n", tab_legenda[i][0], tab_legenda[i][1]);
                        else if (tab_legenda[i][0]) printf("+%d pkt umiejetnosci\n", tab_legenda[i][0]);
                        else printf("-%d pkt ruchu\n", tab_legenda[i][1]);
                    }
                }
                printf("\n\tJesli chcesz wrocic do gry, wcisnij Enter...");
                bug = getchar();
                while (bug != '\n') bug = getchar();
                break;
                //Wybor atrybutu
            } else if (isdigit(bug)) {
                for (j = 0; j < 4; j++) {
                    if (isdigit(bug) && bug > 48 && bug < 58) {
                        switch (j) {
                            case 0:
                                wiersz = bug - 48;
                                break;
                            case 1:
                                wiersz = (wiersz * 10) + (bug - 48);
                                j--;
                                break;
                            case 2:
                                kolumna = bug - 48;
                                break;
                            case 3:
                                kolumna = (kolumna * 10) + bug - 48;
                                break;
                            default:
                                break;
                        }
                    } else if (bug != ' ') break;
                    bug = getchar();
                }
                if (bug == '\n') {
                    if (tab_mapa[wiersz - 1][kolumna - 1][0] == ' ' ||
                        tab_mapa[wiersz - 1][kolumna - 1][1] == 'Z' ||
                        wiersz > WIERSZ || kolumna > KOLUMNA)
                        printf("\tTen element jest niedostepny!\n");
                        //Reakcja programu na wybranie wlasciwego elementu
                    else {
                        //Zakończenie pętli
                        i = 3;
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
                    }
                } else {
                    printf("\tBledne wartosci!\n");
                    while (bug != '\n') bug = getchar();
                }
            } else {
                printf("\tBledne wartosci!\n");
                while (bug != '\n') bug = getchar();
            }
        }
        suwak();
        //Sprawdzenie liczby zuzytych elementow
        odkryte = 0;
        for (i = 0; i < WIERSZ; i++) {
            for (j = 0; j < KOLUMNA; j++) {
                if (tab_mapa[i][j][1] == 'Z') break;
                else if (tab_mapa[i][j][0] == ' ') odkryte++;
                if (odkryte == (WIERSZ * KOLUMNA)) ruch = 0;
            }
        }
    } while (ruch > 0);

    //Ekran koncowy
    tab = 8;
    tabulator();
    printf("Gratulacje!\n");
    tab = 7;
    tabulator();
    printf("Oto twoj koncowy wynik:\n\n");
    tab = 3;
    tabulator();
    printf("Inteligencja %d\tEmpatia %d\tSprawnosc %d\tPamiec %d\tWyobraznia %d\tUrok %d\n", tab_stat[0], tab_stat[1],
           tab_stat[2], tab_stat[3], tab_stat[4], tab_stat[5]);

    return 0;
}

//Funkcja "suwak" odpowiada za "czyszczenie ekranu" - przesuwanie tekstu tak, aby nie bylo widac wczesniejszych, niepotrzebnych komunikatow.
void suwak () {
    for (int i = 0; i < linia; i++) printf("\n");
}

//Funkcja "tabulator" odpowiada za wykonanie tabulacji tekstu
void tabulator () {
    for (int i = 0; i < tab; i++) printf("\t");
}