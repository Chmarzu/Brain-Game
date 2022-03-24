#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

//Wymiary tabeli tab_mapa
#define WIERSZ 7
#define KOLUMNA 23
#define GLEBOKOSC 2

#define RUCH 30     //Liczba punktow ruchu

boolean lang;       //Language version: 0 - English, 1 - polski

int menu_glowne(FILE *pf);

void settings(FILE *pf);

void gra(int *pzwrot, FILE *pf);
void ekran_powitalny();
void inic_mapa(int i, char *ptab_mapa, char *ptab_mapa2);
void ekran_gry(int i, int j, int ruch, int *ptab_stat, char *ptab_mapa, char *ptab_mapa2);

void reakcja(int i, int j, int *pzwrot, int *pruch, int *ptab_stat, char *ptab_mapa, char *ptab_mapa2, char *ptab_mapa3);
void instrukcja(int i, int *ptab_legenda, int *ptab_legenda2);

void atrybut(int i, char *ptab_mapa, char *ptab_mapa2, char *ptab_mapa3, int *ptab_stat, int *ptab_legenda, int *pruch);
void los(int i, char *ptab_mapa, int *ptab_legenda, int *pruch, unsigned short *pbieda);
void zwykly_at(char ptab_mapa, int *ptab_stat, int *ptab_legenda, int *pruch, unsigned short *pbieda);
void super_at(char ptab_mapa, int *ptab_stat, int *ptab_legenda, int *pruch, unsigned short *pbieda);
void mega_at(int i, char ptab_mapa, char *ptab_mapa2, char *ptab_mapa3, int *ptab_stat, int *ptab_legenda, int *pruch, unsigned short *pbieda);
void hiper_at(int i, int *ptab_stat, int *ptab_legenda, int *pruch, unsigned short *pbieda);
void reakcja_lanc(int i, char *ptab_mapa, char *ptab_mapa2, char *ptmp, char *ptmk, int *ptab_legenda, int *pruch, unsigned short *pbieda);
void oko(int i, char *ptab_mapa, char *ptab_mapa2, char *ptmp, char *ptmk);

void test(int i, int *pzwrot, int *pruch, char *ptab_mapa, char *ptab_mapa2);
void ekran_koncowy(int *ptab_stat);

void zapisz_gre(FILE *pf, int const *pruch, int *ptab_stat, char *ptab_mapa, int i, int j);
void wczytaj_gre(FILE *pf, int *pruch, int *ptab_stat, char *ptab_mapa, int i, int j);

void suwak(int linia);
void tabulator(int tab);

int main() {
    int zwrot;      //Wartosc zwracana przez funkcje
    FILE *f;        //Odpowiada za plik zapisu gry

    srand(time(NULL));

    f = fopen("lang.txt", "r");     //Language version control
    if (f != NULL)
        lang = fgetc(f) - 48;
    fclose(f);

    do {
        zwrot = menu_glowne(f);      //Menu glowne
        switch (zwrot) {
            case 1:     //Nowa gra
                zwrot = 2;
                gra(&zwrot, f);
                break;
            case 2:     //Kontynuuj gre
                zwrot = 1;
                gra(&zwrot, f);
                break;
            case 3:     //Ustawienia
                settings(f);
                break;
            case 4:     //Zamkniecie gry
                if (!lang)
                    printf("See you next time!");
                else
                    printf("Do nastepnego razu!");
                Sleep(1000);
                break;
            default:
                printf("Switch error in func main!");
                Sleep(10000);
                suwak(40);
                break;
        }
        suwak(40);
    } while (zwrot != 4);
    return 0;
}

int menu_glowne(FILE *pf) {
    int tekst = 0;      //Opcja wybrana przez gracza
    char sprzatacz;     //Czyszczenie pozostalego wprowadzonego tesktu
    unsigned short save;    //Sprawdzenie wystepowania pliku zapisu: 0 - brak, 1 - istnieje
    int i;      //Dla petli

    pf = fopen("save.txt","r");
    if (pf != NULL)
        save = 1;
    else save = 0;
    fclose(pf);

    for (i = 0; i < 5; i++) {
        tabulator(2);
        switch (i) {
            case 0:
                printf("Brain Game\n\n");
                break;
            case 1:
                if (!lang)
                    printf("(%d) New Game\n", i);
                else
                printf("(%d) Nowa Gra\n", i);
                break;
            case 2:
                if (save) {
                    if (!lang)
                        printf("(%d) Load Game\n", i);
                    else
                        printf("(%d) Wczytaj Gre\n", i);
                } else printf("\r");
                break;
            case 3:
                if (save) {
                    if (!lang)
                        printf("(%d) Settings\n", i);
                    else
                        printf("(%d) Ustawienia\n", i);
                } else {
                    if (!lang)
                        printf("(%d) Settings\n", i + 1);
                    else
                        printf("(%d) Ustawienia\n", i - 1);
                }
                break;
            case 4:
                if (save) {
                    if (!lang)
                        printf("(%d) Quit\n", i);
                    else
                    printf("(%d) Opusc gre\n", i);
                } else {
                    if (!lang)
                        printf("(%d) Quit\n", i + 1);
                    else
                    printf("(%d) Opusc gre\n", i - 1);
                }
                break;
            default:
                printf("Switch error in func main_menu!");
                Sleep(10000);
                suwak(40);
                break;
        }
    }
    scanf("%d", &tekst);
    suwak(40);
    while ((sprzatacz = getchar()) != '\n');
    if (save || tekst == 1)
        return tekst;
    else
        return tekst + 1;
}

void settings(FILE *pf) {
    unsigned char temp;      //Temporary variable used to perform file operations

    tabulator(3);
    if (!lang) {
        printf("Settings\n\n");
        printf("\tLanguage\n");
        printf("\t* English (0)\n");
        printf("\t- polski (1)");
        suwak(3);
        printf("Press Enter to get into Main Menu...\n");
    } else {
        printf("Ustawienia\n\n");
        printf("\tJezyk\n");
        printf("\t- English (0)\n");
        printf("\t* polski (1)");
        suwak(3);
        printf("Wcisnij Enter, aby przejsc do Menu Glownego...\n");
    }
    scanf("%c", &temp);

    if (temp != lang && (temp == '0' || temp == '1')) {
        lang = temp - 48;

        pf = fopen("lang.txt", "w");
        fputc(temp, pf);
        fclose(pf);
    }
}

