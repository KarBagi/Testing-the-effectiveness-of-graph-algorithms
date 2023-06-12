#include <iostream>
#include <fstream>
#include <windows.h>
#include <string>
#include <time.h>
#include "testowanie.h"
#include "graf.h"

using namespace std;

void Testowanie::testowanieMST()
{
    Czas czas;
    Graf graf;
    int ktore;

    for (;;)
    {
        cout << endl << endl;
        cout << "Menu Minimalnego Drzewa Rozpinajacego:" << endl;
        cout << "Wybierz akcje:" << endl;
        cout << "1. Zbuduj z pliku" << endl;
        cout << "2. Wygeneruj losowy graf" << endl;
        cout << "3. Wyswietl" << endl;
        cout << "4. Algorytm Prima" << endl;
        cout << "5. Algorytm Kruskala" << endl;
        cout << "6. Powrot do menu glownego" << endl;
        cin >> ktore;

        if (ktore == 1)
        {
            string nazwa;
            cout << "Podaj nazwe pliku: ";
            cin >> nazwa;
            system("cls");
            string pelna_nazwa = "pliki_wejsciowe/" + nazwa + ".txt";
            fstream plik;
            plik.open(pelna_nazwa, ios::in);
            if (plik.is_open())
            {
                int ile_w, ile_k;
                plik >> ile_k;
                plik >> ile_w;
                graf.stworz(ile_w, ile_k);

                for (int i = 0; i < ile_k; i++)
                {
                    plik >> graf.krawedzie_lista[i].wpoczatek;
                    plik >> graf.krawedzie_lista[i].wkoniec;
                    plik >> graf.krawedzie_lista[i].waga;
                    graf.macierz_sasiedztwa[graf.krawedzie_lista[i].wpoczatek][graf.krawedzie_lista[i].wkoniec] = graf.krawedzie_lista[i].waga;
                    graf.macierz_sasiedztwa[graf.krawedzie_lista[i].wkoniec][graf.krawedzie_lista[i].wpoczatek] = graf.krawedzie_lista[i].waga;
                }
                graf.stworzListe();
                cout << "Czas trwania operacji wyniosl " << czas.czasTrwania() << " ms." << endl;
            }
            else
            {
                cout << "Nie udalo sie otworzyc pliku " << pelna_nazwa << endl;
            }
            plik.close();

            graf.wyswietlMacierz();
            cout << endl;
            graf.wyswietlListe();
        }
        if (ktore == 2)
        {
            int n, gestosc;
            cout << "Podaj liczbe wierzcholkow: ";
            cin >> n;
            cout << "Podaj gestosc: ";
            cin >> gestosc;
            system("cls");
            czas.Start();
            if ((0.01 * gestosc * n * (n - 1)) / 2 >= n - 1)
                graf.stworz(n, (0.01 * gestosc * n * (n - 1)) / 2);
            else
                graf.stworz(n, n - 1);
            graf.losuj(true);
            czas.Stop();
            cout << "Czas trwania operacji wyniosl " << czas.czasTrwania() << " ms." << endl;
            cout << "Gotowe" << endl;
        }
        if (ktore == 3)
        {
            system("cls");
            czas.Start();
            if (graf.l_wierzcholkow < 100 && graf.l_wierzcholkow>0)
            {
                graf.wyswietlListe();
                cout << endl;
                graf.wyswietlMacierz();
            }

            else cout << "cos nie dziala" << endl;
            czas.Stop();
            cout << "Czas trwania operacji wyniosl " << czas.czasTrwania() << " ms." << endl;
            cout << "Gotowe" << endl;
        }
        if (ktore == 4)
        {
            system("cls");
            cout << "znajdowanie MST algorytmem Prima" << endl;
            czas.Start();
            graf.MSTPrimMacierz();
            czas.Stop();
            cout << "Czas trwania operacji wyniosl " << czas.czasTrwania() << " ms." << endl;
            czas.Start();
            graf.MSTPrimLista();
            czas.Stop();
            cout << "Czas trwania operacji wyniosl " << czas.czasTrwania() << " ms." << endl;
            cout << "Gotowe" << endl;
        }
        if (ktore == 5)
        {
            system("cls");
            cout << "znajdowanie MST algorytmem Kruskala" << endl;
            czas.Start();
            graf.MSTKruskalMacierz();
            czas.Stop();
            cout << "Czas trwania operacji wyniosl " << czas.czasTrwania() << " ms." << endl;
            czas.Start();
            graf.MSTKruskalLista();
            czas.Stop();
            cout << "Czas trwania operacji wyniosl " << czas.czasTrwania() << " ms." << endl;
            cout << "Gotowe" << endl;
        }
        if (ktore == 6)
        {
            system("cls");
            //cout<<"halo"<<endl;
            //graf.czysc();
            return;
        }
    }
}

