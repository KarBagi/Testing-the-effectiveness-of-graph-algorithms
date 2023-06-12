#include "Graf.h"
#include "Czas.h"

using namespace std;

void Graf::stworz(int l_w, int l_k)
{
    if (l_k > l_w - 1)
        l_krawedzi = l_k;
    else
        l_krawedzi = l_w - 1;
    l_wierzcholkow = l_w;

    krawedzie_lista = new Krawedz[l_krawedzi];

    ID_wierzcholkow = new int[l_wierzcholkow];
    for (int i = 0; i < l_wierzcholkow; i++)
        ID_wierzcholkow[i] = i;

    macierz_sasiedztwa = new int* [l_wierzcholkow];
    lista_sasiedztwa = new int* [l_wierzcholkow];

    for (int i = 0; i < l_wierzcholkow; i++)
    {
        macierz_sasiedztwa[i] = new int[l_wierzcholkow];
        for (int j = 0; j < l_wierzcholkow; j++)
        {
            macierz_sasiedztwa[i][j] = 0;
        }
    }

    kolejka_krawedziPM = new Krawedz[l_krawedzi];
    kolejka_krawedziPL = new Krawedz[l_krawedzi];
    kolejka_krawedziKM = new Krawedz[l_krawedzi];
    kolejka_krawedziKL = new Krawedz[l_krawedzi];
    krawedzie_gotoweP = new Krawedz[l_wierzcholkow - 1];
    krawedzie_gotoweK = new Krawedz[l_wierzcholkow - 1];
    krawedzie_gotowePLista = new Krawedz[l_wierzcholkow - 1];
    krawedzie_gotoweKLista = new Krawedz[l_wierzcholkow - 1];
}

void Graf::stworzListe()
{
    int ile_sasiadow, a;
    for (int i = 0; i < l_wierzcholkow; i++)
    {
        ile_sasiadow = 0;
        a = 1;

        for (int j = 0; j < l_wierzcholkow; j++)     //zliczam szerokosc listy sasiadow dla danego wierzcholka
        {
            if (macierz_sasiedztwa[i][j] != 0) ile_sasiadow++;
        }


        lista_sasiedztwa[i] = new int[ile_sasiadow * 2 + 1];     //x sasiadow * 2 (wierzcholek koncowy + waga) + jedno miejsce na wierzcholek poczatkowy
        lista_sasiedztwa[i][0] = ile_sasiadow;
        //cout<<lista_sasiedztwa[i][0]<<" sasiadow"<<endl;

        for (int j = 0; j < l_wierzcholkow; j++)
        {
            if (macierz_sasiedztwa[i][j] != 0)     //wypelniam i-ty wiersz listy sasiadow
            {
                lista_sasiedztwa[i][a] = j;
                lista_sasiedztwa[i][a + 1] = macierz_sasiedztwa[i][j];
                a += 2;
            }
        }

    }
}

void Graf::losuj(bool nieskierowany)
{
    int ile_krawedzi = l_krawedzi;
    int w, u;
    int* odwiedzone;
    odwiedzone = new int[l_wierzcholkow];

    for (int i = 0; i < l_wierzcholkow; i++)
        odwiedzone[i] = false;

    u = rand() % l_wierzcholkow;
    odwiedzone[u] = true;
    for (int i = 0; i < l_wierzcholkow - 1;)
    {
        w = rand() % l_wierzcholkow;
        if (odwiedzone[w] == false)
        {
            odwiedzone[w] = true;
            macierz_sasiedztwa[u][w] = rand() % 20 + 1;
            krawedzie_lista[i].wpoczatek = u;
            krawedzie_lista[i].wkoniec = w;
            krawedzie_lista[i].waga = macierz_sasiedztwa[u][w];
            if (nieskierowany) macierz_sasiedztwa[w][u] = macierz_sasiedztwa[u][w];
            i++;
            ile_krawedzi--;
            u = w;
        }
    }

    if (ile_krawedzi > 0)
    {
        cout << "wiecej krawedzi" << endl;
        for (int i = 0; i < ile_krawedzi;)
        {
            u = rand() % l_wierzcholkow;
            w = rand() % l_wierzcholkow;

            if (macierz_sasiedztwa[w][u] == 0 && w != u)
            {
                macierz_sasiedztwa[w][u] = rand() % 20 + 1;
                if (nieskierowany) macierz_sasiedztwa[u][w] = macierz_sasiedztwa[w][u];
                i++;
            }
        }
    }

    stworzListe();
    //wyswietlListe();
    //wyswietlMacierz();
}

void Graf::wyswietlListe()
{
    cout << "Lista sasiedztwa: " << endl;
    for (int i = 0; i < l_wierzcholkow; i++)
    {
        cout << i;

        for (int j = 1; j < lista_sasiedztwa[i][0] * 2; j += 2)
        {
            cout << " -> [" << lista_sasiedztwa[i][j] << "|" << lista_sasiedztwa[i][j + 1] << "] ";
        }
        cout << endl;
    }
}

