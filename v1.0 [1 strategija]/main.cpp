#include "input.h"
#include "output.h"
#include <algorithm>
#include <cmath>
#include <ctime>
#include <fstream>
#include <chrono>
using namespace std;
int main() {
    srand( static_cast<unsigned int>( time( nullptr ) ) );///nustatome kiek laiko atsitiktinis skaicius bus generuojamas.

   vector<Studentas> studentas;///sudaromas vektorius.

    
    cout << "Generuojami studentai." << endl;///pranesame apie vykdoma operacija.

    for ( unsigned i = 1; 6 != i; ++i ) {
        studentas = generuoti_studentas( static_cast<unsigned>( pow( 10, i ) ) );
       ofstream os("studentai" + to_string(i) + ".out");
        rasyti_info(  os, studentas );///iskvieciama funkcija kad butu sudaroma lentele i txt faila su galutiniais studentu pazymiais.

    }
///sukamas ciklas kuriame sukuriamas papildomas failai kuriame bus sugeneruojami 10/100/10000/100000 stu dentu su sugeneruotais atsitiktiniais pazymiais.
    cout << "Studentai sugeneruoti sekmingai." << endl;
    cout << "Skirstomi i kategorijas \"golvociai\" ir \"vargseliai\" grupes." << endl;///pranesama i kokias grupes skirstomi studentai
    
    auto pradzia = high_resolution_clock::now();
    
    kategorizuoti_studentas( studentas ) );///irasome duomenis
    
    auto pabaiga = high_resolution_clock::now();
    auto trukme = duration_cast<microseconds>(pabaiga - pradzia);
    
    cout << "Skirste " << trukme.count() << " mikrosekundes" << endl;

    return 0;
}
