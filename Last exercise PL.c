#include <stdio.h>
#include <string.h>


// Program okazal sie stosunkowo dlugi, co wynika z rozdrobnienia funkcji, ale uznalem ze jest to lepsze rozwiazanie niz
// tworzenie dlugich funkcji z wieloma zbednymi arugmentami (np jednej funkcji dla usuwania, w ktorej dopiero wybiera sie co usuwamy).
// Program ostrzega w wielu miejscach o np wpisaniu zlego numeru albumu i zadowalajaco przechodzil wielorakie testy.
// Program dzialal bez tego, ale debugger wymagal podawania dlugosci przy uzywaniu scanf_s i fscanf_s, wiec je zostawilem.


struct student {
    char imie[16]; // Dlugosc imienia i nazwiska na podstawie jednego z wczesniejszych zadan z pracownikami.
    char nazwisko[64];
    long long int nr_albumu; // Numer albumu moglby byc tez jako char, ale wymagaloby to naduzywania funkcji strcmp.
};


struct ocena_z_programowania {
    long long int nr_albumu;
    char ocena[3]; // Ocena docelowo moze byc z plusem lub minusem.
};


struct ocena_z_fizyki {
    long long int nr_albumu;
    char ocena[3];
};


// Funkcje dodajace nowe elementy sa osobne dla kazdego typu struktury.
// Dzialaja one bardzo podobnie do siebie i zwracaja odpowiednia strukture.
struct student opcja_N() {
    struct student nowy_student;
    printf("Podaj imie nowego studenta:\n>");
    scanf_s("%s", nowy_student.imie, 16);
    printf("Podaj nazwisko nowego studenta:\n>");
    scanf_s("%s", nowy_student.nazwisko, 64);
    printf("Podaj numer albumu nowego studenta:\n>");
    scanf_s("%lld", &nowy_student.nr_albumu, 20);
    return nowy_student;
}


struct ocena_z_programowania opcja_O_P() {
    struct ocena_z_programowania nowa_ocena_z_programowania;
    printf("Podaj nowa ocene z programowania:\n>");
    scanf_s("%s", nowa_ocena_z_programowania.ocena, 3);
    printf("Podaj numer albumu:\n>");
    scanf_s("%lld", &nowa_ocena_z_programowania.nr_albumu, 20);
    return nowa_ocena_z_programowania;
}


struct ocena_z_fizyki opcja_O_F() {
    struct ocena_z_fizyki nowa_ocena_z_fizyki;
    printf("Podaj nowa ocene z fizyki:\n>");
    scanf_s("%s", nowa_ocena_z_fizyki.ocena, 3);
    printf("Podaj numer albumu:\n>");
    scanf_s("%lld", &nowa_ocena_z_fizyki.nr_albumu, 20);
    return nowa_ocena_z_fizyki;
}


// Wiekszosc funkcji ma typ void, poniewaz jako parametry biora wskazniki odpowiednich list struktur i na nich dzialaja.
// Fukcje usuwajace elementy tez sa osobne dla kazdego typu struktury, ale sa bardzo podobne.
void opcja_U_S(struct student* studenci, int N) {
    int indeks;
    long long int album_do_usuniecia;
    int byl_indeks = 0; // W paru funkcjach pojawiaja sie zmienne tego typu, sprawdzajace czy nalezy wypisac odpowiednia informacje zwrotna pod koniec jakiejs petli.
    printf("Podaj numer albumu usuwanego studenta:\n>");
    scanf_s("%lld", &album_do_usuniecia, 20);
    for (indeks = 0; indeks < N; indeks++) {
        if (studenci[indeks].nr_albumu == album_do_usuniecia) {
            byl_indeks = 1;
            break;
        }
    }
    if (byl_indeks == 0) { // W tym przypadku jest to informacja o blednym numerze indeksu w przypadku nieznalezienia wpisanego.
        printf("Podano bledny numer albumu.\n");
    }
    for (indeks = indeks; indeks < N; indeks++) { // Przestawianie pozostalych elementow funkcji.
        studenci[indeks] = studenci[indeks + 1];
    }
}