void Graf::wyswietlMacierz()
{
    cout << "Macierz sasiedztwa: " << endl;
    for (int i = 0; i < l_wierzcholkow + 1; i++)
    {
        if (i > 0)cout << i - 1 << " |";
        for (int j = 0; j < l_wierzcholkow; j++)
        {
            if (i == 0)
            {
                if (j == 0)cout << "  ";
                cout << " " << j;
            }
            else
                cout << macierz_sasiedztwa[i - 1][j] << " ";
        }
        if (i == 0)
        {
            cout << endl;
            for (int j = 0; j < l_wierzcholkow * 2 + 2; j++) cout << "-";
        }

        cout << endl;
    }
}

int Graf::przepatrzSasiadow(int w, int a)
{
    ID_wierzcholkow[w] = 0;
    for (int i = 0; i < l_wierzcholkow; i++)
    {
        if (macierz_sasiedztwa[w][i] != 0 and ID_wierzcholkow[i] != 0)
        {
            kolejka_krawedziPM[a].wpoczatek = w;
            kolejka_krawedziPM[a].wkoniec = i;
            kolejka_krawedziPM[a].waga = macierz_sasiedztwa[w][i];
            //cout<<"dodaje do kolejki wage "<<kolejka_krawedziPM[a].waga<<endl;
            a++;
        }
    }
    return a;
}

void Graf::MSTPrimMacierz()
{
    cout<<"Macierz: "<<endl;
    for (int i = 0; i < l_krawedzi; i++)
    {
        krawedzie_lista[i].uzyta = false;
        krawedzie_lista[i].indeks = i;
        kolejka_krawedziPM[i].wpoczatek = krawedzie_lista[i].wpoczatek;
        kolejka_krawedziPM[i].wkoniec = krawedzie_lista[i].wkoniec;
        kolejka_krawedziPM[i].waga = krawedzie_lista[i].waga;
        kolejka_krawedziPM[i].uzyta = false;
    }

    for (int i = 0; i < l_wierzcholkow - 1; i++)
    {
        krawedzie_gotoweP[i].uzyta = false;
    }

    for (int i = 0; i < l_wierzcholkow; i++)
    {
        ID_wierzcholkow[i] = i;
    }

    int minn, wybrana, ktory_teraz = 0, suma = 0;
    int a = 0;
    int ile_juz = -1;
    bool koniec;


    while (ile_juz < l_wierzcholkow - 2)
    {
        //cout<<endl<<endl<<"patrze sasiadow "<<ktory_teraz<<endl;
        a = przepatrzSasiadow(ktory_teraz, a);
        /*cout<<"kolejka wyglada tak: "<<endl;
        for(int k=0;k<a;k++)
        {
            cout<<kolejka_krawedziPM[k].wpoczatek<<" -> "<<kolejka_krawedziPM[k].wkoniec<<": "<<kolejka_krawedziPM[k].waga<<", ID = "<<ID_wierzcholkow[kolejka_krawedziPM[k].wkoniec]<<endl;
        }*/
        koniec = false;
        for (int i = 0; i < a; i++)
        {
            while (!koniec)
            {
                //cout<<"krawedz o wadze "<<kolejka_krawedziPM[i].waga<<" jest uzyta: "<<kolejka_krawedziPM[i].uzyta<<", "<<ID_wierzcholkow[kolejka_krawedziPM[i].wkoniec]<<endl;
                if (kolejka_krawedziPM[i].uzyta == false and ID_wierzcholkow[kolejka_krawedziPM[i].wkoniec] != 0)
                {
                    //cout<<"wybieram pierwsza wolna wage: "<<kolejka_krawedziPM[i].waga<<endl;
                    minn = kolejka_krawedziPM[i].waga;
                    wybrana = i;
                    koniec = true;
                    i++;
                }
                else
                {
                    i++;
                }
            }
            //cout<<"teraz i wynosi: "<<i<<endl;
            if (i < a)
                if (kolejka_krawedziPM[i].uzyta == false and ID_wierzcholkow[kolejka_krawedziPM[i].wkoniec] != 0)
                {
                    //cout<<"sprawdzam "<<minn<<" i "<<kolejka_krawedziPM[i].waga<<endl;
                    if (kolejka_krawedziPM[i].waga < minn)
                    {
                        minn = kolejka_krawedziPM[i].waga;
                        wybrana = i;
                        //cout<<"nowa mniejsza waga"<<endl;
                    }
                    //else cout<<"stara waga zostaje najmniejsza"<<endl;

                }
        }
        //cout<<"najmniejsza dostepna waga: "<<kolejka_krawedziPM[wybrana].waga<<endl;

        kolejka_krawedziPM[wybrana].uzyta = true;
        krawedzie_gotoweP[ile_juz + 1].wpoczatek = kolejka_krawedziPM[wybrana].wpoczatek;
        krawedzie_gotoweP[ile_juz + 1].wkoniec = kolejka_krawedziPM[wybrana].wkoniec;
        krawedzie_gotoweP[ile_juz + 1].waga = kolejka_krawedziPM[wybrana].waga;
        //cout<<"suma wynosi "<<suma<<" i po dodaniu "<<kolejka_krawedziPM[wybrana].waga;
        suma += krawedzie_gotoweP[ile_juz + 1].waga;
        //cout<<" wynosi "<<suma<<endl;
        //cout<<"wybralismy krawedz ktora konczy sie w "<<ID_wierzcholkow[kolejka_krawedziPM[wybrana].wkoniec]<<endl;
        ID_wierzcholkow[kolejka_krawedziPM[wybrana].wkoniec] = 0;
        ktory_teraz = kolejka_krawedziPM[wybrana].wkoniec;
        ile_juz++;
    }

    for(int i=0; i<l_wierzcholkow-1; i++)
    {
        cout<<krawedzie_gotoweP[i].wpoczatek<<" -> "<<krawedzie_gotoweP[i].wkoniec<<": "<<krawedzie_gotoweP[i].waga<<endl;
    }
    cout<<"suma: "<<suma<<endl;
}