void gra(int *pzwrot, FILE *pf) {
    /*
     * Znaczenie wartosci zmiennej zwrot:
     * 0 - koniec petli
     * 1 - wczytaj zapis gry
     * 2 - reinicjalizuj tablice tab_mapa
     * 3 - kontynuuj petle bez zmian
     */

    int i = 0, j = 0;    //Zmienne obslugujace petle
    static int ruch = RUCH;   //Mechanika punktow ruchu

    /*
     * Tablica z wartościami statystyk
     * Kolejnosc: Inteligencja, Empatia, Sprawnosc, Pamiec, Wyobraznia, Urok
     */
    int tab_stat[6] = {0, 0, 0, 0, 0, 0};

    //Tablica dla elementow wyswietlanych na mapie gry
    char tab_mapa[WIERSZ][KOLUMNA][GLEBOKOSC];

    ekran_powitalny();

    if (*pzwrot == 1)
        wczytaj_gre(pf, &ruch, &tab_stat[0], &tab_mapa[0][0][0], i, j);

    do {
        //Inicjalizacja tablicy tab_mapa
        if (*pzwrot == 2)
            inic_mapa(i, &tab_mapa[0][0][0], &tab_mapa[0][0][1]);

        //Ekran gry
        ekran_gry(i, j, ruch, &tab_stat[0], &tab_mapa[0][0][0], &tab_mapa[0][0][1]);

        //Sekcja interaktywna
        reakcja(i, j, pzwrot, &ruch, &tab_stat[0], &tab_mapa[0][0][0], &tab_mapa[0][0][0], &tab_mapa[0][0][1]);

        //Test stanu gry
        if (*pzwrot == 3)
            test(i, pzwrot, &ruch, &tab_mapa[0][0][0], &tab_mapa[0][0][1]);

        suwak(40);

    } while (*pzwrot > 0);

    if (*pzwrot < 0)
        zapisz_gre(pf, &ruch, &tab_stat[0], &tab_mapa[0][0][0], i, j);

    ekran_koncowy(&tab_stat[0]);
}

void ekran_powitalny() {
    suwak(3);
    tabulator(4);
    if (!lang)
        printf("Welcome in Brain Game!\n");
    else
        printf("Witaj w Brain Game!\n");
    Sleep(500);
    if (!lang)
        printf("\t\tThis game was inspired by mini-game from game \"Growing Up\".");
    else {
        tabulator(3);
        printf("Gra ta jest inspirowana mini gra z \"Growing Up\".");
    }
    Sleep(1000);
    suwak(40);
}

void inic_mapa(int i, char *ptab_mapa, char *ptab_mapa2) {
    int los;    //Decyduje ktory atrybut ma zostac zainicjalizowany
    int odkryte = 0;    //Ogranicza liczbe odkrytych atrybutow

    for (i = 0; i < (WIERSZ * KOLUMNA); i++) {
        //if (i == 150) los = 24;
        //los = i;
        //los = rand() % 27;

        los = rand() % 3;
        if (los) {
            los = rand() % 100;
            if (los < 50)
                los = rand() % 6;
            else if (los < 60)
                los = rand() % 5 + 6;
            else if (los < 63)
                los = rand() % 5 + 6;
            else if (los < 67)
                los = 18;
            else if (los < 74)
                los = 19;
            else if (los < 77)
                los = 20;
            else if (los < 80)
                los = 21;
            else if (los < 87)
                los = 22;
            else if (los < 94)
                los = 23;
            else if (los < 96)
                los = 24;
            else if (los < 100)
                los = 25;
        } else los = 26;

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
                *ptab_mapa = '&';
                break;
            case 22:
                *ptab_mapa = '@';
                break;
            case 23:
                *ptab_mapa = '+';
                break;
            case 24:
                *ptab_mapa = '!';
                break;
            case 25:
                *ptab_mapa = '?';
                break;
            default:
                *ptab_mapa = ' ';
                break;
        }
        //Usunac do update'a
        if (*ptab_mapa == ' ')
            *ptab_mapa2 = 'O';
            //else if (i == 0) *ptab_mapa2 = 'O';    //Odslaniecie lda wybranej iteracji
        //else if (*ptab_mapa == '&') *ptab_mapa2 = 'O';   //Odslaniecie kazdego atrybutu okreslonego typu
        else if (odkryte < 3 && (*ptab_mapa == 'i' || *ptab_mapa == 'e' || *ptab_mapa == 's' ||
                                 *ptab_mapa == 'p' || *ptab_mapa == 'w' || *ptab_mapa == 'u')) {
            *ptab_mapa2 = 'O';
            odkryte++;
        } else *ptab_mapa2 = 'Z';
        //*ptab_mapa2 = 'O';    //Odslaniecie wszystkiego

        ptab_mapa += 2;
        ptab_mapa2 += 2;
    }
}

void ekran_gry(int i, int j, int ruch, int *ptab_stat, char *ptab_mapa, char *ptab_mapa2) {
    int pom = 1;    //Odpowiada za pomocnicze liczby wokol mapy gry

    //Statystyki
    if (!lang)
        printf("\tYour statistics:\n\t");
    else
        printf("\tTwoje statystyki:\n\t");
    for (i = 0; i < 6; i++) {
        switch (i) {
            case 0:
                if (!lang)
                    printf("Intelligence %d", *ptab_stat);
                else
                    printf("Inteligencja %d", *ptab_stat);
                break;
            case 1:
                if (!lang)
                    printf("Empathy %d", *ptab_stat);
                else
                    printf("Empatia %d", *ptab_stat);
                break;
            case 2:
                if (!lang)
                    printf("Agility %d", *ptab_stat);
                else
                    printf("Sprawnosc %d", *ptab_stat);
                break;
            case 3:
                if (!lang)
                    printf("Memory %d", *ptab_stat);
                else
                    printf("Pamiec %d", *ptab_stat);
                break;
            case 4:
                if (!lang)
                    printf("Imagination %d", *ptab_stat);
                else
                    printf("Wyobraznia %d", *ptab_stat);
                break;
            case 5:
                if (!lang)
                    printf("Charm %d", *ptab_stat);
                else
                    printf("Urok %d", *ptab_stat);
                break;
            default:
                printf("Switch num 1 error in func game_screen");
                Sleep(10000);
                suwak(40);
                break;
        }
        printf("     ");
        ptab_stat++;
    }
    if (!lang)
        printf("\n\tRemaining move points: %d", ruch);
    else
        printf("\n\tPozostale punkty ruchu: %d", ruch);
    suwak(3);

    //Mapa gry
    for (i = 0; i < (WIERSZ + 4); i++) {
        printf("\t");
        if (!i || i == 1 || i == (WIERSZ + 3)) pom = 1;     //Wyrowanie naliczania liczb pomocniczych
        if (!i || i == (WIERSZ + 3)) {      //Pomocnicze liczby w poziomie
            for (j = 0; j < KOLUMNA; j++) {
                if (!j)
                    printf("      ");
                if (pom < 9)
                    printf("%d   ", pom);
                else printf("%d  ", pom);
                pom++;
            }
        } else if (i == 1 || i == (WIERSZ + 2)) {       //Rama mapy w poziomie
            for (j = 0; j < (4 * KOLUMNA + 6); j++) {
                if (j < 3)
                    printf(" ");
                else printf("-");
            }
        } else {
            for (j = 0; j < (KOLUMNA + 4); j++) {
                //Pomocnicze liczby w pionie
                if (!j) {
                    if (pom < 10)
                        printf(" %d ", pom);
                    if (pom >= 10)
                        printf("%d ", pom);
                } else if (j == (KOLUMNA + 3)) {
                    printf("%d", pom);
                    pom++;
                } else if (j == 1 || j == (KOLUMNA + 2))    //Rama mapy w pionie
                    printf("| ");
                else {  //Atrybuty
                    if (*ptab_mapa2 == 'Z')     //Wyswietlanie zaslonietych elementow
                        printf("[*] ");
                    else if (*ptab_mapa == ' ' || *ptab_mapa > 96 && *ptab_mapa < 104 && *ptab_mapa != 'e' ||
                             *ptab_mapa == '#') {      //Wyswietlanie elementow w prawidlowej postaci
                        switch (*ptab_mapa) {
                            case 32:
                                printf("    ");
                                break;
                            case 35:
                                printf("{^} ");
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
                            default:
                                printf("Switch num 2 error in func game_screen");
                                Sleep(10000);
                                suwak(40);
                                break;
                        }
                    } else printf("[%c] ", *ptab_mapa);     //Wyswietlanie elementow w oryginalnej postaci

                    ptab_mapa += 2;
                    ptab_mapa2 += 2;
                }
            }
        }
        printf("\n");
    }
    if (!lang) {
        printf("\n\tChoose element (insert number of row, then column: \"x x\").");
        printf("\n\tTo get into manual, insert: \"m\".\n\tPress Enter to get into Main Menu...\n");
    } else {
        printf("\n\tWybierz element (podaj numer wiersza, a potem kolumny: \"x x\").");
        printf("\n\tAby przejsc do instrukcji, wpisz: \"i\".\n\tJesli chcesz opusic gre, wcisnij Enter...\n");
    }
}

