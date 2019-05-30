#pragma once

#include <string>
#include <vector>
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
vector<Studentas> generuoti_studentas( const unsigned );
const vector<Studentas> kategorizuoti_studentas( vector<Studentas> & );
