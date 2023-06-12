#include <iostream>
#include <time.h>
#include "testowanie.h"
#include "testowanieAutomatyczne.h"

using namespace std;

int main()
{
    srand(time(NULL));
    int ktora;
    Testowanie testowanie;
    TestowanieAutomatyczne test;

    while (true)
    {
        cout << "Ktory problem chcesz rozwiazac? " << endl;
        cout << "1. Wyznaczanie minimalnego drzewa rozpinajacego" << endl;
        cout << "2. Wyznaczanie najkrotszej sciezki" << endl;
        //cout<<"3. Wyznaczanie maksymalnego przeplywu"<<endl;
        cout << "3. Koniec" << endl;
        cout << "4. Wykonaj testowanie automatyczne" << endl;
        cin >> ktora;

        if (ktora == 1)
        {
            system("cls");
            cout << "Wyznaczanie minimalnego drzewa rozpinajacego." << endl;
            testowanie.testowanieMST();
        }
        if (ktora == 2)
        {
            system("cls");
            cout << "Wyznaczanie najkrotszej sciezki." << endl;
            testowanie.testowanieSciezki();
        }
        /*if(ktora==3)
        {
            system("cls");
            cout<<"Wyznaczanie maksymalnego przeplywu."<<endl;
            testowanie.testowaniePrzeplywu();
        }*/
        if (ktora == 3) return 0;
        if (ktora == 4)
        {
            cout << "Test automatyczny" << endl;
            test.testowanie();
        }
    }

    return 0;
}