void opcja_U_P(struct ocena_z_programowania* oceny_z_programowania, int M) {
    int indeks;
    long long int album_do_usuniecia;
    int byl_indeks = 0;
    char ocena[3];
    printf("Podaj numer albumu:\n>");
    scanf_s("%lld", &album_do_usuniecia, 20);
    printf("Podaj ocene:\n>");
    scanf_s("%s", ocena, 3);
    for (indeks = 0; indeks < M; indeks++) {
        if (oceny_z_programowania[indeks].nr_albumu == album_do_usuniecia && (strcmp(oceny_z_programowania[indeks].ocena, ocena) == 0)) {
            byl_indeks = 1;
            break;
        }
    }
    if (byl_indeks == 0) {
        printf("Podano bledny numer albumu lub ten student nie ma takiej oceny z programowania.\n");
    }
    for (indeks = indeks; indeks < M; indeks++) {
        oceny_z_programowania[indeks] = oceny_z_programowania[indeks + 1];
    }
}


void opcja_U_F(struct ocena_z_fizyki* oceny_z_fizyki, int K) {
    int indeks;
    long long int album_do_usuniecia;
    int byl_indeks = 0;
    char ocena[3];
    printf("Podaj numer albumu:\n>");
    scanf_s("%lld", &album_do_usuniecia, 20);
    printf("Podaj ocene:\n>");
    scanf_s("%s", ocena, 3);
    for (indeks = 0; indeks < K; indeks++) {
        if (oceny_z_fizyki[indeks].nr_albumu == album_do_usuniecia && (strcmp(oceny_z_fizyki[indeks].ocena, ocena) == 0)) {
            byl_indeks = 1;
            break;
        }
    }
    if (byl_indeks == 0) {
        printf("Podano bledny numer albumu lub ten student nie ma takiej oceny z fizyki.\n");
    }
    for (indeks = indeks; indeks < K; indeks++) {
        oceny_z_fizyki[indeks] = oceny_z_fizyki[indeks + 1];
    }
}


// Funkcja wypisujaca informacje o studencie/studentach o danym nazwisku.
void opcja_W(struct student* studenci, int N, struct ocena_z_programowania* oceny_z_programowania, int M, struct ocena_z_fizyki* oceny_z_fizyki, int K) {
    char nazwisko_do_pokazania[64];
    int i;
    int j;
    int byla_ocena = 0; // Zmienna odpowiedzialna zarowno za wypisywanie przecinkow przy wielu ocenach, jak i za informacje zwrotne pod koniec petli wewnetrznych.
    int bylo_nazwisko = 0; // Zmienna odpowiedzialna za informacja zwrotna na koncu glownej petli.
    printf("Podaj nazwisko studenta:\n>");
    scanf_s("%s", nazwisko_do_pokazania, 64);
    for (i = 0; i < N; i++) {
        if (strcmp(studenci[i].nazwisko, nazwisko_do_pokazania) == 0) {
            printf("\n");
            bylo_nazwisko = 1;
            printf("Imie: %s\n", studenci[i].imie);
            printf("Nazwisko: %s\n", studenci[i].nazwisko);
            printf("Numer albumu: %lld\n", studenci[i].nr_albumu);
            printf("Oceny z programowania: ");
            for (j = 0; j < M; j++) {
                if (studenci[i].nr_albumu == oceny_z_programowania[j].nr_albumu) {
                    if (byla_ocena == 1) {
                        printf(", ");
                    }
                    printf("%s", oceny_z_programowania[j].ocena);
                    byla_ocena = 1;
                }
            }
            if (byla_ocena == 0) {
                printf("Brak.");
            }
            printf("\n");
            byla_ocena = 0;
            printf("Oceny z fizyki: ");
            for (j = 0; j < K; j++) {
                if (studenci[i].nr_albumu == oceny_z_fizyki[j].nr_albumu) {
                    if (byla_ocena == 1) {
                        printf(", ");
                    }
                    printf("%s", oceny_z_fizyki[j].ocena);
                    byla_ocena = 1;
                }
            }
            if (byla_ocena == 0) {
                printf("Brak.");
            }
            printf("\n");
            byla_ocena = 0;
        }
    }
    if (bylo_nazwisko == 1) printf("\nTo wszyscy studenci z tym nazwiskiem.");
    else printf("Nie ma studenta o takim nazwisku.");
    printf("\n");
}