void Graf::MSTPrimLista()
{
    cout<<"Lista: "<<endl;



    for (int i = 0; i < l_krawedzi; i++)
    {
        krawedzie_lista[i].uzyta = false;
        krawedzie_lista[i].indeks = i;
        kolejka_krawedziPL[i].wpoczatek = krawedzie_lista[i].wpoczatek;
        kolejka_krawedziPL[i].wkoniec = krawedzie_lista[i].wkoniec;
        kolejka_krawedziPL[i].waga = krawedzie_lista[i].waga;
        kolejka_krawedziPL[i].uzyta = false;
    }

    for (int i = 0; i < l_wierzcholkow - 1; i++)
    {
        krawedzie_gotowePLista[i].uzyta = false;
    }

    for (int i = 0; i < l_wierzcholkow; i++)
    {
        ID_wierzcholkow[i] = i;
    }

    int minn, wybrana, ktory_teraz = 0, suma = 0;;
    int a = 0;
    int ile_juz = -1;
    bool koniec;

    while (ile_juz < l_wierzcholkow - 2)
    {
        //cout<<endl<<endl<<"patrze sasiadow "<<ktory_teraz<<endl;
        a = przepatrzSasiadowLista(ktory_teraz, a);
        /*cout<<"kolejka wyglada tak: "<<endl;
        for(int k=0;k<a;k++)
        {
            cout<<kolejka_krawedzi[k].wpoczatek<<" -> "<<kolejka_krawedzi[k].wkoniec<<": "<<kolejka_krawedzi[k].waga<<endl;
        }*/
        koniec = false;
        for (int i = 0; i < a; i++)
        {
            while (!koniec)
            {
                //cout<<"krawedz o wadze "<<kolejka_krawedzi[i].waga<<" jest uzyta: "<<kolejka_krawedzi[i].uzyta<<endl;
                if (kolejka_krawedziPL[i].uzyta == false and ID_wierzcholkow[kolejka_krawedziPL[i].wkoniec] != 0)
                {
                    //cout<<"wybieram pierwsza wolna wage: "<<kolejka_krawedzi[i].waga<<endl;
                    minn = kolejka_krawedziPL[i].waga;
                    wybrana = i;
                    koniec = true;
                    i++;
                }
                else
                {
                    i++;
                }
            }

            if (i < a)
                if (kolejka_krawedziPL[i].uzyta == false and ID_wierzcholkow[kolejka_krawedziPL[i].wkoniec] != 0)
                {
                    //cout<<"sprawdzam "<<minn<<" i "<<kolejka_krawedzi[i].waga<<endl;
                    if (kolejka_krawedziPL[i].waga < minn)
                    {
                        minn = kolejka_krawedziPL[i].waga;
                        wybrana = i;
                        //cout<<"nowa mniejsza waga"<<endl;
                    }
                    //else cout<<"stara waga zostaje najmniejsza"<<endl;

                }
        }
        //cout<<"najmniejsza dostepna waga: "<<kolejka_krawedzi[wybrana].waga<<endl;

        kolejka_krawedziPL[wybrana].uzyta = true;
        krawedzie_gotowePLista[ile_juz + 1].wpoczatek = kolejka_krawedziPL[wybrana].wpoczatek;
        krawedzie_gotowePLista[ile_juz + 1].wkoniec = kolejka_krawedziPL[wybrana].wkoniec;
        krawedzie_gotowePLista[ile_juz + 1].waga = kolejka_krawedziPL[wybrana].waga;
        //cout<<"suma wynosi "<<suma<<" i po dodaniu "<<kolejka_krawedzi[wybrana].waga;
        suma += krawedzie_gotowePLista[ile_juz + 1].waga;
        //cout<<" wynosi "<<suma<<endl;
        ID_wierzcholkow[kolejka_krawedziPL[wybrana].wkoniec] = 0;
        ktory_teraz = kolejka_krawedziPL[wybrana].wkoniec;
        ile_juz++;
    }

    for(int i=0; i<l_wierzcholkow-1; i++)
    {
        cout<<krawedzie_gotowePLista[i].wpoczatek<<" -> "<<krawedzie_gotowePLista[i].wkoniec<<": "<<krawedzie_gotowePLista[i].waga<<endl;
    }
    cout<<"suma: "<<suma<<endl;
}

