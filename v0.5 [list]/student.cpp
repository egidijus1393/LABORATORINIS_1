#include "student.h"
#include "calculations.h"
#include "random.h"
#include <list>
#include <string>
#include <cstdlib>
#include <algorithm>
#include <iostream>
using namespace std;
list<Studentas> generuoti_studentas( const unsigned n ) {
    list<Studentas> studentas;
    Studentas s;
auto start = high_resolution_clock::now();
    for ( list<Studentas>::size_type i = 0; n != i; ++i ) {

        studentas.push_back( s );
        s.vardas          = "Vardas" + to_string( i + 1 );///sukuriamas vardas prie zodzio Vardas pridedant vis 1-netu didesni skaiciu.
        s.pavarde       = "Pavarde" + to_string( i + 1 );///sukuriama pavarde prie zodzio Pavarde pridedant vis 1-netu didesni skaiciu.
        s.egzamino_rez     = rand() % 10 + 1;///rezultatai generuojami su rand funkcija nuo 1 iki 10
        skaiciuoti_med_vid( s, pazymiu_generavimas( 5 ) );
        s.galutinis_paz    = 0.6 * s.vidurkis + 0.4 * s.egzamino_rez;///galutinio pazymio skaiciavimas

    }
    return studentas;
}
///skaiciuojamas laikas kiek uztrunka programai atlikti funkcijai.
const list<Studentas> kategorizuoti_studentas( list<Studentas> &studentas ) {
    const auto rem = partition( studentas.begin(), studentas.end(),
                                     []( Studentas &studentas ) {
        return studentas.galutinis_paz >= 5.0;///pagal galutini pazimi graziname studentus kurie turi didesni pazimi nei 5.
    } );

    const list<Studentas> vargselis( rem, studentas.end() );
    studentas.erase( rem, studentas.cend() );

    return vargselis;
}