// Funkcja robiaca to samo co poprzednia tylko na podstawie numeru albumu.
void opcja_A(struct student* studenci, int N, struct ocena_z_programowania* oceny_z_programowania, int M, struct ocena_z_fizyki* oceny_z_fizyki, int K) {
    long long int album_do_pokazania;
    int i;
    int j;
    int byla_ocena = 0;
    int byl_album = 0;
    printf("Podaj numer albumu studenta:\n>");
    scanf_s("%lld", &album_do_pokazania, 20);
    for (i = 0; i < N; i++) {
        if (studenci[i].nr_albumu == album_do_pokazania) {
            byl_album = 1;
            printf("Imie: %s\n", studenci[i].imie);
            printf("Nazwisko: %s\n", studenci[i].nazwisko);
            printf("Numer albumu: %lld\n", studenci[i].nr_albumu);
            printf("Oceny z programowania: ");
            for (j = 0; j < M; j++) {
                if (studenci[i].nr_albumu == oceny_z_programowania[j].nr_albumu) {
                    if (byla_ocena == 1) {
                        printf(", ");
                    }
                    printf("%s", oceny_z_programowania[j].ocena);
                    byla_ocena = 1;
                }
            }
            if (byla_ocena == 0) {
                printf("Brak.");
            }
            printf("\n");
            byla_ocena = 0;
            printf("Oceny z fizyki: ");
            for (j = 0; j < K; j++) {
                if (studenci[i].nr_albumu == oceny_z_fizyki[j].nr_albumu) {
                    if (byla_ocena == 1) {
                        printf(", ");
                    }
                    printf("%s", oceny_z_fizyki[j].ocena);
                    byla_ocena = 1;
                }
            }
            if (byla_ocena == 0) {
                printf("Brak.");
            }
            break; // Poniewaz numery albumow sa unikatowe po jednym studenci mozna zastosowac break.
        }
    }
    if (byl_album == 0) printf("Nie ma studenta z takim numerem albumu.");
    printf("\n");
}


// Funkcja wypisujaca dane z listy struktur do plikow.
void opcja_Z(struct student* studenci, int N, struct ocena_z_programowania* oceny_z_programowania, int M, struct ocena_z_fizyki* oceny_z_fizyki, int K) {
    int i;
    FILE* plik;
    char nazwa_pliku[100];
    printf("Podaj nazwe pliku, do ktorego zapisac studentow lub wpisz 0, by nie zapisywac danych:\n>");
    scanf_s("%s", nazwa_pliku, 100);
    if ((strcmp(nazwa_pliku, "0")) != 0) {
        fopen_s(&plik, nazwa_pliku, "w");
        fprintf(plik, "%d\n", N);
        for (i = 0; i < N; i++) {
            fprintf(plik, "%s\n", studenci[i].imie);
            fprintf(plik, "%s\n", studenci[i].nazwisko);
            fprintf(plik, "%lld\n", studenci[i].nr_albumu);
        }
        fclose(plik);
        printf("Zapisano studentow do pliku %s.\n", nazwa_pliku);
    }
    printf("\n");

    printf("Podaj nazwe pliku, do ktorego zapisac oceny z programowania lub wpisz 0, by nie zapisywac danych:\n>");
    scanf_s("%s", nazwa_pliku, 100);
    if ((strcmp(nazwa_pliku, "0")) != 0) {
        fopen_s(&plik, nazwa_pliku, "w");
        fprintf(plik, "%d\n", M);
        for (i = 0; i < M; i++) {
            fprintf(plik, "%lld\n", oceny_z_programowania[i].nr_albumu);
            fprintf(plik, "%s\n", oceny_z_programowania[i].ocena);
        }
        fclose(plik);
        printf("Zapisano oceny z programowania do pliku %s.\n", nazwa_pliku);
    }
    printf("\n");

    printf("Podaj nazwe pliku, do ktorego zapisac oceny z fizyki lub wpisz 0, by nie zapisywac danych:\n>");
    scanf_s("%s", nazwa_pliku, 100);
    if ((strcmp(nazwa_pliku, "0")) != 0) {
        fopen_s(&plik, nazwa_pliku, "w");
        fprintf(plik, "%d\n", K);
        for (i = 0; i < K; i++) {
            fprintf(plik, "%lld\n", oceny_z_fizyki[i].nr_albumu);
            fprintf(plik, "%s\n", oceny_z_fizyki[i].ocena);
        }
        fclose(plik);
        printf("Zapisano oceny do pliku %s.\n", nazwa_pliku);
    }
}


