#include "random.h"
#include "student.h"
#include "input.h"
#include <vector>
#include <iostream>
#include <cstdlib>
using namespace std;
void pazymiu_generavimas( vector<unsigned> &pazymiai ) {
    unsigned n = GautiSkaiciu( "Namu darbu skaicius" );
    unsigned k;

    while ( n-- ) {
        cout << "Sugeneruotas pazimys: " << ( k = rand() % 10 + 1 ) << endl;

        pazymiai.push_back( k );
    }
}
///sugeneruojamas atsitiktinis pazimys ir jis nukeliamas i gala ir patikrinamas ar jis skaicius.
