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
void del(node*& H) // usuwanie pierwszego elementu/wartownika
{
    if (H != NULL) // jeśli H jest różne od NULL 
    {
        node* p = H; // przypisz p do H
        H = H->next; // przesuń początek na kolejny element
        delete p; // usuń stare H ( pierwszy element listy) 
    }

}
void Split(node*& H, node*& H1, node*& H2) // dzieli listę na dwie (raz dodaje do jednej raz do drugiej )
{
    int i = 0; // przypisujemy inta który będzie wyznacznikiem do której listy ma zostać przypisany element
    node* p = H; //tworzymy wskaznik pomocniczy na listę która ma zostać podzielona
    AddLE(H1, 0, 0, 0); // dodajemy "wartownika" w liście nr 1
    node* a = H1; // wskaźnik pomocniczy na listę do której przypisujemy nr 1
    AddLE(H2, 0, 0, 0);//dodajemy "wartownika" w liście nr 2
    node* d = H2; // wskaźnik pomocniczy na listę do której przypisujemy nr 2
    while (p != NULL) // do końca
    {
        i++; // zwiekszamy i 
        if (i % 2 != 0) //jezeli i jest parzysty //przypisujemy do listy H1 nr 1
        {
            H = p->next; //wskazujemy Head-owi następny element (przesuwamy listę o jeden "w prawo"
            a->next = p; // przypisujemy pominięty element do listy nr 1
            a = a->next; // przejscie na kolejny element listy nr 1
        }
        else   //przypisujemy do listy H1 nr 1
        {
            H = p->next; //wskazujemy Head-owi następny element (przesuwamy listę o jeden "w prawo")
            d->next = p; // przypisujemy pominięty element do listy nr 2
            d = d->next;
        }
        p = p->next; //przejscie na kolejny element głównej listy
        if (H == NULL) //jezeli główna lista jest juz pusta
        {
            d->next = NULL; //przypisujemy ostatniemu wskaznikowi listy nr 1 NULL
            a->next = NULL; //przypisujemy ostatniemu wskaznikowi listy nr 2 NULL
        }
    }
    del(H1); del(H2); // usunięcie wartowników
}
void LinkSorted(node*& H1, node*& H2, node*& H) //funkcja sortuje i łączy elementy  do listy głównej
{
    AddLE(H, 0, 0, 0); // wartownik do listy wynikowej
    node* T = H; // wskaźnik na listę wynikową
    while (H1 && H2) // do końca list nr 1 i nr 2 (jeśli istnieją)
    {
        if (H1->dist < H2->dist) // jezeli dystans elementu z listy nr 1 jest mniejszy od nr 2
        {
            T->next = H1; //przypisujemy do listy głównej element mniejszy czyli z listy nr 1
            H1 = H1->next; //przejscie na kolejny element listy nr 1
            T = T->next; //przejscie na kolejny element listy głównej
        }
        else // w innym przypadku
        {
            T->next = H2; //dodaj do listy wynikowej element z listy nr 2
            H2 = H2->next; // przesuń wskaźnik listy nr 2 na kolejny element
            T = T->next; // przesuń listę wynikową na kolejny element 
        }
    }
    if (H1 == NULL) //jezeli lista nr 1 jest pusta
    {
        T->next = H2; //przypisz reszte listy nr 2 liście wynikowej
        H2 = NULL; //i przypisz NULL liście H2
    }
    else // w innym przypadku
    {
        T->next = H1; //przypisz reszte listy nr 1 liscie wynikowej
        H1 = NULL; //i przypisz NULL liscie nr 1
    }
    del(H); // usuń wartownik funkcji wynikowej
}
void mergeSort(node*& H) //funcka sortujaca elementy listy poprzez dzielenie ich na mniejsze listy
{
    node* p = H; // wskaźnik pomocniczy na podaną liste
    if (H != NULL && p->next != NULL) //jezeli lista wynikowa posiada co najmniej dwa elementy
    {
        node* H1 = NULL; // wskaźnik na listę nr 1 
        node* H2 = NULL; // wksaźnik na listę nr 2
        Split(H, H1, H2); // podziel listę podaną na listy nr 1 i 2 (mniejsze)
        mergeSort(H1); //rekurencja dla isty nr 1
        mergeSort(H2); // rekurencja dla listy nr 2
        LinkSorted(H1, H2, H);//sortuje i łaczy listy nr 1 i nr 2 spowrotem w listę podaną (posortowaną tym razem)
    }
}
void DoLER(node* LE, int las[], int kolor[], node*& LeR, int size) // Kruskal! // przyjmuje listę krawędzi bez powtórzeń , tablicę lasów , tablicę kolorów , listę wynikową , rozmiar tablic
{
    AddLE(LeR, 0, 0, 0); // wartownik dla listy wynikowej
    node* p = LE;  // wskaźnik na listę posortowanych krawędzi
    node* d = LeR; // wskaznik na liste wynikowa
    int wood = 0; // przypisujemy poziom lasu
    while (p != NULL) // aż dojdziemy do końca listy krawędzi
    {
        if (kolor[(p->from) - 1] == 0 && kolor[(p->to) - 1] == 0) // jeśli element  listy krawędzi trafia na dwie białe ( w tablicy) to
        {
            wood++; //las level up !
            kolor[(p->from) - 1] = 1; //zmienia kolor elmentu "skąd" na szary
            kolor[(p->to) - 1] = 1; // zmień kolor elementu "dokad"  na szary
            las[(p->from) - 1] = wood; //przypisuje level lasu elementowi "skąd"
            las[(p->to) - 1] = wood; //przypisuje level lasu elementowi "dokąd"
            LE = p->next; // przesuniecie na kolejny element (z pominieciem elementu p)                                                 // poprawka ! tutaj ej ej popatrz tam  <-------
            d->next = p; // przypisujemy kolejny element tablicy wynikowej (według tego na co wskazuje p)
            d = d->next; //przejscie na kolejny element
            p = LE; //powrót wskaźnika p na listę LE
        }
        else if (kolor[(p->from) - 1] != kolor[(p->to) - 1])  // jeśli element listy krawędzi trafia na dwie rożne  (w tablicy szary i biały) to
        {
            if (kolor[(p->from) - 1] == 1) //  jezeli kolor elemntu "skąd" jest szary
            {
                las[(p->to) - 1] = las[(p->from) - 1]; // przypisujemy level lasu elementu "skąd" elementowi "dokad" czyli dodajem do istniejacego lasu
                kolor[(p->to) - 1] = 1; // zmieniamy kolor elementu "dokąd" na szary
            }
            else // w przeciwnym razie bierzemy pod uwage element "dokąd"
            {
                las[(p->from) - 1] = las[(p->to) - 1]; // przypisujemy level lasu "dokad" elementowi "skad"  czyli dodajemy do istniejacego lasu
                kolor[(p->from) - 1] = 1;// zmieniamy kolor elementu "skąd" na szary
            }
            LE = p->next; // przesuniecie na kolejny element (z pominieciem elementu p)  
            d->next = p; // przypisujemy kolejny element tablicy wynikowej (według tego na co wskazuje p)
            d = d->next; //przejscie na kolejny element
            p = LE; //powrót wskaźnika p na listę LE
        }
        else if (kolor[(p->from) - 1] == 1 && kolor[(p->to) - 1] == 1) // jeśli elementy krawędzi trafia na  dwa szare (w tablicy) to
        {
            if (las[(p->from) - 1] == las[(p->to) - 1])  //jeżeli elementy mają ten sam level lasu
            {
                LE = p->next; // przesuniecie na kolejny element (z pominieciem elementu p)  
              //  las[(p->from) - 1] = wood; //zmień level lasu na wspólny level
              //  las[(p->to) - 1] = wood; // zamień level lasu na wspólny level wyższy
                delete p;  // usun wskaźnik
                p = NULL; //przypiisjemy wskasnikowi p NULL
                p = LE; // przypisz spowrotem do listy krawedzi
            }
            else if (las[(p->from) - 1] != las[(p->to) - 1])  // jezeli elementy mają różne levele lasu                         //ej ej psst psst tutaj też mnie popraw !!1
            {
                wood++; // level up!
                int one = las[(p->from) - 1]; // przypisujemy level lasu do "one" elementu "skad"  // przed zmiana
                int two = las[(p->to) - 1]; // przypisujem level lasu do "two" elemenru "dokąd"
                for (int i = 0; i < size; i++) // powtórz dla całej tablicy
                {
                    if (las[i] == one || las[i] == two) // jezeli poziom lasu i jest równy "one" lub "two"
                    {
                        las[i] = wood; // zmienia level lasu dla "i" elementu
                    }
                }
                LE = p->next; // przesuniecie na kolejny element (z pominieciem elementu p)  
                d->next = p; // przypisujemy kolejny element tablicy wynikowej (według tego na co wskazuje p)
                d = d->next; //przejscie na kolejny element
                p = LE; //powrót wskaźnika p na listę LE
            }
        }
    }
    d->next = NULL; // zakończenie listy wynikowej Nullem
    del(LeR); //usuwa wartownika listy wynikowej
}
int main()
{
    fstream czytaj; //zmienna czytaj klasy fstream
    czytaj.open("graf.txt"); // otwiera plik tekstowy "graf"    
    int rozmiar;// deklaracja rozmiaru  
    czytaj >> rozmiar; // pierwsza liczba w pliku jest rozmiarem macierzy kwadratowej (liczby powinny być oddzielone spacją/tabulatorem/enterem) 
    int** M = new int* [rozmiar]; // wskaźnik na tablice ze wskaźnikami na tablice (tablica tablic)
    node* LE = new node; LE = NULL; // wskaźnik na liste
    node* LER = new node; LER = NULL; // zadeklarowanie tablicy która jest wynikiem
    int* las = new int[rozmiar]; //wskaźnik na tablicę z levelami lasu
    int* kolor = new int[rozmiar]; //wskaźnik na tablicę z kolorami

    for (int i = 0; i < rozmiar; i++)
    {
        M[i] = new int[rozmiar]; // stwórz tablice dla tablicy elementu "i" w tablicy M  --- czyli przypisuje tablicy kolejne tablice jako elementy
        las[i] = 0;  //ustawia wartośc tablicy z levelami lasu na 0 (bez levelu)
        kolor[i] = 0;     // ustawia wartośc tablicy z kolorami na 0 (wszystkie białe)                     
        for (int j = 0; j < rozmiar; j++)  //pętla przechodząca po elementach wierszy z pliku tekstowego
        {
            czytaj >> M[i][j];  // czyta jedną liczbe z "macierzy" zapisanej w pliku tekstowym i ją zapisuje w tablicy tablic
            cout << M[i][j] << " "; // wypisz zapisany element
        }
        cout << endl; // odziela enterem w celu łatwiejszej wizualizacji  macierzy
    }
    for (int i = 0; i < rozmiar; i++)
        for (int j = 0; j < rozmiar; j++) // jeśli element jest różny od zera ( w Macierzy 0 oznacza brak połączenia z danym elementem)
            if (M[i][j] != 0 && i <= j)     // na potrzeby krawędzi bez powtórzeń został dodany warunek && i<=j
                AddEndLE(LE, j + 1, M[i][j], i + 1); //+1  dla dokładnych wartości , dodaj ten element do listy "i"  zapisując skąd dokąd i na jaką odległość się łączy
    cout << endl;
    mergeSort(LE); // sortujemy za pomocą mergesorta (podział na listy , rekurencja itd)
    cout << "Lista posortowanych krawedzi bez powtorzen->";
    showLE(LE);      cout << endl; // pokaz liste krawędzi 
    DoLER(LE, las, kolor, LER, rozmiar);
    cout << "Lista LER->";
    showLE(LER); // wywołuje funkcje Kruskala!
}
