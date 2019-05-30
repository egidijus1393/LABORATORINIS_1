#include "random.h"
#include "student.h"
#include <vector>
#include <iostream>
#include <cstdlib>
using namespace std;
void pazymiu_generavimas( vector<unsigned> &pazymiai, unsigned n, bool rodyti_pazymius ) {
    unsigned k;

    while ( n-- ) {
        pazymiai.push_back( ( k = rand() % 10 + 1 ) );///sugeneruojamas pazimys nuo 1 iki 10.

        if ( rodyti_pazymius ) {
            cout << "Sugeneruotas pazimys: " << k << endl;///parodomas sugeneruotas pazimys.
        }
    }
}

vector<unsigned> pazymiu_generavimas( unsigned n ) {
    vector<unsigned> vec;
    pazymiu_generavimas( vec, n, false );

    return vec;
}
///i vektoriu irasomas sugeneruotas pazimys.