void reakcja(int i, int j, int *pzwrot, int *pruch, int *ptab_stat, char *ptab_mapa, char *ptab_mapa2, char *ptab_mapa3) {
    char tekst;   //Przechowuje tekst wpisany przez gracza
    int wiersz, kolumna = 0;    //Polozenie elementu wybranego przez gracza
    int spacja = 0;     //Liczba spacji wprowadzonych przez gracza

    /*
     * Tablica dla legendy atrybutow
     * Kolejnosc: zwykly atrybut, super atrybut, mega atrybut, hiper atrybut, oko, super oko, reakcja lancuchowa, zacmienie, bonusowe pkt ruchu, nowa mapa, losowy atrybut
     * {koszt, bonus}
     */
    int tab_legenda[][2] = {{1, 1},
                            {3, 5},
                            {4, 0},
                            {5, 3},
                            {3, 0},
                            {7, 0},
                            {4, 0},
                            {5, 0},
                            {0, 5},
                            {0, (RUCH / 2)},
                            {0, 0}};

    for (i = 0; i < 3; i++) {   //Petla w razie pomylki gracza - 3 proby
        printf("\t");
        tekst = getchar();

        if (tekst == '\n') {    //Wyjscie z gry
            *pzwrot = -1;
            break;
        } else if (tekst == 'm' || tekst == 'M' || tekst == 'i' || tekst == 'I') {      //Instrukcja
            while (tekst != '\n') tekst = getchar();
            instrukcja(i, &tab_legenda[0][0], &tab_legenda[0][1]);
            break;
        } else if (isdigit(tekst) && tekst != '0') {    //Wybor atrybutu
            wiersz = tekst - 48;    //Inicjalizacja dla zmiennej wiersz
            for (j = 0; j < 5; j++) {
                tekst = getchar();
                if (isdigit(tekst)) {
                    if (j == 0) wiersz = (wiersz * 10) + (tekst - 48);      //Inicjalizacja dla zmiennej wiersz (dodanie cyfry jednosci)
                    else if (!kolumna && tekst != '0') kolumna = tekst - 48;    //Inicjalizacja dla zmiennej kolumna
                    else kolumna = (kolumna * 10) + (tekst - 48);       //Inicjalizacja dla zmiennej kolumna (dodanie cyfry jednosci)
                }
                else if (tekst == ' ') {      //Sprawdzenie wystapienia spacji
                    if (j == 0 || j == 1 && !spacja)
                        spacja = 1;
                    else break;
                } else break;
            }
            if (tekst == '\n' && wiersz && kolumna) {        //Weryfikacja przebiegu wczesniejszej inicjalizacji
                ptab_mapa += 2 * ((wiersz - 1) * KOLUMNA + (kolumna - 1));
                ptab_mapa2 = ptab_mapa;
                ptab_mapa2++;

                if (*ptab_mapa == ' ' || *ptab_mapa2 == 'Z' ||
                    wiersz > WIERSZ || kolumna > KOLUMNA) {
                    if (!lang)
                        printf("\tThis element is inaccessible!\n");
                    else
                        printf("\tTen element jest niedostepny!\n");
                } else {
                    ptab_mapa2 = ptab_mapa3 - 1;
                    atrybut(i, ptab_mapa, ptab_mapa2, ptab_mapa3, ptab_stat, &tab_legenda[0][0], pruch);
                    break;
                }
            } else {        //Reakcja na blad
                if (!lang)
                    printf("\tIncorrect values!\n");
                else
                    printf("\tBledne wartosci!\n");
                while (tekst != '\n') tekst = getchar();
            }
        } else {      //Reakcja na blad
            if (!lang)
                printf("\tIncorrect values!\n");
            else
                printf("\tBledne wartosci!\n");
            while (tekst != '\n') tekst = getchar();
        }
    }

    if(*pzwrot > 0) {
        if (*ptab_mapa == '!')
            *pzwrot = 2;
        else *pzwrot = 3;
    }
}

