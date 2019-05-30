#include "output.h"
#include "student.h"
#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;
void rasyti_info( ostream &out, const vector<Studentas> &studentas ) {
    out << setw( 16 ) << left << "Vardas" << setw( 16 ) << "Pavarde"
        << setw( 17 ) << "Galutinis (Vid.)" << "Galutinis (Med.)" << endl;
    out << string( 61, '-' ) << endl;
    out << fixed << setprecision( 2 );

    for ( const auto &s : studentas ) {
        out << left << setw( 16 ) << s.vardas << setw( 15 ) << s.pavarde
            << setw( 13 ) << right << s.galutinis_paz
            << setw( 17 ) << ( 0.6 * s.mediana + 0.4 * s.egzamino_rez ) << endl;
    }
}
///lenteles sudarymas bei jos uzpildymas.