void Graf::przepatrzSasiadowKruskalMacierz(int w, int z, int na)
{
    //cout<<"przegladam sasiadow"<<endl;
    for (int j = 0; j < l_wierzcholkow; j++)
    {
        if (macierz_sasiedztwa[w][j] != 0 and ID_wierzcholkow[j] == z and j != w)
        {
            //cout<<"zamieniam sasiada ID "<<ID_wierzcholkow[w]<<" z "<<z<<" na "<<na<<endl;
            ID_wierzcholkow[j] = na;

            przepatrzSasiadowKruskalMacierz(j, z, na);
        }

    }
}

void Graf::przepatrzSasiadowKruskalLista(int w, int z, int na)
{
    //cout<<"przegladam sasiadow"<<endl;
    for (int j = 1; j < lista_sasiedztwa[w][0] * 2; j += 2)
    {
        //cout<<lista_sasiedztwa[w][0]<<endl;
        //cout<<ID_wierzcholkow[lista_sasiedztwa[w][j]]<<endl;
        if (ID_wierzcholkow[lista_sasiedztwa[w][j]] == z)
        {
            //cout<<"zamieniam s¹siada ID "<<ID_wierzcholkow[w]<<" z "<<z<<" na "<<na<<endl;
            ID_wierzcholkow[lista_sasiedztwa[w][j]] = na;
            if (z != na)
                przepatrzSasiadowKruskalLista(lista_sasiedztwa[w][j], z, na);
        }

    }
}

int Graf::przepatrzSasiadowLista(int w, int a)
{
    ID_wierzcholkow[w] = 0;

    for (int i = 1; i < lista_sasiedztwa[w][0] * 2; i += 2)
    {
        //cout<<"wierzcholek "<<w<<" -> "<<lista_sasiedztwa[w][i]<<" = "<<lista_sasiedztwa[w][i+1]<<endl;
        if (ID_wierzcholkow[lista_sasiedztwa[w][i]] != 0)
        {
            kolejka_krawedziPL[a].wpoczatek = w;
            kolejka_krawedziPL[a].wkoniec = lista_sasiedztwa[w][i];
            kolejka_krawedziPL[a].waga = lista_sasiedztwa[w][i + 1];
            //cout<<"dodaje do kolejki wage "<<kolejka_krawedzi[a].waga<<endl;
            a++;
        }
    }
    return a;
}

void Graf::przepatrzKrawedzieMacierz()
{
    //cout<<"tworzenie kolejki wszystkich krawedzi"<<endl;
    int a = 0;
    for (int i = 0; i < l_wierzcholkow; i++)
    {
        for (int j = i; j < l_wierzcholkow; j++)
        {
            //cout<<i;
            if (macierz_sasiedztwa[i][j] != 0)
            {
                kolejka_krawedziKM[a].wpoczatek = i;
                kolejka_krawedziKM[a].wkoniec = j;
                kolejka_krawedziKM[a].waga = macierz_sasiedztwa[i][j];
                kolejka_krawedziKM[a].uzyta = false;
                //cout<<"dodaje do kolejki wage "<<kolejka_krawedziKM[a].waga<<endl;
                a++;
            }
        }
    }
}

void Graf::przepatrzKrawedzieLista()
{
    int a = 0;
    for (int w = 0; w < l_wierzcholkow; w++)
    {
        for (int i = 1; i < lista_sasiedztwa[w][0] * 2; i += 2)
        {
            //cout<<"wierzcholek "<<w<<" -> "<<lista_sasiedztwa[w][i]<<" = "<<lista_sasiedztwa[w][i+1]<<endl;
            if (w < lista_sasiedztwa[w][i])
            {
                kolejka_krawedziKL[a].wpoczatek = w;
                kolejka_krawedziKL[a].wkoniec = lista_sasiedztwa[w][i];
                kolejka_krawedziKL[a].waga = lista_sasiedztwa[w][i + 1];
                //cout<<"dodaje do kolejki wage "<<kolejka_krawedziKL[a].waga<<endl;
                a++;
            }
        }
    }


}