void instrukcja(int i, int *ptab_legenda, int *ptab_legenda2) {
    char tekst;     //Przechowuje tekst wpisany przez gracza

    suwak(40);
    tabulator(3);
    if (!lang)
        printf("Manunal:\n\n");
    else
        printf("Instrukcja:\n\n");

    for (i = 0; i < 11; i++) {
        switch (i) {
            case 0:
                if (!lang)
                    printf("\tNormal attribute [x]: ");
                else
                    printf("\tZwykly atrybut [x]: ");
                break;
            case 1:
                if (!lang) {
                    printf("\nBoosters:\n");
                    printf("\tSuper attribute [X]: ");
                } else {
                    printf("\nBoostery:\n");
                    printf("\tSuper atrybut [X]: ");
                }
                break;
            case 2:
                if (!lang)
                    printf("\tMega attribute {x}: ");
                else
                    printf("\tMega atrybut {x}: ");
                break;
            case 3:
                if (!lang)
                    printf("\tHyper attribute [$]: -%d move points, +%d points to all categories\n", *ptab_legenda, *ptab_legenda2);
                else
                    printf("\tHiper atrybut [$]: -%d pkt ruchu, +%d pkt wszystkich umiejetnosci\n", *ptab_legenda, *ptab_legenda2);
                break;
            case 4:
                if (!lang) {
                    printf("\nRange extenders:\n");
                    printf("\tEye [^]: ");
                } else {
                    printf("\nPoszerzacze zasiegu:\n");
                    printf("\tOko [^]: ");
                }
                break;
            case 5:
                if (!lang)
                    printf("\tSuper eye {^}: ");
                else
                    printf("\tSuper oko {^}: ");
                break;
            case 6:
                if (!lang)
                    printf("\tChain reaction [&]: ");
                else
                    printf("\tReakcja lancuchowa [&]: ");
                break;
            case 7:
                if (!lang) {
                    printf("\nDebuffs:\n");
                    printf("\tBlackout [@]: ");
                } else {
                    printf("\nDebuffy:\n");
                    printf("\tZacmienie [@]: ");
                }
                break;
            case 8:
                if (!lang) {
                    printf("\nOther:\n");
                    printf("\tBonus to move points [+]: ");
                } else {
                    printf("\nInne:\n");
                    printf("\tBonus do pkt ruchu [+]: ");
                }
                break;
            case 9:
                if (!lang)
                    printf("\tNew map [!]: ");
                else
                    printf("\tNowa mapa [!]: ");
                break;
            case 10:
                if (!lang)
                    printf("\tRandom attribute [?]: cost equal to received attribute type");
                else
                    printf("\tLosowy atrybut [?]: koszt taki, jak wylosowanego typu atrybutu");
                break;
            default:
                printf("Switch error in func manual");
                Sleep(10000);
                suwak(40);
                break;
        }

        if (i != 3 && i != 10) {
            if (*ptab_legenda && *ptab_legenda2) {
                if (!lang)
                    printf("-%d move points, +%d points to accurate category\n", *ptab_legenda, *ptab_legenda2);
                else
                    printf("-%d pkt ruchu, +%d pkt umiejetnosci\n", *ptab_legenda, *ptab_legenda2);
            } else if (*ptab_legenda) {
                if (!lang)
                    printf("-%d move points\n", *ptab_legenda);
                else
                    printf("-%d pkt ruchu\n", *ptab_legenda);
            } else {
                if (!lang)
                    printf("+%d points to accurate category\n", *ptab_legenda2);
                else
                    printf("+%d pkt umiejetnosci\n", *ptab_legenda2);
            }
        }

        ptab_legenda += 2;
        ptab_legenda2 += 2;
    }

    suwak(3);
    if (!lang)
        printf("Press Enter to get back into game...\n");
    else
        printf("\tAby wrocic do gry, wcisnij Enter...");
    tekst = getchar();
    while (tekst != '\n') tekst = getchar();
}

void atrybut(int i, char *ptab_mapa, char *ptab_mapa2,  char *ptab_mapa3, int *ptab_stat, int *ptab_legenda, int *pruch) {
    char *ptmp;     //Wskaznik dla pierwszego elementu tablicy (odkrywanie elementow)
    char *ptmk;     //Wskaznik dla ostatniego elementu tablicy (odkrywanie elementow)
    unsigned short bieda = 1;    //Informuje, czy liczba pkt ruchu jest wystarczajaca (odkrywanie elementow)
    ptmp = ptmk = ptab_mapa2;
    ptmk += 2 * WIERSZ * KOLUMNA;

    //Zmiana statystyk i dezaktywacja elementu
    //Losowy atrybut
    if (*ptab_mapa == '?')
        los(i, ptab_mapa, ptab_legenda, pruch, &bieda);

    //Zwykle atrybuty
    if (*ptab_mapa == 'i' || *ptab_mapa == 'e' || *ptab_mapa == 's' ||
        *ptab_mapa == 'p' || *ptab_mapa == 'w' || *ptab_mapa == 'u') {
        zwykly_at(*ptab_mapa, ptab_stat, ptab_legenda, pruch, &bieda);

    //Super atrybuty
    } else if (*ptab_mapa == 'I' || *ptab_mapa == 'E' || *ptab_mapa == 'S' ||
               *ptab_mapa == 'P' || *ptab_mapa == 'W' || *ptab_mapa == 'U') {
        super_at(*ptab_mapa, ptab_stat, ptab_legenda, pruch, &bieda);

    //Mega atrybuty
    } else if (*ptab_mapa > 96 && *ptab_mapa < 104 && *ptab_mapa != 101) {
        mega_at(i, *ptab_mapa, ptab_mapa2, ptab_mapa3, ptab_stat, ptab_legenda, pruch, &bieda);

    //Hiper atrybut
    } else if (*ptab_mapa == '$') {
        hiper_at(i, ptab_stat, ptab_legenda, pruch, &bieda);

    //Oko
    } else if (*ptab_mapa == '^') {
        ptab_legenda += 8;      //Utrata punktow ruchu z weryfikacja ich stanu
        if (*pruch < *ptab_legenda) {
            printf("Za malo punktow ruchu!\n");
            bieda = 0;
            Sleep(1000);
        }
        else *pruch -= *ptab_legenda;

    //Super oko
    } else if (*ptab_mapa == '#') {
        ptab_legenda += 10;     //Utrata punktow ruchu z weryfikacja ich stanu
        if (*pruch < *ptab_legenda) {
            printf("Za malo punktow ruchu!\n");
            bieda = 0;
            Sleep(1000);
        }
        else *pruch -= *ptab_legenda;

    //Reakcja lancuchowa
    } else if (*ptab_mapa == '&') {
        reakcja_lanc(i, ptab_mapa, ptab_mapa2, ptmp, ptmk, ptab_legenda, pruch, &bieda);

    //Zacmienie
    } else if (*ptab_mapa == '@') {
        ptab_legenda += 14;     //Utrata punktow ruchu z weryfikacja ich stanu
        if (*pruch < *ptab_legenda) {
            printf("Za malo punktow ruchu!\n");
            bieda = 0;
            Sleep(1000);
        }
        else *pruch -= *ptab_legenda;

    //Bonus do punktow ruchu
    } else if (*ptab_mapa == '+') {
        ptab_legenda += 17;     //Zwiekszenie liczby punktow ruchu
        *pruch += *ptab_legenda;

    //Nowa mapa
    } else if (*ptab_mapa == '!') {
        ptab_legenda += 19;     //Zwiekszenie liczby punktow ruchu
        *pruch += *ptab_legenda;
    }

    if (bieda) {    //Sprawdzenie, czy atrybut zostal obsluzony
        if (*ptab_mapa != '^' && *ptab_mapa != '#' && *ptab_mapa != '!' && *ptab_mapa != '&')
            *ptab_mapa = ' ';   //Dezaktywacja atrybutow poza okiem, superokiem, nowa mapa i reakcja lancuchowa

        if (*ptab_mapa == ' ') {    //Odkrywanie elementow wokol wybranego
            for (i = 0; i < 8; i++) {
                if (!i) ptab_mapa -= 2 * KOLUMNA + 1;
                else if (i == 3 || i == 5) ptab_mapa += 2 * KOLUMNA - 4;
                else if (i == 4) ptab_mapa += 4;
                else ptab_mapa += 2;
                if (*ptab_mapa != 'O' && ptab_mapa > ptmp && ptab_mapa < ptmk)
                    *ptab_mapa = 'O';
            }
        } else if (*ptab_mapa == '^')   //Odkrywanie elementow dla oka
            oko(i, ptab_mapa, ptab_mapa2, ptmp, ptmk);

        else if (*ptab_mapa == '#') {     //Odkrywanie elementow dla super oka
            ptmp++;
            for (i = 0; i < WIERSZ * KOLUMNA; i++) {
                if (*ptmp == 'Z') *ptmp = 'O';
                ptmp += 2;
            }
        }
        if (*ptab_mapa != ' ' && *ptab_mapa != '!')      //Spacjalna dezaktywacja pozostalych atrybutow poza nowa mapa
            *ptab_mapa = ' ';
    }
}

