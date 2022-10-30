#include <iostream>
#include <fstream>
using namespace std;
struct node
{
    int from; // skad
    int to; // dokad
    int dist; // odleglosc
    node* next; // wskażnik na sąsiada
};
void AddLE(node*& H, int x, int y, int z) // dodaj na poczatek
{
    node* p = new node; // tworzenie nowego elemntu grafu
    p->to = x;  // przypisanie mu numeru sąsiada do którego zmierza
    p->from = z; // przypisanie mu swojego polozenie (skad wychodzimy)
    p->dist = y; // przypisanie dystansu do sasiada
    p->next = H;  //przypianie mu wkażnika na kolejny element grafu
    H = p; // dodaj element do listy (na początek)
}
void AddEndLE(node*& H, int x, int y, int z) //dodaj na koniec
{
    node* p = H; // tworzenie nowego wskaźnika na liste
    if (p == NULL) // jeśli nie istnieje lista to przypisz na poczatek
    {
        AddLE(H, x, y, z);  // dodajemy na początek
    }
    else // jeśli istnieją elementy grafu
    {
        while (p->next != NULL) // przechodzi dalej aż do końca 
        {
            p = p->next; // kolejny element
        }
        node* ad = new node; // nowy znacznik
        ad->from = z;  // przypisanie mu swojego polozenia
        ad->to = x;   // przypisanie mu nastepnego wskaźnika - sąsiada
        ad->dist = y;  // przypisanie dystansu do nastepnego sasiad
        ad->next = NULL; // zerujemy kolejny element (żeby był końcem)
        p->next = ad; // dodaj element do listy jako kolejny element (na koniec)
    }

}
void show(node* H) //pokaż listę sasiedztwa
{
    cout << "LN ->"; // przed
    node* p = H; // wskaznik pomocniczy
    while (p != NULL) // aż do końca
    {
        cout << p->to << "dist" << p->dist << "-> "; // do kogo , jaki dystans
        p = p->next; // kolejny element
    }
    cout << "NULL" << endl;
}
int suma(int tab[], int size) // liczymy sume tablicy
{
    int suma = 0; //deklaracja zmiennej
    for (int i = 0; i < size; i++)
    {
        suma = suma + tab[i]; //dodaj element do sumy calkowitej
    }
    return suma; // zwróć sume
}
void Dijkstra(node** LN, int kolor[], int poprzednik[], int odleglosc[], int s, int size) //przyjmuje  liste sasiadów , tablice kolorów , tablice poprzedników, tablice odleglosci , punkt startowy
{                                                                                               // rozmiar tablic , wypisuje najmniejsze 
    kolor[s - 1] = 1; // ustaw kolor startowego wierzchołka na szary
    poprzednik[s - 1] = NULL; // poprzednik startowego wierzchołka na 0 
    odleglosc[s - 1] = 0; // dystans do startowego wierzchołka na 0
    node* p = new node; // wskaźnik pomocniczy
    node* d = new node; // wskaźnik pomocniczy
    int mindist; //zmienna do przechowania wierzchołka z najmniejszym dystansem
    int dystans = 0;  //zmienna utworzona do mierzenia smy dystansów pomiędzy wierzchołkami
    int min, min2;  // min globalne i lokalne
    for (int j = 0; j < size; j++) //główna pętl sprawdzająca kolory wierzchołków
    {
        min = 2147483647;  // min = globalne , min2 = lokalne dla szarych
        min2 = 2147483647;//przypisanie zmiennym min,min2 najwiekszego mozliwego inta
        if (kolor[j] == 1) //jezeli wierzchołek j ma kolor szary 
        {
            for (int f = 0; f < size; f++) //pętla sprawdzająca kolejno wszystkie wierzchołki szare , ma za zadanie znaleźć najmniejszy dystans
            {
                if (kolor[f] == 1 && odleglosc[f] < min2)//jezeli kolor wierzchołka f jest szary && odleglosc wierzcholka f jest miejsza od min lokalnego
                {
                    min2 = odleglosc[f]; //pzypisz min lokalnemu dystans wierzcholka f
                    mindist = f; //zapisuje wierzchołek a najblizszej odleglosci
                }


            }
            j = mindist; //przypisujemy j wartosc "mindst" czyli szary wierzchołek z najmniejszym dystansem

            p = LN[j]; //sprawdzamy liste sasiadow dla naszego "j"
            while (p != NULL) //do konca
            {
                if (kolor[p->to - 1] == 1) //jezeli kolor wierzcholka do którego zmierza wierzchołek "j" jest szary
                {
                    if (odleglosc[j] + p->dist < odleglosc[p->to - 1]) //jezeli odleglosc wierzcholka j (od poprzednika) + dystans do "dokąd" jest  mniejszy od odleglosci wierzchołka                                                  
                    {                                                                                                                                       // "dokąd"(od poprzednika)
                        poprzednik[p->to - 1] = j + 1; // przypisujemy wierzchołkowi "dokąd" nowego poprzednika "j"  //+1 aby były dokładne wartości
                        odleglosc[p->to - 1] = odleglosc[j] + p->dist; //przypisujemy wierzchołkowi "dokąd" odleglosc wierzchołka "j" + dystansu pomiędzy nimi 
                    }

                }
                else if (kolor[p->to - 1] == 0) //jezeli kolor wierzchołka "dokąd" do którego zmierza wierzchołek "j" jest biały
                {
                    dystans = odleglosc[j] + p->dist; // dystans zapisuje wartość odleglosci poprzednika i dystansu miedzy nimi
                    odleglosc[p->to - 1] = dystans; //przypisuje odleglosc wierzchołka "dokąd" równą odleglosci poprzenika i dystansu pomiedzy nimi
                    poprzednik[p->to - 1] = j + 1; // poprzednik "dokąd" = "skąd" czyli j+1
                    kolor[p->to - 1] = 1;  // zmienia kolor wierzchołka "dokąd" na szary
                    if (p->dist < min) // jeśli dystans miedzy nimi jest mniejszy od aktualnego min 
                    {
                        min = p->dist; //przypisz wartość min dystans pomiędzy wierzchołkami "j" i "dokąd"
                        d = p; // przypisz wskaźnik do wierzchołka z najmniejszym dystansem
                    }
                }
                p = p->next; //dalej dalej wskazniku
            }
        }
        if (suma(kolor, size) == (size + size) - 1) //jest to warunek zamykający pętlę sprawdzający czy suma wszystkich czarnych kolorów (dwujek) jest równy rozmiar*2 -1 
        {                                                                                                                       //  (jest to przypadek kiedy został już ostatni szary wierzchołek)
            for (int end = 0; end < size; end++)  // przechodzi po wszystkich kolorach
            {
                kolor[end] = 2; //przpisuje wierzchołkom czarny kolor
            }
            cout << "Koniec" << endl;
            cout << "Wierzchołki\t";
            for (int i = 0; i < size; i++)
            {
                cout << i + 1 << "\t"; // wypisz wartośc wierzchołka + 1(numerowane od 0)
            } cout << endl;
            cout << "Kolory\t\t";
            for (int i = 0; i < size; i++)
            {
                cout << kolor[i] << "\t"; // wypisuje tablice kolorów wierzcholkow
            } cout << endl;
            cout << "Poprzdniki\t";
            for (int i = 0; i < size; i++)
            {
                cout << poprzednik[i] << "\t"; //wypisuje tablice poprzednikow wierzcholkow
            }cout << endl;
            cout << "Odleglosci\t";
            for (int i = 0; i < size; i++)
            {
                cout << odleglosc[i] << "\t"; // wypisuje tablice odleglosci od wierzchołka startowego 
            }cout << endl;
            break;
        }
        kolor[j] = 2; //zamalowanie wierzchołka na którym jestesmy na czarno przed przejsciem na nastepny
        j = d->to - 2; // wcześniej została dwukrotnie dodane +1 dlatego musimy odjąc -2
    }
}

