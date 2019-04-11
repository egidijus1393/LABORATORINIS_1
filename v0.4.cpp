#include "input.h"
#include "output.h"
#include <algorithm>
#include <cmath>
#include <ctime>
#include <fstream>
using namespace std;
int main() {
    srand( static_cast<unsigned int>( time( nullptr ) ) );

   vector<Studentas> studentas;

    /// Generuoti studentai.
    cout << "Generuojami studentai." << endl;

    for ( unsigned i = 1; 6 != i; ++i ) {
        studentas = generuoti_studentas( static_cast<unsigned>( pow( 10, i ) ) );
       ofstream os("studentai" + to_string(i) + ".out");
        rasyti_info(  os, studentas );

    }

    cout << "Studentai sugeneruoti sekmingai." << endl;
    cout << "Skirstomi i kategorijas \"golvociai\" ir \"vargseliai\" grupes." << endl;
ofstream os("vargseliai.out");
    rasyti_info( os, kategorizuoti_studentas( studentas ) );
    os.close();
    os.open("galvociai.out");
    rasyti_info( os, studentas );
os.close();
    cout << "Studentai suskirstyti i kategorijas sekmingai.\n" << endl;

    // User-submitted students.
    studentas.clear();
    /*read_data( studentas );*/
    rasyti_info(cout, studentas );

    return 0;
}