void los(int i, char *ptab_mapa, int *ptab_legenda, int *pruch, unsigned short *pbieda) {
    int los;    //Decyduje ktory atrybut ma zostac zainicjalizowany
    los = rand() % 24;

    ptab_legenda += 10;     //Sprawdzenie punktow ruchu (ustawic na najwiekszy koszt)
    if (*pruch < *ptab_legenda) {
        printf("Za malo punktow ruchu!\n");
        *pbieda = 0;
        Sleep(1000);
    } else {
        switch (los) {      //Losowanie efektu
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
            case 23:
                *ptab_mapa = '!';
                break;
            default:
                printf("Blad switcha los nr 1!");
                break;
        }

        //Komunikaty dla gracza
        suwak(40);
        tabulator(3);
        printf("Rozpoczeto losowanie.\n");
        Sleep(800);
        tabulator(3);
        printf("Prosze czekac");
        Sleep(2000);
        for (i = 0; i < 3; i++) {
            printf(".");
            Sleep(2000);
        }

        printf("\n");
        tabulator(3);
        printf("Wylosowano: ");
        if (*ptab_mapa > 96 && *ptab_mapa < 104 && *ptab_mapa != 'e' ||
            *ptab_mapa == '#') {      //Wyswietlanie elementu w prawidlowej postaci
            switch (*ptab_mapa) {
                case 35:
                    printf("{^} ");
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
                default:
                    printf("Blad switcha los nr 2");
                    break;
            }
        } else printf("[%c] ", *ptab_mapa);     //Wyswietlanie elementu w oryginalnej postaci
        printf("!");
        Sleep(5000);
    }
}

void zwykly_at(char ptab_mapa, int *ptab_stat, int *ptab_legenda, int *pruch, unsigned short *pbieda) {
    if (*pruch < *ptab_legenda) {     //Utrata punktow ruchu z weryfikacja ich stanu
        printf("Za malo punktow ruchu!\n");
        *pbieda = 0;
        Sleep(1000);
    } else {
        *pruch -= *ptab_legenda;
        ptab_legenda++;

        switch (ptab_mapa) {        //Zmiana statystyk z weryfikacja kategorii
            case 'i':
                *ptab_stat += *ptab_legenda;
                break;
            case 'e':
                ptab_stat++;
                *ptab_stat += *ptab_legenda;
                break;
            case 's':
                ptab_stat += 2;
                *ptab_stat += *ptab_legenda;
                break;
            case 'p':
                ptab_stat += 3;
                *ptab_stat += *ptab_legenda;
                break;
            case 'w':
                ptab_stat += 4;
                *ptab_stat += *ptab_legenda;
                break;
            case 'u':
                ptab_stat += 5;
                *ptab_stat += *ptab_legenda;
                break;
            default:
                printf("Blad switcha zwykly_at!");
                break;
        }
    }
}

void super_at(char ptab_mapa, int *ptab_stat, int *ptab_legenda, int *pruch, unsigned short *pbieda) {
    ptab_legenda += 2;      //Utrata punktow ruchu z weryfikacja ich stanu
    if (*pruch < *ptab_legenda) {
        printf("Za malo punktow ruchu!\n");
        *pbieda = 0;
        Sleep(1000);
    } else {
        *pruch -= *ptab_legenda;
        ptab_legenda++;

        switch (ptab_mapa) {        //Zmiana statystyk z weryfikacja kategorii
            case 'I':
                *ptab_stat += *ptab_legenda;
                break;
            case 'E':
                ptab_stat++;
                *ptab_stat += *ptab_legenda;
                break;
            case 'S':
                ptab_stat += 2;
                *ptab_stat += *ptab_legenda;
                break;
            case 'P':
                ptab_stat += 3;
                *ptab_stat += *ptab_legenda;
                break;
            case 'W':
                ptab_stat += 4;
                *ptab_stat += *ptab_legenda;
                break;
            case 'U':
                ptab_stat += 5;
                *ptab_stat += *ptab_legenda;
                break;
            default:
                printf("Blad switcha super_at!");
                break;
        }
    }
}