int main()
{
    fstream czytaj; //zmienna czytaj klasy fstream
    czytaj.open("graf.txt"); // otwiera plik tekstowy "graf"    
    int rozmiar;// deklaracja rozmiaru  
    czytaj >> rozmiar; // pierwsza liczba w pliku jest rozmiarem macierzy kwadratowej (liczby powinny być oddzielone spacją/tabulatorem/enterem) 
    int** M = new int* [rozmiar]; // wskaźnik na tablice ze wskaźnikami na tablice (tablica tablic)
    node** LN = new node * [rozmiar]; // tablica wskaźników na listy
    int* kolor = new int[rozmiar]; // tablica kolorów
    int* poprzednik = new int[rozmiar]; //tablica poprzedników
    int* odleglosc = new int[rozmiar]; //tablica odleglosci

    for (int i = 0; i < rozmiar; i++) //rezerwowanie pamieci na tablice 
    {
        M[i] = new int[rozmiar];
        LN[i] = NULL;
    }
    for (int i = 0; i < rozmiar; i++)
    {
        for (int j = 0; j < rozmiar; j++)
        {
            czytaj >> M[i][j]; //wczytaj wartość z pliku txt
            cout << M[i][j] << " "; // wypisz zapisana wartość
        }
        cout << endl;
    }
    for (int i = 0; i < rozmiar; i++) //ustawianie tabel na wartości domyślne
    {
        kolor[i] = 0;   // białe wierzchołki
        poprzednik[i] = -1;  // poprzednik mniejszy od 0 = brak poprzednika
        odleglosc[i] = -1;  // odleglosc od startu mniejsza od 0= nie została jeszcze przypisana
    }
    for (int i = 0; i < rozmiar; i++)
        for (int j = 0; j < rozmiar; j++)
            if (M[i][j] != 0)
                AddEndLE(LN[i], j + 1, M[i][j], i + 1); // towrzy liste sasiadow
    for (int i = 0; i < rozmiar; i++)
    {
        show(LN[i]); // wyswietla kolejne listy sasiadow 
    }
    //  int n = 0;
    Dijkstra(LN, kolor, poprzednik, odleglosc, 1, rozmiar);
}
