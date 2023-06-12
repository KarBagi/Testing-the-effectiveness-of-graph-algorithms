#include <iostream>
#include <fstream>
#include <windows.h>
#include <string>
#include <time.h>
#include "testowanieautomatyczne.h"
#include "graf.h"

using namespace std;

void TestowanieAutomatyczne::testowanie()
{
    srand(time(NULL));

    //testowanieMSTPrimLista(1000);
    //testowanieMSTPrimLista(1500);
    //testowanieMSTPrimLista(2000);
    //testowanieMSTPrimLista(2500);
    //testowanieMSTPrimLista(3000);
    //testowanieMSTPrimLista(3500);
    //testowanieMSTPrimLista(4000);
    //testowanieMSTPrimMacierz(1000);
    //testowanieMSTPrimMacierz(1500);
    //testowanieMSTPrimMacierz(2000);
    //testowanieMSTPrimMacierz(2500);
    //testowanieMSTPrimMacierz(3000);
    //testowanieMSTPrimMacierz(3500);
    //testowanieMSTPrimMacierz(4000);
    //testowanieMSTKruskalMacierz(1000);
    //testowanieMSTKruskalMacierz(1500);
    //testowanieMSTKruskalMacierz(2000);
    //testowanieMSTKruskalMacierz(2500);
    //testowanieMSTKruskalMacierz(3000);
    //testowanieMSTKruskalMacierz(3500);
    //testowanieMSTKruskalMacierz(4000);
    //testowanieMSTKruskalLista(1000);
    //testowanieMSTKruskalLista(1500);
    //testowanieMSTKruskalLista(2000);
    //testowanieMSTKruskalLista(2500);
    testowanieMSTKruskalLista(3000);
    testowanieMSTKruskalLista(3500);
    testowanieMSTKruskalLista(4000);


}

void TestowanieAutomatyczne::testowanieMSTPrimMacierz(int n)
{
    Czas czas;
    Graf graf[155];
    int wartosc;
    fstream plikwyjsciowy;
    string nazwa;
    nazwa += "pliki_wyjsciowe/MSTPRIM" + to_string(n) + "MACIERZ.txt";

    plikwyjsciowy.open(nazwa, ios::in | ios::out);

    if (plikwyjsciowy.good()) cout << "jest dobrze" << endl;
    plikwyjsciowy << "glebokosc 20%" << endl;
    for (int j = 0; j < 50; j++)
    {
        graf[j].stworz(n, 20);
        graf[j].losuj(true);
    }

    for (int j = 0; j < 50; j++)
    {
        czas.Start();
        graf[j].MSTPrimMacierz();
        czas.Stop();
        plikwyjsciowy << czas.czasTrwania() << endl;
    }
    plikwyjsciowy << "glebokosc 50%" << endl;
    for (int j = 50; j < 100; j++)
    {
        graf[j].stworz(n, 50);
        graf[j].losuj(true);
    }

    for (int j = 50; j < 100; j++)
    {
        czas.Start();
        graf[j].MSTPrimMacierz();
        czas.Stop();
        plikwyjsciowy << czas.czasTrwania() << endl;
    }
    plikwyjsciowy << "glebokosc 99%" << endl;
    for (int j = 100; j < 150; j++)
    {
        graf[j].stworz(n, 99);
        graf[j].losuj(true);
    }

    for (int j = 100; j < 150; j++)
    {
        czas.Start();
        graf[j].MSTPrimMacierz();
        czas.Stop();
        plikwyjsciowy << czas.czasTrwania() << endl;
    }

    plikwyjsciowy.close();

}