void mega_at(int i, char ptab_mapa, char *ptab_mapa2, char *ptab_mapa3, int *ptab_stat, int *ptab_legenda, int *pruch, unsigned short *pbieda) {
    ptab_legenda += 4;      //Utrata punktow ruchu z weryfikacja ich stanu
    if (*pruch < *ptab_legenda) {
        printf("Za malo punktow ruchu!\n");
        *pbieda = 0;
        Sleep(1000);
    } else {
        *pruch -= *ptab_legenda;
        ptab_legenda -= 3;

        switch (ptab_mapa) {        //Weryfikacja kategorii
            case 'b':
                ptab_stat++;
                break;
            case 'c':
                ptab_stat += 2;
                break;
            case 'd':
                ptab_stat += 3;
                break;
            case 'f':
                ptab_stat += 4;
                break;
            case 'g':
                ptab_stat += 5;
                break;
            default:
                printf("Blad switcha mega_at nr 1!");
                break;
        }

        for (i = 0; i < WIERSZ * KOLUMNA; i++) {    //Przeszukanie tablicy za wlasciwymi elem. i zmiana statystyk
            if (*ptab_mapa3 == 'O') {
                switch (ptab_mapa) {
                    case 'a':
                        if (*ptab_mapa2 == 'i') {
                            *ptab_stat += *ptab_legenda;
                            *ptab_mapa2 = ' ';
                        }
                        break;
                    case 'b':
                        if (*ptab_mapa2 == 'e') {
                            *ptab_stat += *ptab_legenda;
                            *ptab_mapa2 = ' ';
                        }
                        break;
                    case 'c':
                        if (*ptab_mapa2 == 's') {
                            *ptab_stat += *ptab_legenda;
                            *ptab_mapa2 = ' ';
                        }
                        break;
                    case 'd':
                        if (*ptab_mapa2 == 'p') {
                            *ptab_stat += *ptab_legenda;
                            *ptab_mapa2 = ' ';
                        }
                        break;
                    case 'f':
                        if (*ptab_mapa2 == 'w') {
                            *ptab_stat += *ptab_legenda;
                            *ptab_mapa2 = ' ';
                        }
                        break;
                    case 'g':
                        if (*ptab_mapa2 == 'u') {
                            *ptab_stat += *ptab_legenda;
                            *ptab_mapa2 = ' ';
                        }
                        break;
                    default:
                        printf("Blad switcha mega_at nr 2!");
                        break;
                }
            }
            ptab_mapa2 += 2;
            ptab_mapa3 += 2;
        }
    }
}

void hiper_at(int i, int *ptab_stat, int *ptab_legenda, int *pruch, unsigned short *pbieda) {
    ptab_legenda += 6;      //Utrata punktow ruchu z weryfikacja ich stanu
    if (*pruch < *ptab_legenda) {
        printf("Za malo punktow ruchu!\n");
        *pbieda = 0;
        Sleep(1000);
    } else {
        *pruch -= *ptab_legenda;
        ptab_legenda++;
        for (i = 0; i < 6; i++) {       //Zmiana statystyk
            *ptab_stat += *ptab_legenda;
            ptab_stat++;
        }
    }
}

void reakcja_lanc(int i, char *ptab_mapa, char *ptab_mapa2, char *ptmp, char *ptmk, int *ptab_legenda, int *pruch, unsigned short *pbieda) {
    unsigned short lewo;        //Liczba elementow stojacych na lewo od atrybutu
    unsigned short prawo;       //Liczba elementow stojacych na prawo od atrybutu
    unsigned short gora;        //Liczba wierszy nad atrybutem
    unsigned short dol;     //Liczba wierszy pod atrybutem
    unsigned short los;     //Wynik losowania
    unsigned short odkryte = 0;     //Liczba odkrytych elementow
    int tab_poprzed[20];        //Tablica adresow wybranych elementow
    int *poprzednik;        //Wskaznik na tablice tab_poprzed
    unsigned short powtorka = 0;        //Powtorzenie elementu
    int j, k;      //Zmienne dla petli

    ptab_legenda += 12;     //Weryfikacja stanu punktow ruchu
    if (*pruch < *ptab_legenda) {
        printf("Za malo punktow ruchu!\n");
        *pbieda = 0;
        Sleep(1000);
    } else {
        *pruch -= *ptab_legenda;    //Utrata punktow ruchu

        poprzednik = &tab_poprzed[0];       //Zapelnienie tablicy zerami
        for (i = 0; i < 20; i++) {
            *poprzednik = 0;
        }

        //Odleglosc atrybutu od brzegow tablicy
        ptab_mapa++;
        lewo = ((ptab_mapa - ptmp) / 2) % KOLUMNA;
        prawo = ((ptmk - ptab_mapa - 1) / 2) % KOLUMNA;
        gora = ((ptab_mapa - ptmp) / 2) / KOLUMNA;
        dol = ((ptmk - ptab_mapa - 1) / 2) / KOLUMNA;

        //Odkrywanie wybranych elementow wokol atrybutu
        while (odkryte < 12) {
            ptab_mapa2 = ptab_mapa;
            if (i)
                i = 0;

            while (!i) {        //Element sasiadujacy (bazowy)
                los = rand() % 4;

                switch (los) {
                    case 0:     //Osloniecie nad
                        if (gora > 0) {
                            ptab_mapa2 -= 2 * KOLUMNA;
                            i = 1;
                        }
                        break;
                    case 1:     //Osloniecie na lewo
                        if (lewo > 0) {
                            ptab_mapa2 -= 2;
                            i = 2;
                        }
                        break;
                    case 2:     //Osloniecie na prawo
                        if (prawo > 0) {
                            ptab_mapa2 += 2;
                            i = 3;
                        }
                        break;
                    case 3:     //Osloniecie pod
                        if (dol > 0) {
                            ptab_mapa2 += 2 * KOLUMNA;
                            i = 4;
                        }
                        break;
                    default:
                        printf("Blad switcha reakcja_lanc nr 1!");
                        break;
                }
            }

            if (*ptab_mapa2 != 'O' && ptab_mapa2 > ptmp && ptab_mapa2 < ptmk)
                *ptab_mapa2 = 'O';
            odkryte++;

            for (j = 0; j < 11; j++) {     //Kolejne elementy
                switch (i) {
                    case 1:     //Baza - gora
                        los = rand() % 3;

                        switch (los) {
                            case 0:     //Osloniecie nad
                                if (gora > j + 1)
                                    ptab_mapa2 -= 2 * KOLUMNA;
                                else j = 20;
                                break;
                            case 1:     //Osloniecie na lewo
                                if (lewo > j)
                                    ptab_mapa2 -= 2;
                                else j = 20;
                                break;
                            case 2:     //Osloniecie na prawo
                                if (prawo > j)
                                    ptab_mapa2 += 2;
                                else j = 20;
                                break;
                            default:
                                printf("Blad switcha reakcja_lanc nr 3!");
                                break;
                        }

                        break;
                    case 2:     //Baza - lewo
                        los = rand() % 3;

                        switch (los) {
                            case 0:     //Osloniecie na lewo
                                if (lewo > j + 1)
                                    ptab_mapa2 -= 2;
                                else j = 20;
                                break;
                            case 1:     //Osloniecie nad
                                if (gora > j)
                                    ptab_mapa2 -= 2 * KOLUMNA;
                                else j = 20;
                                break;
                            case 2:     //Osloniecie pod
                                if (dol > j)
                                    ptab_mapa2 += 2 * KOLUMNA;
                                else j = 20;
                                break;
                            default:
                                printf("Blad switcha reakcja_lanc nr 4!");
                                break;
                        }

                        break;
                    case 3:     //Baza - prawo
                        los = rand() % 3;

                        switch (los) {
                            case 0:     //Osloniecie na prawo
                                if (prawo > j + 1)
                                    ptab_mapa2 += 2;
                                else j = 20;
                                break;
                            case 1:     //Osloniecie nad
                                if (gora > j)
                                    ptab_mapa2 -= 2 * KOLUMNA;
                                else j = 20;
                                break;
                            case 2:     //Osloniecie pod
                                if (dol > j)
                                    ptab_mapa2 += 2 * KOLUMNA;
                                else j = 20;
                                break;
                            default:
                                printf("Blad switcha reakcja_lanc nr 5!");
                                break;
                        }

                        break;
                    case 4:     //Baza - dol
                        los = rand() % 3;

                        switch (los) {
                            case 0:     //Osloniecie pod
                                if (dol > j + 1)
                                    ptab_mapa2 += 2 * KOLUMNA;
                                else j = 20;
                                break;
                            case 1:     //Osloniecie na lewo
                                if (lewo > j)
                                    ptab_mapa2 -= 2;
                                else j = 20;
                                break;
                            case 2:     //Osloniecie na prawo
                                if (prawo > j)
                                    ptab_mapa2 += 2;
                                else j = 20;
                                break;
                            default:
                                printf("Blad switcha reakcja_lanc nr 6!");
                                break;
                        }

                        break;
                    default:
                        printf("Blad switcha reakcja_lanc nr 2!");
                        break;
                }
                if (j != 20) {
                    poprzednik = &tab_poprzed[0];
                    for (k = 0; k < 20; k++) {      //Weryfikacja wystapienia powtorki
                        if (*poprzednik) {
                            if (*poprzednik == ptab_mapa2) {
                                powtorka = 1;
                                break;
                            }
                            poprzednik++;
                        } else break;
                    }
                    if (!powtorka) {        //Brak powtorki
                        if (k == 20) {
                            printf("Brak mejsca w tablicy!");
                            Sleep(5000);
                        } else *poprzednik = ptab_mapa2;

                        if (*ptab_mapa2 != 'O' && ptab_mapa2 > ptmp && ptab_mapa2 < ptmk)
                            *ptab_mapa2 = 'O';
                        odkryte++;
                    } else j--;
                }
                if (odkryte > 12)
                    break;
            }
        }
    }
}