void Graf::MSTKruskalMacierz()
{
    przepatrzKrawedzieMacierz();
    cout << "Macierz: " << endl;
    for (int i = 0; i < l_krawedzi; i++)
    {
        krawedzie_lista[i].uzyta = false;
        krawedzie_lista[i].indeks = i;
    }

    for (int i = 0; i < l_wierzcholkow - 1; i++)
    {
        krawedzie_gotoweK[i].uzyta = false;
    }

    for (int i = 0; i < l_wierzcholkow; i++)
    {
        ID_wierzcholkow[i] = i;
    }

    int minn, wybrana, ktory_teraz = 0, suma = 0;;
    int ile_juz = -1;
    bool koniec;

    while (ile_juz < l_wierzcholkow - 2)
    {
        /*cout<<"kolejka wyglada tak: "<<endl;
        for(int k=0; k<l_krawedzi; k++)
        {
            cout<<kolejka_krawedziKM[k].wpoczatek<<" -> "<<kolejka_krawedziKM[k].wkoniec<<": "<<kolejka_krawedziKM[k].waga<<endl;
        }*/
        koniec = false;
        for (int i = 0; i < l_krawedzi; i++)
        {
            while (!koniec)
            {
                //cout<<"krawedz o wadze "<<kolejka_krawedziKM[i].waga<<" jest uzyta: "<<kolejka_krawedziKM[i].uzyta<<endl;
                if (kolejka_krawedziKM[i].uzyta == false and ID_wierzcholkow[kolejka_krawedziKM[i].wkoniec] != ID_wierzcholkow[kolejka_krawedziKM[i].wpoczatek])
                {
                    //cout<<"wybieram pierwsza wolna wage: "<<kolejka_krawedziKM[i].waga<<endl;
                    minn = kolejka_krawedziKM[i].waga;
                    wybrana = i;
                    koniec = true;
                    i++;
                }
                else
                {
                    i++;
                }
            }
            //if(i<=l_wierzcholkow-1)
            if (kolejka_krawedziKM[i].uzyta == false and ID_wierzcholkow[kolejka_krawedziKM[i].wkoniec] != ID_wierzcholkow[kolejka_krawedziKM[i].wpoczatek])
            {
                //cout<<"sprawdzam "<<minn<<" i "<<kolejka_krawedziKM[i].waga<<endl;
                if (kolejka_krawedziKM[i].waga < minn)
                {
                    minn = kolejka_krawedziKM[i].waga;
                    wybrana = i;
                    //cout<<"nowa mniejsza waga"<<endl;
                }
                //else cout<<"stara waga zostaje najmniejsza"<<endl;

            }
        }
        //cout<<"najmniejsza dostepna waga: "<<kolejka_krawedziKM[wybrana].wpoczatek<<" -> "<<kolejka_krawedziKM[wybrana].wkoniec<<" = "<<kolejka_krawedziKM[wybrana].waga<<endl;
        //cout<<ID_wierzcholkow[kolejka_krawedziKM[wybrana].wpoczatek]<<" "<<ID_wierzcholkow[kolejka_krawedziKM[wybrana].wkoniec]<<endl;
        kolejka_krawedziKM[wybrana].uzyta = true;

        if (ID_wierzcholkow[kolejka_krawedziKM[wybrana].wkoniec] > ID_wierzcholkow[kolejka_krawedziKM[wybrana].wpoczatek])
        {
            //cout<<"zamieniam z "<<ID_wierzcholkow[kolejka_krawedziKM[wybrana].wkoniec]<<" na "<<ID_wierzcholkow[kolejka_krawedziKM[wybrana].wpoczatek]<<endl;
            przepatrzSasiadowKruskalMacierz(kolejka_krawedziKM[wybrana].wkoniec, ID_wierzcholkow[kolejka_krawedziKM[wybrana].wkoniec], ID_wierzcholkow[kolejka_krawedziKM[wybrana].wpoczatek]);
            ID_wierzcholkow[kolejka_krawedziKM[wybrana].wkoniec] = ID_wierzcholkow[kolejka_krawedziKM[wybrana].wpoczatek];
        }
        else if (ID_wierzcholkow[kolejka_krawedziKM[wybrana].wkoniec] < ID_wierzcholkow[kolejka_krawedziKM[wybrana].wpoczatek])
        {
            //cout<<"zamieniam z "<<ID_wierzcholkow[kolejka_krawedziKM[wybrana].wpoczatek]<<" na "<<ID_wierzcholkow[kolejka_krawedziKM[wybrana].wkoniec]<<endl;
            przepatrzSasiadowKruskalMacierz(kolejka_krawedziKM[wybrana].wpoczatek, ID_wierzcholkow[kolejka_krawedziKM[wybrana].wpoczatek], ID_wierzcholkow[kolejka_krawedziKM[wybrana].wkoniec]);
            ID_wierzcholkow[kolejka_krawedziKM[wybrana].wpoczatek] = ID_wierzcholkow[kolejka_krawedziKM[wybrana].wkoniec];
        }
        //cout<<"halo"<<endl;
        krawedzie_gotoweK[ile_juz + 1].wpoczatek = kolejka_krawedziKM[wybrana].wpoczatek;
        krawedzie_gotoweK[ile_juz + 1].wkoniec = kolejka_krawedziKM[wybrana].wkoniec;
        krawedzie_gotoweK[ile_juz + 1].waga = kolejka_krawedziKM[wybrana].waga;
        //cout<<"suma wynosi "<<suma<<" i po dodaniu "<<kolejka_krawedziKM[wybrana].waga;
        suma += krawedzie_gotoweK[ile_juz + 1].waga;
        //cout<<" wynosi "<<suma<<endl;
        ile_juz++;
    }

    for (int i = 0; i < l_wierzcholkow - 1; i++)
    {
        cout << krawedzie_gotoweK[i].wpoczatek << " -> " << krawedzie_gotoweK[i].wkoniec << ": " << krawedzie_gotoweK[i].waga << endl;
    }
    cout << "suma: " << suma << endl;
}