void Testowanie::testowanieSciezki()
{
    Czas czas;
    Graf graf;
    int ktore;

    for (;;)
    {
        cout << endl << endl;
        cout << "Menu znajdowania najkrotszej sciezki:" << endl;
        cout << "Wybierz akcje:" << endl;
        cout << "1. Zbuduj z pliku" << endl;
        cout << "2. Wygeneruj losowy graf" << endl;
        cout << "3. Wyswietl" << endl;
        cout << "4. Algorytm Dijkstry" << endl;
        cout << "5. Algorytm Bellmana-Forda" << endl;
        cout << "6. Powrot do menu glownego" << endl;
        cin >> ktore;

        if (ktore == 1)
        {
            string nazwa;
            cout << "Podaj nazwe pliku: ";
            cin >> nazwa;
            system("cls");
            string pelna_nazwa = "pliki_wejsciowe/" + nazwa + ".txt";
            fstream plik;
            plik.open(pelna_nazwa, ios::in);
            if (plik.is_open())
            {
                int ile_w, ile_k;
                plik >> ile_k;
                plik >> ile_w;
                plik >> graf.wierzcholek_poczatkowy;
                graf.stworz(ile_w, ile_k);

                for (int i = 0; i < ile_k; i++)
                {
                    plik >> graf.krawedzie_lista[i].wpoczatek;
                    plik >> graf.krawedzie_lista[i].wkoniec;
                    plik >> graf.krawedzie_lista[i].waga;
                    graf.macierz_sasiedztwa[graf.krawedzie_lista[i].wpoczatek][graf.krawedzie_lista[i].wkoniec] = graf.krawedzie_lista[i].waga;
                }
                graf.stworzListe();
                cout << "Czas trwania operacji wyniosl " << czas.czasTrwania() << " ms." << endl;
            }
            else
            {
                cout << "Nie udalo sie otworzyc pliku " << pelna_nazwa << endl;
            }
            plik.close();

            graf.wyswietlMacierz();
            cout << endl;
            graf.wyswietlListe();
        }
        if (ktore == 2)
        {
            int n, gestosc;
            cout << "Podaj liczbe wierzcholkow: ";
            cin >> n;
            cout << "Podaj gestosc: ";
            cin >> gestosc;
            system("cls");
            czas.Start();
            if ((0.01 * gestosc * n * (n - 1)) / 2 >= n - 1)
                graf.stworz(n, (0.01 * gestosc * n * (n - 1)) / 2);
            else
                graf.stworz(n, n - 1);
            graf.losuj(true);
            graf.wierzcholek_poczatkowy = rand() % n;
            czas.Stop();
            cout << "Czas trwania operacji wyniosl " << czas.czasTrwania() << " ms." << endl;
            cout << "Gotowe" << endl;
        }
        if (ktore == 3)
        {
            system("cls");
            czas.Start();
            if (graf.l_wierzcholkow < 100 && graf.l_wierzcholkow>0)
            {
                graf.wyswietlListe();
                cout << endl;
                graf.wyswietlMacierz();
            }

            else cout << "cos nie dziala" << endl;
            czas.Stop();
            cout << "Czas trwania operacji wyniosl " << czas.czasTrwania() << " ms." << endl;
            cout << "Gotowe" << endl;
        }
        if (ktore == 4)
        {
            system("cls");
            cout << "znajdowanie najkrotszych sciezek algorytmem Dijkstry" << endl;
            czas.Start();
            graf.SciezkaDijkstryMacierz();
            czas.Stop();
            cout << "Czas trwania operacji wyniosl " << czas.czasTrwania() << " ms." << endl;
            czas.Start();
            graf.SciezkaDijkstryLista();
            czas.Stop();
            cout << "Czas trwania operacji wyniosl " << czas.czasTrwania() << " ms." << endl;
            cout << "Gotowe" << endl;
        }
        if (ktore == 5)
        {
            system("cls");
            cout << "znajdowanie najkrotszych sciezek algorytmem Bellmana-Forda" << endl;
            czas.Start();
            graf.SciezkaBellmanMacierz();
            czas.Stop();
            cout << "Czas trwania operacji wyniosl " << czas.czasTrwania() << " ms." << endl;
            czas.Start();
            graf.SciezkaBellmanLista();
            czas.Stop();
            cout << "Czas trwania operacji wyniosl " << czas.czasTrwania() << " ms." << endl;
            cout << "Gotowe" << endl;
        }
        if (ktore == 6)
        {
            system("cls");
            //cout<<"halo"<<endl;
            //graf.czysc();
            return;
        }
        /*
        if(ktore==7)
        {
            cout<<"Podaj szukana wartosc: ";
            cin>>wartosc;
            bool czy;
            system("cls");
            czas.Start();
            czy=tablica.tCzyIstnieje(wartosc);
            czas.Stop();
            if(czy) cout<<"Podana wartosc jest w tablicy"<<endl;
            else cout<<"Nie znaleziono podanej wartosci"<<endl;
            cout<<"Czas trwania operacji wyniosl "<<czas.czasTrwania()<<" ms."<<endl;
            tablica.tWyswietl();
        }
        if(ktore==5)
        {
            int ile;
            cout<<"Ile danych wylosowac? "<<endl;
            cin>>ile;
            system("cls");
            //tablica.~Tablica();
            //Tablica tablica;
            czas.Start();
            for(int i=0; i<ile; i++)
            {
                wartosc=rand()%20000-10000;
                tablica.tDodajElement(i, wartosc);
            }
            czas.Stop();
            tablica.tWyswietl();
            cout<<"Czas trwania operacji wyniosl "<<czas.czasTrwania()<<" ms."<<endl;
        }
        if(ktore==6)
        {
            system("cls");
            tablica.tWyswietl();
        }
        if(ktore==7)
        {
            system("cls");
            //tablica.~Tablica();
            return;
        }*/
    }
}

