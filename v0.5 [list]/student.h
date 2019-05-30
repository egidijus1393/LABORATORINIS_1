#pragma once

#include <string>
#include <list>
using namespace std;
struct Studentas {
    string vardas;
    string pavarde;
    unsigned egzamino_rez  = 0;
    double vidurkis     = 0;
    double mediana       = 0;
    double galutinis_paz   = 0;
};
///aprasoma struktura.
list<Studentas> generuoti_studentas( const unsigned );
const list<Studentas> kategorizuoti_studentas( list<Studentas> & );