// Funkcja main zawierajaca menu i czytajaca dane z plikow na poczatku programu.
int main() {
    printf("Dzien dobry!\n\n");
    // Wczytywanie danych z plikow - najpierw dla studentow, pozniej na tej samej zasadzie dla ocen.
    char nazwa_pliku[100];
    int i;
    FILE* plik;
    struct student studenci[50];
    int N; // Zmienna oznaczajaca ilosc elementow w liscie struktur studenci. W dalszej czesci analogicznie dla M i K przy ocenach.
    printf("Podaj nazwe pliku, z ktorego wczytac studentow lub wpisz 0, by nie wczytywac danych:\n>");
    scanf_s("%s", nazwa_pliku, 100);
    if ((strcmp(nazwa_pliku, "0")) != 0) {
        fopen_s(&plik, nazwa_pliku, "r");
        while (plik == NULL) { // Test czy nazwa pliku jest poprawna.
            printf("Podano bledna nazwe pliku. Sprobuj ponownie:\n");
            scanf_s("%s", nazwa_pliku, 100);
            fopen_s(&plik, nazwa_pliku, "r");
        }
        fscanf_s(plik, "%d", &N, 128);
        for (i = 0; i < N; i++) { // Trzy linijki danych dla kazdego z N studentow, od razu przypisuje do listy struktur.
            fscanf_s(plik, "%s", studenci[i].imie, 16);
            fscanf_s(plik, "%s", studenci[i].nazwisko, 64);
            fscanf_s(plik, "%lld", &studenci[i].nr_albumu, 20);
        }
        fclose(plik);
        printf("Wczytano studentow z pliku %s.\n", nazwa_pliku);
    }
    else N = 0; // Jezeli nie wczytujemy danych z pliku to N = 0.
    printf("\n");

    struct ocena_z_programowania oceny_z_programowania[50];
    int M;
    printf("Podaj nazwe pliku, z ktorego wczytac oceny z programowania lub wpisz 0, by nie wczytywac danych:\n>");
    scanf_s("%s", nazwa_pliku, 100);
    if ((strcmp(nazwa_pliku, "0")) != 0) {
        fopen_s(&plik, nazwa_pliku, "r");
        while (plik == NULL) {
            printf("Podano bledna nazwe pliku. Sprobuj ponownie:\n");
            scanf_s("%s", nazwa_pliku, 100);
            fopen_s(&plik, nazwa_pliku, "r");
        }
        fscanf_s(plik, "%d", &M, 20);
        for (i = 0; i < M; i++) {
            fscanf_s(plik, "%lld", &oceny_z_programowania[i].nr_albumu, 20);
            fscanf_s(plik, "%s", oceny_z_programowania[i].ocena, 3);
        }
        fclose(plik);
        printf("Wczytano oceny z programowania z pliku %s.\n", nazwa_pliku);
    }
    else M = 0;
    printf("\n");

    struct ocena_z_fizyki oceny_z_fizyki[50];
    int K;
    printf("Podaj nazwe pliku, z ktorego wczytac oceny z fizyki lub wpisz 0, by nie wczytywac danych:\n>");
    scanf_s("%s", nazwa_pliku, 100);
    if ((strcmp(nazwa_pliku, "0")) != 0) {
        fopen_s(&plik, nazwa_pliku, "r");
        while (plik == NULL) {
            printf("Podano bledna nazwe pliku. Sprobuj ponownie:\n>");
            scanf_s("%s", nazwa_pliku, 100);
            fopen_s(&plik, nazwa_pliku, "r");
        }
        fscanf_s(plik, "%d", &K, 128);
        for (i = 0; i < K; i++) {
            fscanf_s(plik, "%lld", &oceny_z_fizyki[i].nr_albumu, 20);
            fscanf_s(plik, "%s", oceny_z_fizyki[i].ocena, 3);
        }
        fclose(plik);
        printf("Wczytano oceny z fizyki z pliku %s.\n", nazwa_pliku);
    }
    else K = 0;
    printf("\n");

    char zbedny_znak; // Zmienna zbierajaca zbedne znaki \n pojawiajace sie przy scanf_s.
    char opcja; // Zmienna przechowywujaca instrukcje.
    // Pierwsze wyswietlenie menu i pobranie opcji przed petla, pozniejsze zawsze na koncu petli.
    printf("Wybierz opcje:\nN - wprowadzenie nowego studenta.\n");
    printf("O - wprowadzenie nowej oceny.\nU - usuniecie studenta lub oceny.\n");
    printf("W - wyprowadzenie informacji o studencie na bazie nazwiska.\n");
    printf("A - wyprowadzenie informacji o studencie na bazie numeru albumu.\n");
    printf("Z - zapisanie danych do plikow.\nQ - wyjscie.\n>");
    scanf_s("%c", &opcja, 1);
    while (opcja != 'Q') { // glowna petla (Q konczy program).
        // Mala czesc operacji (szczegolnie na N, M i K), dzieje sie poza funkcjami.
        switch (opcja) {
        case 'N':
            printf("\n");
            studenci[N] = opcja_N(); // Na puste miejsce dodany jest nowy student.
            N++; // A licznik przeskakuje do gory.
            for (i = 0; i < N - 1; i++) { // Dodatkowe sprawdzenie czy numery albumow sie nie powtarzaja.
                if (studenci[N - 1].nr_albumu == studenci[i].nr_albumu) {
                    printf("Jest juz inny student o takim numerze albumu.\n");
                    N--; // Jesli tak to licznik wraca do poprzedniego ustawienia.
                }
            }
            break;
        case 'O':
            printf("\n");
            printf("Wybierz:\nP - dodanie oceny z programowania.\nF - dodanie oceny z fizyki.\n>");
            scanf_s("%c%c", &zbedny_znak, 1, &opcja, 1);
            printf("\n");
            // Jak juz pisalem funkcje sa "rozdrobnione", stad wewnetrzny switch.
            switch (opcja) {
            case 'P':
                oceny_z_programowania[M] = opcja_O_P();
                M++; // Zwiekszenie odpowiedniego licznika po dodaniu oceny.
                break;
            case 'F':
                oceny_z_fizyki[K] = opcja_O_F();
                K++; // Tutaj podobnie.
                break;
            }
            break;
        case 'U':
            printf("\n");
            printf("Wybierz:\nS - usuniecie studenta.\nP - usuniecie oceny z programowania.\nF - usuniecie oceny z fizyki.\n>");
            scanf_s("%c%c", &zbedny_znak, 1, &opcja, 1);
            printf("\n");
            // Kolejny wewnetrzny switch.
            switch (opcja) {
            case 'S':
                // Usuniecie studenta nie powoduje usuniecia jego ocen, tak samo mozna dodac ocene do numeru albumu, a potem dopiero studenta o takim numerze albumu.
                opcja_U_S(studenci, N);
                N--; // Obniżanie odpowienich licznikow.
                break;
            case 'P':
                opcja_U_P(oceny_z_programowania, M);
                M--; // Tak samo.
                break;
            case 'F':
                opcja_U_F(oceny_z_fizyki, K);
                K--; // Tak samo.
                break;
            }
            break;
        case 'W':
            printf("\n");
            opcja_W(studenci, N, oceny_z_programowania, M, oceny_z_fizyki, K);
            break;
        case 'A':
            printf("\n");
            opcja_A(studenci, N, oceny_z_programowania, M, oceny_z_fizyki, K);
            break;
        case 'Z':
            printf("\n");
            opcja_Z(studenci, N, oceny_z_programowania, M, oceny_z_fizyki, K);
        }
        // Menu wyswietla sie tylko, gdy wykonala sie jakas funkcja w tej iteracji petli.
        // Pomaga to glownie w tym, ze gdy scanf_s wylapie jakis niechciany znak pokroju \n, to menu nie wyswietla sie pare razy pod rzad, a uzytkownik nawet nie wie, ze petla wykonala zbedna iteracje.
        // Z tego samego powodu printf("\n"); jest wewnatrz kazdego case, a nie po while.
        if (opcja == 'N' || opcja == 'O' || opcja == 'P' || opcja == 'F' || opcja == 'U' || opcja == 'S' || opcja == 'W' || opcja == 'A' || opcja == 'Z') {
            printf("Gotowe.\n\nWybierz opcje:\nN - wprowadzenie nowego studenta.\n");
            printf("O - wprowadzenie nowej oceny.\nU - usuniecie studenta lub oceny.\n");
            printf("W - wyprowadzenie informacji o studencie na bazie nazwiska.\n");
            printf("A - wyprowadzenie informacji o studencie na bazie numeru albumu.\n");
            printf("Z - zapisanie danych do plikow.\nQ - wyjscie.\n>");
        }
        scanf_s("%c", &opcja, 1);
    }
    printf("\nDo widzenia.\n");
    return 0;
}
