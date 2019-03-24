#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

struct Studentas {
    string vardas;
    string pavarde;
    double vid = 0;
    int egzas = 0;
};

void TikrintiPavadinima( string &pav ) {
    const int n = pav.length();

    for ( int i = ( pav[0] >= 65 && pav[0] <= 90 ); i < n; i++ ) {
        if ( pav[i] >= 97 && pav[i] <= 122 && pav[0] >= 65 && pav[0] <= 90 ) {
            continue;
        } else {
            cout << endl << "Blogai ivestas studento vardas" << endl << endl;
            cout << "Áveskite dar kartà: ";
            cin >> pav;

            i = 0;
        }
    }
}

int GautiSkaiciu() {
    string input;
    cin >> input;

    while ( input.find_first_not_of( "0123456789" ) != string::npos ) {
        cout << endl << "Blogai ávestas skaièius" << endl << endl;
        cout << "Áveskite dar karta: ";
        cin >> input;
    }

    return stoi( input );
}

int main() {
    setlocale( LC_ALL, "Lithuanian" );

    int s;

    cout << "Áveskite studentu skaièius: ";
    cin >> s;

    Studentas studentai[100];

    for ( int i = 0; i < s; i++ ) {
        cout << "Áveskite " << i+1 << " studento vardà: ";
        cin >> studentai[i].vardas;
        TikrintiPavadinima( studentai[i].vardas );

        cout << endl;
        cout << "Pavardæ: ";
        cin >> studentai[i].pavarde;
        TikrintiPavadinima( studentai[i].pavarde );

        cout << "Studento "  << i+1 << " namu darbu skaièiø: ";
        int n    = GautiSkaiciu();
        int suma = 0;

        for ( int j = 0, k; j < n; j++ ) {
            cout << "Iveskite paşymá: ";
            k = GautiSkaiciu();

            while ( k < 1 || k > 10 ) {
                cout << "Ivestas skaièius yra per maşas/didelis." << endl;
                cout << "Bandykite dar kartà: ";
                k = GautiSkaiciu();
            }

            suma = suma + k;
        }

        studentai[i].vid = suma / n;

        cout << "Iveskite egzamino rezultatà: ";
        studentai[i].egzas = GautiSkaiciu();
    }

    cout << "Vardas\t" << "Pavarde\t" << "\t" << "Galutinis (Vid.)" << endl;
    cout << "----------------------------------------" << endl;

    for ( int i = 0; i < s; i++ ) {
        cout << studentai[i].vardas << "\t" << studentai[i].pavarde;
        cout.width(29);
        cout<< fixed << setprecision( 2 ) << ( 0.4 * studentai[i].vid + 0.6 * studentai[i].egzas ) << endl;
    }

    return 0;
}
