#include <iostream>
#include "Czas.h"

#ifndef TESTOWANIEAUTOMATYCZNE_H
#define TESTOWANIEAUTOMATYCZNE_H

class TestowanieAutomatyczne
{

public:
    void testowanie();
    void testowanieMSTPrimMacierz(int n);
    void testowanieMSTPrimLista(int n);
    void testowanieMSTKruskalMacierz(int n);
    void testowanieMSTKruskalLista(int n);
    void testowanieSciezkiDijkstryMacierz(int n);
    void testowanieSciezkiDijkstryLista(int n);
    void testowanieSciezkiBellmanMacierz(int n);
    void testowanieSciezkiBellmanLista(int n);

};

#endif