void oko(int i, char *ptab_mapa, char *ptab_mapa2, char *ptmp, char *ptmk) {
    unsigned short lewo;     //Liczba elementow stojacych na lewo od "oka"
    unsigned short prawo;   //Liczba elementow stojacych na prawo od "oka"

    ptab_mapa2 = ptab_mapa;
    for (i = 0; i < 24; i++) {
        if (!i) {       //Obliczenie bledu przesuniecia (za malo kolumn w otoczeniu)
            ptab_mapa++;
            lewo = ((ptab_mapa - ptmp) / 2) % KOLUMNA;
            prawo = ((ptmk - ptab_mapa - 1) / 2) % KOLUMNA;
        }

        switch (i) {    //Ustawienie na wlasciwe elementy
            case 0:
                ptab_mapa = ptab_mapa2 - (23 + (KOLUMNA - 5) * 4);
                break;
            case 5:
                ptab_mapa = ptab_mapa2 - (13 + (KOLUMNA - 5) * 2);
                break;
            case 10:
                ptab_mapa = ptab_mapa2 - 3;
                break;
            case 12:
                ptab_mapa += 4;
                break;
            case 14:
                ptab_mapa = ptab_mapa2 + (7 + (KOLUMNA - 5) * 2);
                break;
            case 19:
                ptab_mapa = ptab_mapa2 + (17 + (KOLUMNA - 5) * 4);
                break;
            default:
                ptab_mapa += 2;
                break;
        }

        //Odslanienie elementow z weryfikacja zajcia bledow
        if (*ptab_mapa != 'O' && ptab_mapa > ptmp && ptab_mapa < ptmk) {
            if (lewo < 2 || prawo < 2) {
                if (lewo < 2) {
                    switch (lewo) {
                        case 0:
                            if (i > 1 && i != 5 && i != 6 && i != 10 && i != 11 && i != 14 && i != 15 && i != 19 &&
                                i != 20)
                                *ptab_mapa = 'O';
                            break;
                        case 1:
                            if (i && i != 5 && i != 10 && i != 14 && i != 19)
                                *ptab_mapa = 'O';
                            break;
                        default:
                            printf("Blad switcha atrybut nr 2!");
                            break;
                    }
                }

                if (prawo < 2) {
                    switch (prawo) {
                        case 0:
                            if (i != 3 && i != 4 && i != 8 && i != 9 && i != 12 && i != 13 && i != 17 && i != 18 &&
                                i != 22 && i != 23)
                                *ptab_mapa = 'O';
                            break;
                        case 1:
                            if (i != 4 && i != 9 && i != 13 && i != 18 && i != 23)
                                *ptab_mapa = 'O';
                            break;
                        default:
                            printf("Blad switcha atrybut nr 3!");
                            break;
                    }
                }
            } else *ptab_mapa = 'O';
        }
    }
}

void test(int i, int *pzwrot, int *pruch, char *ptab_mapa, char *ptab_mapa2) {
    int zuzyte = 0;     //Libcza zuzytych elementow

    if (*pruch <= 0) {      //Sprawdzenie liczby pkt ruchu
        *pzwrot = 0;

        if (!*pruch) {
            suwak(40);
            tabulator(3);
            Sleep(500);
            printf("Zuzyto wszystkie puknty ruchu.\n");
            Sleep(500);
            tabulator(3);
            printf("Za chwile zostaniesz przeniesiony do ekranu koncowego");
            Sleep(3000);
        }

    } else {      //Sprawdzenie liczby zuzytych elementow
        for (i = 0; i < WIERSZ * KOLUMNA; i++) {
            if (*ptab_mapa2 == 'Z')
                break;
            else if (*ptab_mapa == ' ')
                zuzyte++;

            ptab_mapa += 2;
            ptab_mapa2 += 2;
        }
        if (zuzyte == (WIERSZ * KOLUMNA)) {
            *pzwrot = 0;

            suwak(40);
            tabulator(3);
            Sleep(500);
            printf("Zuzyto wszystkie elementy.\n");
            Sleep(500);
            tabulator(3);
            printf("Za chwile zostaniesz przeniesiony do ekranu koncowego");
            Sleep(3000);
        }
    }
}

