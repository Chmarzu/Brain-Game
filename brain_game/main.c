#include <stdio.h>
//Wybor wielkosci tabeli tab_mapa
#define WIERSZ 6
#define KOLUMNA 6
int linia = 3; //Zmienna globalna odpowiadajaca ilosci przesuwanych linijek w funkcji "suwak".

//Funkcja "suwak" odpowiada za "czyszczenie ekranu" - przesuwanie tekstu tak, aby nie bylo widac wczesniejszych, niepotrzebnych komunikatow.
int suwak () {
    for (int i = 0; i < linia; i++) printf("\n");
    return 0;
}

int main() {
    //Sekcja zmiennych
    /* i, j - zmienne dla petli
    bug - ester egg uruchamiany, jesli gracz wcisnie zly przycisk na ekranie startowym
    ruch - mechanika punktow ruchu, warunek petli glownej czesci gry
    pom - odpowiada za pomocnicze liczby wokol mapy gry
    wiersz, kolumna - polozenie elementu wybranego przez gracza
    lbelementow - odpowiada za liczbe wykorzystywanych elementow na mapie gry */
    int i, j, bug, ruch = 3, pom = 1, wiersz, kolumna;

    /* Tablica z wartościami statystyk i ich inicjalizacja
    Kolejnosc: Inteligencja, Empatia, Sprawnosc, Pamiec, Wyobraznia, Urok */
    int tab_stat [6] = {0, 0, 0, 0, 0, 0};

    //Tablica dla elementow wyswietlanych na mapie gry i ich inicjalizacja
    char tab_mapa [WIERSZ][KOLUMNA];
    for (i = 0; i < WIERSZ; ++i) {
        for (j = 0; j < KOLUMNA; ++j) {
            switch (j) {
                case 0:
                    tab_mapa[i][j]='i';
                    break;
                case 1:
                    tab_mapa[i][j]='e';
                    break;
                case 2:
                    tab_mapa[i][j]='s';
                    break;
                case 3:
                    tab_mapa[i][j]='p';
                    break;
                case 4:
                    tab_mapa[i][j]='w';
                    break;
                case 5:
                    tab_mapa[i][j]='u';
                    break;
                default:
                    tab_mapa[i][j]=' ';
                    break;
            }
        }
    }

    //Ekran powitalny
    suwak();
    printf("Witaj w Mapie Mozgu!\nGra ta jest inspirowana mini gra z Growing Up.\n\n\nAby przejsc dalej, wprowadz 0... ");
    scanf("%d", &bug);
    linia=10;
    suwak();

    //Ester egg :)
    if(bug!=0) {
        printf("Nie ladnie psuc gre!\nSprobuj jeszcze raz :D\nAby przejsc dalej, wprowadz 0... ");
        scanf("%d", &bug);
        if(bug!=0) {
            printf("\nTo byla ostatnia szansa...");
            return 0;
        } else suwak();
    }

    //Wlasciwa gra
    do {
        //Statystyki
        printf("Twoje statystyki:\nInteligencja %d | Empatia %d | Sprawnosc %d | Pamiec %d | Wyobraznia %d | Urok %d\n",  tab_stat[0], tab_stat[1], tab_stat[2], tab_stat[3], tab_stat[4], tab_stat[5]);
        printf("Pozostale punkty ruchow: %d\n", ruch);
        printf ("Legenda:\nZwykle elementy: 1 pkt\n\n");

        //Mapa gry
        for (i = 0; i < (WIERSZ + 4); i++) {
            (i == 0 || i == 1 || i == (WIERSZ + 3)) ? pom = 1 : pom;
            if (i == 0 || i == (WIERSZ + 3)) {
                for (int k = 0; k < (KOLUMNA); k++) {
                    if (k == 0) for (int l = 0; l < 6; ++l) printf(" ");
                    if (pom < 9) printf("%d   ", pom);
                    if (pom >= 9) printf("%d  ", pom);
                    pom++;
                }
            }
            else if (i == 1 || i == (WIERSZ + 2)) {
                for (int n = 0; n < (4 * KOLUMNA + 6); n++) {
                    if (n < 3) printf(" ");
                    else printf("-");
                }
            }
            else {
                for (j = 0; j < (KOLUMNA + 4); j++) {
                    if (j == 0) {
                        if (pom < 10)printf(" %d ", pom);
                        if (pom >= 10)printf("%d ", pom);
                    }
                    else if (j == (KOLUMNA + 3)) {
                        printf("%d", pom);
                        pom++;
                    }
                    else if (j == 1 || j == (KOLUMNA + 2)) printf("| ");
                    else {
                        printf("[%c] ", tab_mapa[(i - 2)][(j - 2)]);
                    }
                }
            }
            printf("\n");
        }

        //Modul interaktywny
        printf ("\nWybierz element (podaj numer wiersza, a potem kolumny).\nJesli chcesz opusic gre, wpisz: 0 0.\n");
        for (i = 0; i < 3; ++i) {
            scanf ("%d %d", &wiersz, &kolumna);
            if (wiersz == 0 && kolumna == 0) return 0;
            else if (wiersz > 0 && kolumna > 0) {
                if (tab_mapa[wiersz - 1][kolumna - 1] == ' ') printf("Ten element zostal juz wybrany!\n");
                else {
                    ruch--;
                    switch (tab_mapa[wiersz - 1][kolumna - 1]) {
                        case 105:
                            tab_stat[0]++;
                            tab_mapa[wiersz - 1][kolumna - 1] = ' ';
                            break;
                        case 101:
                            tab_stat[1]++;
                            tab_mapa[wiersz - 1][kolumna - 1] = ' ';
                            break;
                        case 115:
                            tab_stat[2]++;
                            tab_mapa[wiersz - 1][kolumna - 1] = ' ';
                            break;
                        case 112:
                            tab_stat[3]++;
                            tab_mapa[wiersz - 1][kolumna - 1] = ' ';
                            break;
                        case 119:
                            tab_stat[4]++;
                            tab_mapa[wiersz - 1][kolumna - 1] = ' ';
                            break;
                        case 117:
                            tab_stat[5]++;
                            tab_mapa[wiersz - 1][kolumna - 1] = ' ';
                            break;
                    }
                    i = 3;
                }
            }
            else printf("Bledne wartosci!\n");
        }
        if (ruch == 0) linia = 15;
        suwak();

        //Ekran koncowy
        if (ruch == 0) {
            printf("Gratulacje!\nOto twoj koncowy wynik:\n\nInteligencja %d | Empatia %d | Sprawnosc %d | Pamiec %d | Wyobraznia %d | Urok %d",  tab_stat[0], tab_stat[1], tab_stat[2], tab_stat[3], tab_stat[4], tab_stat[5]);
            return 0;
        }
    } while (ruch > 0);
    return 0;
}