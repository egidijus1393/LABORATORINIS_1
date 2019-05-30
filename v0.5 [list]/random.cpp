#include "random.h"
#include "student.h"
#include <list>
#include <iostream>
#include <cstdlib>
using namespace std;
void pazymiu_generavimas( list<unsigned> &pazymiai, unsigned n, bool rodyti_pazymius ) {
    unsigned k;

    while ( n-- ) {
        pazymiai.push_back( ( k = rand() % 10 + 1 ) );///sugeneruojamas pazimys nuo 1 iki 10.

        if ( rodyti_pazymius ) {
            cout << "Sugeneruotas pazimys: " << k << endl;///parodomas sugeneruotas pazimys.
        }
    }
}

list<unsigned> pazymiu_generavimas( unsigned n ) {
    list<unsigned> vec;
    pazymiu_generavimas( vec, n, false );

    return vec;
}
///i vektoriu irasomas sugeneruotas pazimys.