void ekran_koncowy(int *ptab_stat) {
    tabulator(8);
    if (!lang)
        printf("Congratulations!\n");
    else
        printf("Gratulacje!\n");
    tabulator(7);
    if (!lang)
        printf("Here is your final score:\n\n");
    else
        printf("Oto twoj koncowy wynik:\n\n");
    tabulator(3);

    for (int i = 0; i < 6; i++) {
        switch (i) {
            case 0:
                if (!lang)
                    printf("Intelligence %d", *ptab_stat);
                else
                    printf("Inteligencja %d", *ptab_stat);
                break;
            case 1:
                if (!lang)
                    printf("Empathy %d", *ptab_stat);
                else
                    printf("Empatia %d", *ptab_stat);
                break;
            case 2:
                if (!lang)
                    printf("Agility %d", *ptab_stat);
                else
                    printf("Sprawnosc %d", *ptab_stat);
                break;
            case 3:
                if (!lang)
                    printf("Memory %d", *ptab_stat);
                else
                    printf("Pamiec %d", *ptab_stat);
                break;
            case 4:
                if (!lang)
                    printf("Imagination %d", *ptab_stat);
                else
                    printf("Wyobraznia %d", *ptab_stat);
                break;
            case 5:
                if (!lang)
                    printf("Charm %d", *ptab_stat);
                else
                    printf("Urok %d", *ptab_stat);
                break;
            default:
                printf("Switch error in func final_screen");
                Sleep(10000);
                suwak(40);
                break;
        }
        printf("\t");
        ptab_stat++;
    }

    Sleep(2000);
    suwak(40);
}

void zapisz_gre(FILE *pf, int const *pruch, int *ptab_stat, char *ptab_mapa, int i, int j) {
    char pom;     //Konwersja zmiennych na typ znakowy
    int licz;       //Pomocnicza zmienna
    int k;      //Zmienna dla petli

    //Komunikacja z graczem
    if (!lang)
        printf("\t\tDo you wish to save your progress? (y/n)\n");
    else
        printf("\t\tCzy chcesz zapisac swoje postepy? (t/n)\n");
    pom = getchar();
    if (pom != 't' && pom != 'T' && pom != 'y' && pom != 'Y') {
        if (!lang)
            printf("\t\tAre you sure? (y - save/n)\n");
        else
            printf("\t\tCzy na pewno nie chcesz dokonac zapisu? (t - zapis/n)\n");
        while (pom != '\n')
            pom = getchar();
        pom = getchar();
    }

    suwak(40);

    if (pom == 't' || pom == 'T' || pom == 'y' || pom == 'Y') {     //Zapis danych do pliku
        pf = fopen("save.txt", "w");

        for (i = 0; i < 3; i++) {
            switch (i) {
                case 0:     //Zapis liczby punktow ruchu
                    if (*pruch > 9) {
                        for (j = 0; j < 2; j++) {
                            switch (j) {
                                case 0:
                                    licz = *pruch / 10;
                                    pom = licz + 48;
                                    fputc(pom, pf);
                                    break;
                                case 1:
                                    licz = *pruch % 10;
                                    pom = licz + 48;
                                    fputc(pom, pf);
                                    break;
                                default:
                                    printf("\n\nBlad switcha zapisz_gre nr 2");
                                    Sleep(5000);
                                    break;
                            }
                        }
                    } else {
                        pom = *pruch + 48;
                        fputc(pom, pf);
                    }
                    break;
                case 1:     //Zapis statystyk
                    for (j = 0; j < 6; j++) {
                        if (*ptab_stat > 9) {
                            for (k = 0; k < 2; k++) {
                                switch (k) {
                                    case 0:
                                        licz = *ptab_stat / 10;
                                        pom = licz + 48;
                                        fputc(pom, pf);
                                        break;
                                    case 1:
                                        licz = *ptab_stat % 10;
                                        pom = licz + 48;
                                        fputc(pom, pf);
                                        break;
                                    default:
                                        printf("\n\nBlad switcha zapisz_gre nr 3");
                                        Sleep(5000);
                                        break;
                                }
                            }
                        } else {
                            pom = *ptab_stat + 48;
                            fputc(pom, pf);
                        }

                        ptab_stat++;
                        if (j < 5)
                            fputc(' ', pf);
                    }
                    break;
                case 2:     //Zapis mapy gry
                    for (j = 0; j < WIERSZ * KOLUMNA * GLEBOKOSC; j++) {
                        fputc(*ptab_mapa, pf);
                        ptab_mapa++;
                    }
                    break;
                default:
                    printf("\n\nBlad switcha zapisz_gre nr 1");
                    Sleep(5000);
                    break;
            }

            fputc('\n', pf);
        }

        fclose(pf);
    }
}

void wczytaj_gre(FILE *pf, int *pruch, int *ptab_stat, char *ptab_mapa, int i, int j) {
    char tab_pom[25];        //Konwersja zmiennych na typ znakowy
    char *ppom;
    int licz;       //Pomocnicza zmienna

    pf = fopen("save.txt", "r");

    for (i = 0; i < 3; i++) {
        if (!i || i == 1) {
            ppom = &tab_pom[0];
            while (*ppom != '\n') {
                *ppom = fgetc(pf);
                if (*ppom != '\n') {
                    ppom++;
                    if (*ppom == '\n')
                        *ppom = 0;
                }
            }
            ppom = &tab_pom[0];
        }

        switch (i) {
            case 0:     //Wczytanie punktow ruchu
                if (tab_pom[1] != '\n') {
                    for (j = 0; j < 2; j++) {
                        switch (j) {
                            case 0:
                                *pruch = *ppom - 48;
                                break;
                            case 1:
                                *pruch = *pruch * 10 + *ppom - 48;
                                break;
                            default:
                                printf("\n\nBlad switcha wczytaj_gre nr 2");
                                Sleep(5000);
                                break;
                        }

                        ppom++;
                    }
                } else
                    *pruch = *ppom - 48;
                break;
            case 1:     //Wczytanie statystyk
                for (j = 0; j < 6; j++) {
                    while (*ppom != ' ' && *ppom != '\n') {
                        if (!*ptab_stat)
                            *ptab_stat = *ppom - 48;
                        else
                            *ptab_stat = *ptab_stat * 10 + *ppom - 48;
                        ppom++;
                    }
                    ppom++;
                    ptab_stat++;
                }
                break;
            case 2:     //Wczytywanie mapy gry
                for (j = 0; j < WIERSZ * KOLUMNA * GLEBOKOSC; j++) {
                    *ptab_mapa = fgetc(pf);
                    ptab_mapa++;
                }
                break;
            default:
                printf("\n\nBlad switcha wczytaj_gre nr 1");
                Sleep(5000);
                break;
        }
    }

    fclose(pf);
}

//Funkcja "suwak" odpowiada za "czyszczenie ekranu" - przesuwanie tekstu tak, aby nie bylo widac wczesniejszych, niepotrzebnych komunikatow.
void suwak (int linia) {
    for (int i = 0; i < linia; i++)
        printf("\n");
}

//Funkcja "tabulator" odpowiada za wykonanie tabulacji tekstu
void tabulator (int tab) {
    for (int i = 0; i < tab; i++)
        printf("\t");
}