void TestowanieAutomatyczne::testowanieMSTPrimLista(int n)
{
    Czas czas;
    Graf graf[155];
    int wartosc;
    fstream plikwyjsciowy;
    string nazwa;
    nazwa += "pliki_wyjsciowe/MSTPRIM" + to_string(n) + "LISTA.txt";
    plikwyjsciowy.open(nazwa, ios::in | ios::out);

    if (plikwyjsciowy.good()) cout << "jest dobrze" << endl;
    plikwyjsciowy << "glebokosc 20%" << endl;
    for (int j = 0; j < 50; j++)
    {
        graf[j].stworz(n, 20);
        graf[j].losuj(true);
    }

    for (int j = 0; j < 50; j++)
    {
        czas.Start();
        graf[j].MSTPrimLista();
        czas.Stop();
        plikwyjsciowy << czas.czasTrwania() << endl;
    }
    plikwyjsciowy << "glebokosc 50%" << endl;
    for (int j = 50; j < 100; j++)
    {
        graf[j].stworz(n, 50);
        graf[j].losuj(true);
    }

    for (int j = 50; j < 100; j++)
    {
        czas.Start();
        graf[j].MSTPrimLista();
        czas.Stop();
        plikwyjsciowy << czas.czasTrwania() << endl;
    }
    plikwyjsciowy << "glebokosc 99%" << endl;
    for (int j = 100; j < 150; j++)
    {
        graf[j].stworz(n, 99);
        graf[j].losuj(true);
    }

    for (int j = 100; j < 150; j++)
    {
        czas.Start();
        graf[j].MSTPrimLista();
        czas.Stop();
        plikwyjsciowy << czas.czasTrwania() << endl;
    }

    plikwyjsciowy.close();

}

void TestowanieAutomatyczne::testowanieMSTKruskalMacierz(int n)
{
    Czas czas;
    Graf graf[155];
    int wartosc;
    fstream plikwyjsciowy;
    string nazwa;
    nazwa += "pliki_wyjsciowe/MSTKRUSKAL" + to_string(n) + "MACIERZ.txt";
    plikwyjsciowy.open(nazwa, ios::in | ios::out);

    if (plikwyjsciowy.good()) cout << "jest dobrze" << endl;
    plikwyjsciowy << "glebokosc 20%" << endl;
    for (int j = 0; j < 50; j++)
    {
        graf[j].stworz(n, 20);
        graf[j].losuj(true);
    }

    for (int j = 0; j < 50; j++)
    {
        czas.Start();
        graf[j].MSTKruskalMacierz();
        czas.Stop();
        plikwyjsciowy << czas.czasTrwania() << endl;
    }
    plikwyjsciowy << "glebokosc 50%" << endl;
    for (int j = 50; j < 100; j++)
    {
        graf[j].stworz(n, 50);
        graf[j].losuj(true);
    }

    for (int j = 50; j < 100; j++)
    {
        czas.Start();
        graf[j].MSTKruskalMacierz();
        czas.Stop();
        plikwyjsciowy << czas.czasTrwania() << endl;
    }
    plikwyjsciowy << "glebokosc 99%" << endl;
    for (int j = 100; j < 150; j++)
    {
        graf[j].stworz(n, 99);
        graf[j].losuj(true);
    }

    for (int j = 100; j < 150; j++)
    {
        czas.Start();
        graf[j].MSTKruskalMacierz();
        czas.Stop();
        plikwyjsciowy << czas.czasTrwania() << endl;
    }

    plikwyjsciowy.close();
}

void TestowanieAutomatyczne::testowanieMSTKruskalLista(int n)
{
    Czas czas;
    Graf graf[155];
    int wartosc;
    fstream plikwyjsciowy;
    string nazwa;
    nazwa += "pliki_wyjsciowe/MSTKRUSKAL" + to_string(n) + "LISTA.txt";
    plikwyjsciowy.open(nazwa, ios::in | ios::out);

    if (plikwyjsciowy.good()) cout << "jest dobrze" << endl;
    plikwyjsciowy << "glebokosc 20%" << endl;
    for (int j = 0; j < 50; j++)
    {
        graf[j].stworz(n, 20);
        graf[j].losuj(true);
    }

    for (int j = 0; j < 50; j++)
    {
        czas.Start();
        graf[j].MSTKruskalLista();
        czas.Stop();
        plikwyjsciowy << czas.czasTrwania() << endl;
    }
    plikwyjsciowy << "glebokosc 50%" << endl;
    for (int j = 50; j < 100; j++)
    {
        graf[j].stworz(n, 50);
        graf[j].losuj(true);
    }

    for (int j = 50; j < 100; j++)
    {
        czas.Start();
        graf[j].MSTKruskalLista();
        czas.Stop();
        plikwyjsciowy << czas.czasTrwania() << endl;
    }
    plikwyjsciowy << "glebokosc 99%" << endl;
    for (int j = 100; j < 150; j++)
    {
        graf[j].stworz(n, 99);
        graf[j].losuj(true);
    }

    for (int j = 100; j < 150; j++)
    {
        czas.Start();
        graf[j].MSTKruskalLista();
        czas.Stop();
        plikwyjsciowy << czas.czasTrwania() << endl;
    }

    plikwyjsciowy.close();
}