void Graf::MSTKruskalLista()
{
    przepatrzKrawedzieLista();
    cout<<"Lista: "<<endl;
    for (int i = 0; i < l_krawedzi; i++)
    {
        krawedzie_lista[i].uzyta = false;
        krawedzie_lista[i].indeks = i;
        kolejka_krawedziKL[i].uzyta = false;
    }

    for (int i = 0; i < l_wierzcholkow - 1; i++)
    {
        krawedzie_gotoweKLista[i].uzyta = false;
    }

    for (int i = 0; i < l_wierzcholkow; i++)
    {
        ID_wierzcholkow[i] = i;
    }

    int minn, wybrana, ktory_teraz = 0, suma = 0;;
    int ile_juz = -1;
    bool koniec;

    while (ile_juz < l_wierzcholkow - 2)
    {
        /*cout<<"kolejka wyglada tak: "<<endl;
        for(int k=0; k<l_krawedzi; k++)
        {
            cout<<kolejka_krawedziKL[k].wpoczatek<<" -> "<<kolejka_krawedziKL[k].wkoniec<<": "<<kolejka_krawedziKL[k].waga<<endl;
        }*/
        koniec = false;
        for (int i = 0; i < l_krawedzi; i++)
        {
            while (!koniec)
            {
                //cout<<"krawedz o wadze "<<kolejka_krawedziKL[i].waga<<" jest uzyta: "<<kolejka_krawedziKL[i].uzyta<<endl;
                if (kolejka_krawedziKL[i].uzyta == false and ID_wierzcholkow[kolejka_krawedziKL[i].wkoniec] != ID_wierzcholkow[kolejka_krawedziKL[i].wpoczatek])
                {
                    //cout<<"wybieram pierwsza wolna wage: "<<kolejka_krawedziKL[i].waga<<endl;
                    minn = kolejka_krawedziKL[i].waga;
                    wybrana = i;
                    koniec = true;
                    i++;
                }
                else
                {
                    i++;
                }
            }
            //if(i<=l_wierzcholkow-1)
            if (kolejka_krawedziKL[i].uzyta == false and ID_wierzcholkow[kolejka_krawedziKL[i].wkoniec] != ID_wierzcholkow[kolejka_krawedziKL[i].wpoczatek])
            {
                //cout<<"sprawdzam "<<minn<<" i "<<kolejka_krawedziKL[i].waga<<endl;
                if (kolejka_krawedziKL[i].waga < minn)
                {
                    minn = kolejka_krawedziKL[i].waga;
                    wybrana = i;
                    //cout<<"nowa mniejsza waga"<<endl;
                }
                //else cout<<"stara waga zostaje najmniejsza"<<endl;

            }
        }
        //cout<<"najmniejsza dostepna waga: "<<kolejka_krawedziKL[wybrana].wpoczatek<<" -> "<<kolejka_krawedziKL[wybrana].wkoniec<<" = "<<kolejka_krawedziKL[wybrana].waga<<endl;
        //cout<<ID_wierzcholkow[kolejka_krawedziKL[wybrana].wpoczatek]<<" "<<ID_wierzcholkow[kolejka_krawedziKL[wybrana].wkoniec]<<endl;
        kolejka_krawedziKL[wybrana].uzyta = true;

        if (ID_wierzcholkow[kolejka_krawedziKL[wybrana].wkoniec] > ID_wierzcholkow[kolejka_krawedziKL[wybrana].wpoczatek])
        {
            przepatrzSasiadowKruskalMacierz(kolejka_krawedziKL[wybrana].wkoniec, ID_wierzcholkow[kolejka_krawedziKL[wybrana].wkoniec], ID_wierzcholkow[kolejka_krawedziKL[wybrana].wpoczatek]);
            ID_wierzcholkow[kolejka_krawedziKL[wybrana].wkoniec] = ID_wierzcholkow[kolejka_krawedziKL[wybrana].wpoczatek];
        }
        else if (ID_wierzcholkow[kolejka_krawedziKL[wybrana].wkoniec] < ID_wierzcholkow[kolejka_krawedziKL[wybrana].wpoczatek])
        {
            //cout<<kolejka_krawedziKL[wybrana].wpoczatek<<" "<<ID_wierzcholkow[kolejka_krawedziKL[wybrana].wpoczatek]<<" "<<ID_wierzcholkow[kolejka_krawedziKL[wybrana].wkoniec]<<endl;
            przepatrzSasiadowKruskalMacierz(kolejka_krawedziKL[wybrana].wpoczatek, ID_wierzcholkow[kolejka_krawedziKL[wybrana].wpoczatek], ID_wierzcholkow[kolejka_krawedziKL[wybrana].wkoniec]);
            ID_wierzcholkow[kolejka_krawedziKL[wybrana].wpoczatek] = ID_wierzcholkow[kolejka_krawedziKL[wybrana].wkoniec];
        }

        krawedzie_gotoweKLista[ile_juz + 1].wpoczatek = kolejka_krawedziKL[wybrana].wpoczatek;
        krawedzie_gotoweKLista[ile_juz + 1].wkoniec = kolejka_krawedziKL[wybrana].wkoniec;
        krawedzie_gotoweKLista[ile_juz + 1].waga = kolejka_krawedziKL[wybrana].waga;
        //cout<<"suma wynosi "<<suma<<" i po dodaniu "<<kolejka_krawedziKL[wybrana].waga;
        suma += krawedzie_gotoweKLista[ile_juz + 1].waga;
        //cout<<" wynosi "<<suma<<endl;
        ile_juz++;
    }

    for(int i=0; i<l_wierzcholkow-1; i++)
    {
        cout<<krawedzie_gotoweKLista[i].wpoczatek<<" -> "<<krawedzie_gotoweKLista[i].wkoniec<<": "<<krawedzie_gotoweKLista[i].waga<<endl;
    }
    cout<<"suma: "<<suma<<endl;
}

