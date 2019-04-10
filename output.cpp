#include "output.h"
#include "student.h"
#include <iostream>
#include <iomanip>
#include <vector>
using namespace std;
void teksto_isvedimas( const vector<Studentas> &studentas ) {
    cout << endl << setw( 16 ) << left << "Vardas" << setw( 16 ) << "Pavarde"
            << setw( 17 ) << "Galutinis (Vid.)" << "Galutinis (Med.)" << endl;
    cout << string( 61, '-' ) << endl;
    cout << fixed << setprecision( 2 );

    for ( const auto &s : studentas ) {
        cout << left << setw( 16 ) << s.vardas << setw( 15 ) << s.pavarde
                << setw( 13 ) << right << ( 0.6 * s.vidurkis + 0.4 * s.egzamino_rez )
                << setw( 17 ) << ( 0.6 * s.mediana + 0.4 * s.egzamino_rez ) << endl;
    }
}
///lenteles sudarymas bei jos uzpildymas.
