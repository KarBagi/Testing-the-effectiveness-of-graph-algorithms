#include<iostream>
#include"wierzcholek.h"
#include"krawedz.h"

#ifndef GRAF_H
#define GRAF_H

using namespace std;

class Graf
{
public:
    void stworz(int l_w, int l_k);
    void stworzListe();

    int l_wierzcholkow, l_krawedzi, gestosc, ile_krawedzi = 0, ile_wierzcholkow = 0, ** macierz_sasiedztwa, ** lista_sasiedztwa, w_poczatek, w_koniec;
    int wierzcholek_poczatkowy;

    Krawedz* krawedzie_lista;
    int* ID_wierzcholkow;

    void wyswietlListe();
    void wyswietlMacierz();

    void MSTPrimMacierz();
    int przepatrzSasiadow(int w, int a);
    Krawedz* kolejka_krawedzi;
    Krawedz* krawedzie_gotoweP;
    Krawedz* krawedzie_gotowePLista;
    void MSTPrimLista();
    int przepatrzSasiadowLista(int w, int a);

    void MSTKruskalMacierz();
    void przepatrzSasiadowKruskalMacierz(int w, int z, int na);
    void przepatrzSasiadowKruskalLista(int w, int z, int na);
    void MSTKruskalLista();
    void przepatrzKrawedzieMacierz();
    void przepatrzKrawedzieLista();
    Krawedz* kolejka_krawedziPM;
    Krawedz* kolejka_krawedziPL;
    Krawedz* kolejka_krawedziKM;
    Krawedz* kolejka_krawedziKL;
    Krawedz* krawedzie_gotoweK;
    Krawedz* krawedzie_gotoweKLista;

    void SciezkaDijkstryMacierz();
    void SciezkaDijkstryLista();
    void SciezkaBellmanMacierz();
    void SciezkaBellmanLista();

    void wyswietlPoprzednika(int wierzcholek);

    void losuj(bool nieskierowany);

};

#endif