void Graf::SciezkaBellmanMacierz()
{
    int* sciezka;
    int* koszty, * poprzednicy;
    int suma = 0;
    koszty = new int[l_wierzcholkow];
    poprzednicy = new int[l_wierzcholkow];

    int x, y, i;

    for (i = 0; i < l_wierzcholkow; i++)
    {
        koszty[i] = 1000;
        poprzednicy[i] = -1;
    }

    koszty[wierzcholek_poczatkowy] = 0;

    for (i = 2; i <= l_wierzcholkow; i++)
    {
        for (x = 0; x < l_wierzcholkow; x++)
        {
            for (y = 0; y < l_wierzcholkow; y++)
            {
                if (macierz_sasiedztwa[x][y] != 0 && x != y)
                {
                    if (koszty[y] > koszty[x] + macierz_sasiedztwa[x][y])
                    {
                        koszty[y] = koszty[x] + macierz_sasiedztwa[x][y];
                        poprzednicy[y] = x;
                    }
                }
            }
        }
    }
    cout << "Wyniki dla macierzy:" << endl << "Wierzcholki: ";
    for (x = 0; x < l_wierzcholkow; x++)
    {
        cout << x << " ";
    }
    cout << endl;

    cout << "Koszty przejsc: ";
    for (x = 0; x < l_wierzcholkow; x++)
    {
        cout << koszty[x] << " ";

        suma = suma + koszty[x];
    }
    cout << " Suma: " << suma << endl << "Poprzednicy: ";
    for (x = 0; x < l_wierzcholkow; x++)
    {
        cout << poprzednicy[x] << " ";
    }
    cout << endl;
}

void Graf::SciezkaBellmanLista()
{
    int* koszty, * poprzednicy;
    int suma = 0;
    koszty = new int[l_wierzcholkow];
    poprzednicy = new int[l_wierzcholkow];

    int x, y, i;

    for (i = 0; i < l_wierzcholkow; i++)
    {
        koszty[i] = 1000;
        poprzednicy[i] = -1;
    }

    koszty[wierzcholek_poczatkowy] = 0;

    for (i = 0; i < l_wierzcholkow - 1; i++)
    {
        for (x = 0; x < l_wierzcholkow; x++)
        {
            for (y = 1; y <= lista_sasiedztwa[x][0] * 2; y += 2)
            {
                if (koszty[lista_sasiedztwa[x][y]] > koszty[x] + lista_sasiedztwa[x][y + 1])
                {
                    koszty[lista_sasiedztwa[x][y]] = koszty[x] + lista_sasiedztwa[x][y + 1];
                    poprzednicy[lista_sasiedztwa[x][y]] = x;
                }
            }
        }
    }
    cout << "Wyniki dla listy:" << endl << "Wierzcholki: ";
    for (x = 0; x < l_wierzcholkow; x++)
    {
        cout << x << " ";
    }
    cout << endl;

    cout << "Koszty przejsc: ";
    for (x = 0; x < l_wierzcholkow; x++)
    {
        cout << koszty[x] << " ";
        suma = suma + koszty[x];
    }
    cout << " Suma: " << suma << endl << "Poprzednicy: ";
    for (x = 0; x < l_wierzcholkow; x++)
    {
        cout << poprzednicy[x] << " ";
    }
    cout << endl;
}

