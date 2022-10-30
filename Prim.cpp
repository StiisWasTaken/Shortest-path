#include <iostream>
#include <fstream>
using namespace std;
struct node // tworzymy strukturę grafu (elementy)
{
    int from;  // skad
    int to;  // dokad
    int dist; // odleglosc
    node* next; // wskażnik na sąsiada
};
void AddLE(node*& H, int x, int y, int z) //dodajemy do listy na początek (jesli graf nie ma elementów)
{
    node* p = new node; // tworzenie nowego elemntu grafu
    p->to = x; // przypisanie mu numeru sąsiada do którego zmierza
    p->from = z; // przypisanie mu swojego polozenie (skad wychodzimy)
    p->dist = y; // przypisanie dystansu do sasiada
    p->next = H; //przypianie mu wkażnika na kolejny element grafu
    H = p;   // dodaj element do listy (na początek)
}
void AddEndLE(node*& H, int x, int y, int z) // dodajemy na koniec listy
{
    node* p = H; // tworzenie nowego elemntu grafu
    if (p == NULL) // jeśli nie istnieje lista to przypisz na poczatek
    {
        AddLE(H, x, y, z); // dodajemy na początek
    }
    else // jeśli istnieją elementy grafu
    {
        while (p->next != NULL) // przechodzi dalej aż do końca 
        {
            p = p->next;  // kolejny element
        }
        node* ad = new node; // nowy znacznik
        ad->from = z;  // przypisanie mu swojego polozenia
        ad->to = x;  // przypisanie mu nastepnego wskaźnika - sąsiada
        ad->dist = y; // przypisanie dystansu do nastepnego sasiad
        ad->next = NULL; // zerujemy kolejny element (żeby był końcem)
        p->next = ad; // dodaj element do listy jako kolejny element (na koniec)
    }

}
void show(node* H) // pokaż liste sąsiadów 
{
    cout << "LN ->";
    node* p = H;
    while (p != NULL) // aż do końca
    {
        cout << p->to << "dist" << p->dist << "-> "; // informacja dokąd i jak daleko 
        p = p->next; // kolejny element listy
    }
    cout << "NULL" << endl;
}
void showLE(node* H) //pokaż listę krawędzi grafu
{
    cout << "LE->"; // przed
    node* p = H; // przypisz znacznik do listy
    while (p != NULL) // aż do końca
    {
        cout << "from" << p->from << "to" << p->to << "dist" << p->dist << "-> "; // informacja skad , dokąd i jaka odległość
        p = p->next; // kolejny element listy
    }
    cout << "NULL" << endl; // po zakończeniu listy
}
void Prim(node** LN, int kolor[], int s, node*& H, int size) // algorytm Prima , wypisuje połączenia na podstawie listy list , tabeli kolorów , ustaloną liczbą(wierzchołek) startową
{                                                               // oraz rozmiaru tabel , wynikiem jest lista połączeń z punktu startowego która zawiera informacje skad dokąd i jaka odległość.
    kolor[s - 1] = 1; // zamalowanie wybrnego wierzchołka na szary , -1 bierze sie stad że używamy dokładnych wartości ( w mainie zostało zapisane i+1)
    node* p = new node;  // tworzenie znaczników pomocniczych
    node* d = new node;  // tworzenie znaczników pomocniczych
    int min; // deklaracja min
    for (int j = 0; j < size; j++) 
    {
        min = 2147483647;  // przypisanie min maxymalnego inta (MAX_INT)
        for (int i = 0; i < size; i++) // pętla ma się powtórzyć po całej tablicy (size - rozmiar tablicy)
        {
            if (kolor[i] == 1) // jeśli kolor elementu jest szary 
            {
                p = LN[i];  //ustaw znacznik pomocniczy na listę sąsiadow elementu szarego 
                while (p != NULL)  // działaj aż dojdziesz do końca
                {
                    if (p->dist < min && kolor[p->to - 1] == 0) // jeśli dystans do sąsiada wybranego szarego elementu jest mniejszy od aktualnego MIN i sąsiad ten jest biały
                    {
                        min = p->dist; // ustaw aktualne min na nowy mniejszy dystans
                        d = p;  // przypisz ten element listy do drugiego wskaźnika żeby móc wykorzystać go później
                    }
                    p = p->next; // kolejny element
                }
            }
        }
        if (min != 2147483647) // jeśli MIN jest różne od MAX INT (czyli zostało zmienione podczas pętli) to
        {
            AddEndLE(H, d->to, d->dist, d->from); // dodaj na koniec listy element który ostatecznie został przypisany jako d (najmniejszy dystans + biały )
            kolor[d->to - 1] = 1;  // pomaluj go na szaro
        }

    }
}
int main()
{
    fstream czytaj; //zmienna czytaj klasy fstream
    czytaj.open("graf.txt"); // otwiera plik tekstowy "graf"    
    int rozmiar; // deklaracja rozmiaru                                                                                                   // rezerwowanie miejsca w pamięci na kolejne elementy
    czytaj >> rozmiar; // pierwsza liczba w pliku jest rozmiarem macierzy kwadratowej (liczby powinny być oddzielone spacją/tabulatorem/enterem)
    int** M = new int* [rozmiar]; // wskaźnik na tablice ze wskaźnikami na tablice (tablica tablic)
    node** LN = new node * [rozmiar]; // wskaźnik na tablicę list
    node* H = new node; H = NULL;// zadeklarowanie tablicy która jest wynikiem
    int* kolor = new int[rozmiar]; //wskaźnik na tablicę z kolorami
    for (int i = 0; i < rozmiar; i++)
    {
        M[i] = new int[rozmiar]; // stwórz tablice dla tablicy elementu "i" w tablicy M  --- czyli przypisuje tablicy kolejne tablice jako elementy
        LN[i] = NULL; //przypisuje kolejnym listom NULLa (deklaruje je)
        kolor[i] = 0; // ustawia wartośc tablicy z kolorami na 0 (wszystkie białe)
    }
    for (int i = 0; i < rozmiar; i++)
    {
        for (int j = 0; j < rozmiar; j++)     
        {
            czytaj >> M[i][j]; // czyta jedną liczbe z "macierzy" zapisanej w pliku tekstowym i ją zapisuje w tablicy tablic
            cout << M[i][j] << " "; // wypisz zapisany element
        }
        cout << endl; // odziela enterem w celu łatwiejszej wizualizacji  macierzy
    }
    for (int i = 0; i < rozmiar; i++)
        for (int j = 0; j < rozmiar; j++)
            if (M[i][j] != 0) // jeśli element jest różny od zera ( w Macierzy 0 oznacza brak połączenia z danym elementem)
                AddEndLE(LN[i], j + 1, M[i][j], i + 1); //dodaj ten element do listy "i"  zapisując skąd dokąd i na jaką odległość się łączy
    for (int i = 0; i < rozmiar; i++)
    {
        show(LN[i]); // wypisuje kolejne listy sąsiadów 
    }
    Prim(LN, kolor, 3, H, rozmiar); // Algorytm Prim
    cout <<"Lista wynikowa"<<endl;
    showLE(H); // pokazuje liste wynikową z Prima
}
