#include "calculations.h"
#include "student.h"
#include <vector>
#include <exception>
#include <stdexcept>
using namespace std;
void skaiciuoti_med_vid( Studentas &s, const vector<unsigned> &pazymiai ) {
    if ( !pazymiai.size() ) {
        throw overflow_error( "dalyba is nulio" );
    }

    unsigned sum = 0;

    for ( vector<unsigned>::size_type i = 0, n = pazymiai.size(); n != i; ++i ) {
        if ( n % 2 && i == ( n / 2 ) ) {
            s.mediana = pazymiai[ i ];
        } else if ( !( n % 2 ) && ( i == ( n / 2 ) || i == ( n / 2 + 1 ) ) ) {
            s.mediana += pazymiai[ i ];
        }

        sum += pazymiai[ i ];
    }

    s.mediana    = ( pazymiai.size() % 2 ) ? s.mediana : s.mediana / 2;
    s.vidurkis   = sum / pazymiai.size();
}
///vidurkio ir medianos apskaiciavimas.