void Graf::SciezkaDijkstryMacierz()
{
    int* koszty, * poprzednicy;
    int suma = 0;
    bool* odwiedzone, koniec;
    koszty = new int[l_wierzcholkow];
    poprzednicy = new int[l_wierzcholkow];
    odwiedzone = new bool[l_wierzcholkow];

    int x, y, i, minn;

    for (i = 0; i < l_wierzcholkow; i++)
    {
        koszty[i] = 1000;
        poprzednicy[i] = -1;
        odwiedzone[i] = false;
    }

    koszty[wierzcholek_poczatkowy] = 0;

    for (i = 0; i < l_wierzcholkow - 1; i++)
    {
        koniec = false;
        x = 0;
        while (!koniec)
        {
            if (odwiedzone[x] == false)
            {
                minn = x;
                koniec = true;
                x++;
            }
            else x++;
        }
        for (y = x; y < l_wierzcholkow; y++)
        {
            if (odwiedzone[y] == false && koszty[y] < koszty[minn])
                minn = y;
        }
        //znaleziono najmniejszy nieodwiedzony wierzcholek
        x = minn;
        odwiedzone[x] = true;
        for (y = 0; y < l_wierzcholkow; y++)
        {
            if (macierz_sasiedztwa[x][y] != 0 && y != x && odwiedzone[y] == false)
            {
                if (koszty[y] > koszty[x] + macierz_sasiedztwa[x][y])
                {
                    koszty[y] = koszty[x] + macierz_sasiedztwa[x][y];
                    poprzednicy[y] = x;
                }
            }
        }
    }
    cout << "Wyniki dla macierzy:" << endl << "Wierzcholki: ";
    for (x = 0; x < l_wierzcholkow; x++)
    {
        cout << x << " ";
    }
    cout << endl;

    cout << "Koszty przejsc: ";
    for (x = 0; x < l_wierzcholkow; x++)
    {
        cout << koszty[x] << " ";
        suma = suma + koszty[x];
    }
    cout << " Suma: " << suma << endl << "Poprzednicy: ";
    for (x = 0; x < l_wierzcholkow; x++)
    {
        cout << poprzednicy[x] << " ";
    }
    cout << endl;
}

void Graf::SciezkaDijkstryLista()
{
    int* koszty, * poprzednicy;
    int suma = 0;
    bool* odwiedzone, koniec;
    koszty = new int[l_wierzcholkow];
    poprzednicy = new int[l_wierzcholkow];
    odwiedzone = new bool[l_wierzcholkow];

    int x, y, i, minn;
    bool zmiana;

    for (i = 0; i < l_wierzcholkow; i++)
    {
        koszty[i] = 1000;
        poprzednicy[i] = -1;
        odwiedzone[i] = false;
    }

    koszty[wierzcholek_poczatkowy] = 0;

    for (i = 0; i < l_wierzcholkow - 1; i++)
    {
        koniec = false;
        x = 0;
        while (!koniec)
        {
            if (odwiedzone[x] == false)
            {
                minn = x;
                koniec = true;
                x++;
            }
            else x++;
        }
        for (y = x; y < l_wierzcholkow; y++)
        {
            if (odwiedzone[y] == false && koszty[y] < koszty[minn])
                minn = y;
        }
        //znaleziono najmniejszy nieodwiedzony wierzcholek
        x = minn;
        odwiedzone[x] = true;
        for (y = 1; y <= lista_sasiedztwa[x][0] * 2; y += 2)
        {
            if (koszty[lista_sasiedztwa[x][y]] > koszty[x] + lista_sasiedztwa[x][y + 1] && odwiedzone[lista_sasiedztwa[x][y]] == false)
            {
                koszty[lista_sasiedztwa[x][y]] = koszty[x] + lista_sasiedztwa[x][y + 1];
                poprzednicy[lista_sasiedztwa[x][y]] = x;
            }
        }
    }
    cout << "Wyniki dla listy:" << endl << "Wierzcholki: ";
    for (x = 0; x < l_wierzcholkow; x++)
    {
        cout << x << " ";
    }
    cout << endl;

    cout << "Koszty przejsc: ";
    for (x = 0; x < l_wierzcholkow; x++)
    {
        cout << koszty[x] << " ";
        suma = suma + koszty[x];
    }
    cout << " Suma: " << suma << endl << "Poprzednicy: ";
    for (x = 0; x < l_wierzcholkow; x++)
    {
        cout << poprzednicy[x] << " ";
    }
    cout << endl;
}
