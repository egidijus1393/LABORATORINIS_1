#pragma once

#include <string>
#include <deque>
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
deque<Studentas> generuoti_studentas( const unsigned );
const deque<Studentas> kategorizuoti_studentas( deque<Studentas> & );