void Testowanie::testowaniePrzeplywu()
{
    /*
    Czas czas;
    Kopiec kopiec;
    int ktore, index, wartosc;

    for(;;)
    {
        cout<<endl<<endl;
        cout<<"Menu operacji na kopcu:"<<endl;
        cout<<"Wybierz akcje:"<<endl;
        cout<<"1. Zbuduj z pliku"<<endl;
        cout<<"2. Dodaj wartosc"<<endl;
        cout<<"3. Usun wartosc"<<endl;
        cout<<"4. Wyszukaj wartosc"<<endl;
        cout<<"5. Wypelnij losowymi danymi"<<endl;
        cout<<"6. Wyswietl kopiec"<<endl;
        cout<<"7. Powrot do menu glownego"<<endl;
        cin>>ktore;
        if(ktore==1)
        {
            string nazwa;
            cout<<"Podaj nazwe pliku: ";
            cin>>nazwa;
            system("cls");
            string pelna_nazwa="pliki_wejsciowe/"+nazwa+".txt";
            fstream plik;
            plik.open( pelna_nazwa, ios::in );
            if (plik.is_open())
            {
                //kopiec.~Kopiec();
                //Kopiec kopiec;
                int ile;
                string dana;
                getline(plik,dana);
                ile = stoi(dana);
                czas.Start();
                for(int i=0; i<ile; i++)
                {
                    getline(plik,dana);
                    kopiec.kDodajElement(stoi(dana));
                }
                czas.Stop();
                kopiec.kWyswietl();
                cout<<"Czas trwania operacji wyniosl "<<czas.czasTrwania()<<" ms."<<endl;
            }
            else
            {
                cout<<"Nie udalo sie otworzyc pliku "<<pelna_nazwa<<endl;
            }
            plik.close();

        }
        if(ktore==2)
        {
            cout<<"Podaj wartosc: ";
            cin>>wartosc;
            system("cls");
            czas.Start();
            kopiec.kDodajElement(wartosc);
            czas.Stop();
            cout<<"Czas trwania operacji wyniosl "<<czas.czasTrwania()<<" ms."<<endl;
            cout<<"Gotowe"<<endl;
            kopiec.kWyswietl();
        }
        if(ktore==3)
        {
            cout<<"Podaj index: ";
            cin>>index;
            system("cls");
            czas.Start();
            kopiec.kUsunElement(index);
            czas.Stop();
            cout<<"Czas trwania operacji wyniosl "<<czas.czasTrwania()<<" ms."<<endl;
            cout<<"Gotowe"<<endl;
            kopiec.kWyswietl();
        }
        if(ktore==4)
        {
            cout<<"Podaj szukana wartosc: ";
            cin>>wartosc;
            bool czy;
            system("cls");
            czas.Start();
            czy=kopiec.kCzyIstnieje(wartosc);
            czas.Stop();
            if(czy) cout<<"Podana wartosc jest w kopcu"<<endl;
            else cout<<"Nie znaleziono podanej wartosci"<<endl;
            cout<<"Czas trwania operacji wyniosl "<<czas.czasTrwania()<<" ms."<<endl;
            kopiec.kWyswietl();
        }
        if(ktore==5)
        {
            int ile;
            cout<<"Ile danych wylosowac? "<<endl;
            cin>>ile;
            system("cls");
            //kopiec.~Kopiec();
            //Kopiec kopiec;
            czas.Start();
            for(int i=0; i<ile; i++)
            {
                wartosc=rand()%20000-10000;
                kopiec.kDodajElement(wartosc);
            }
            czas.Stop();
            kopiec.kWyswietl();
            cout<<"Czas trwania operacji wyniosl "<<czas.czasTrwania()<<" ms."<<endl;
        }
        if(ktore==6)
        {
            system("cls");
            kopiec.kWyswietl();
        }
        if(ktore==7)
        {
            system("cls");
            kopiec.~Kopiec();
            return;
        }
    }*/
}

