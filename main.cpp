#include <iostream>
#include <string>
#include <iomanip>

//apsirašiau bibliotekas
using namespace std;

struct Studentas {
    string vardas;
    string pavarde;
    double vid = 0;
    double med = 0;
    int egz = 0;
};
//apsirašiau struktura
void TikrintiPavadinima( string &pav ) {
    const int n = pav.length();

    for ( int i = ( pav[0] >= 65 && pav[0] <= 90 ); i < n; i++ ) {
        if ( pav[i] >= 97 && pav[i] <= 122 && pav[0] >= 65 && pav[0] <= 90 ) {
            continue;
        } else {
            cout <<  "Blogai ivestas studento vardas"  << endl;
            cout << "Įveskite dar kartą: ";
            cin >> pav;

            i = 0;
        }
    }
}
//apsirašiu void funkcija kuri patikrina ar imanomas toks vardas(ar pirmas elemantas mažoji ar didžioji raide o sekantys elementai iš mažosios) užklausiame vartotojo ivesti studento varda ji patikriname jei vardas neegzistuoja išvedame i ekrana iveskite dar karta.
int GautiSkaiciu() {
    string input;
    cin >> input;

    while ( input.find_first_not_of( "0123456789" ) != string::npos ) {
        cout << "Blogai ivestas skaicius" << endl;
        cout << "Įveskite dar karta: ";
        cin >> input;
    }

    return stoi( input );
}
// Sukdami while cikla tikriname ar musu stringas nera lygus vienam iš nurodytu "find_first_not_of" argumentu, jei yra tada gražiname gera skaiciu jei ne jis gražina" blogai ivestas skaicius".
int main() {
    setlocale( LC_ALL, "Lithuanian" );
//Nustatome lietuviu kalba.
    int s;

    cout << "Iveskite studentu skaiciu: ";
    cin >> s;
//paprašome vartotoja ivesti studentu skaiciu ta skaiciu panaudojame for ciklui norodyti iki kokios reikšmes sukamas foras.
    Studentas studentai[ 100 ];

    for ( int i = 0; i < s; i++ ) {
        cout << "Iveskite:" << i+1 << " studento varda: ";
        cin >> studentai[i].vardas;
        TikrintiPavadinima( studentai[i].vardas );
//Vartotoja prašome ivesti varda ji siunciame i void funkcija kad patikritu ar jis egzistuoja.
        cout << endl;
        cout << "Pavarde: ";
        cin >> studentai[i].pavarde;
        TikrintiPavadinima( studentai[i].pavarde );
//Vartotoja prašome ivesti pavarde ji siunciame i void funkcija kad patikritu ar jis egzistuoja.
        cout << "Studento "<<i+1<<"namu darbu skaicius: ";
        int n    = GautiSkaiciu();
        int suma = 0;
//Vartotoja prašome ivesti namu darbu skaiciu iš funkcijos"GautiSkaiciu".
        for ( int j = 1, k; j <= n; j++ ) {
            cout << "Iveskite pazymi: ";
            k = GautiSkaiciu();
//sukame for cikla ir prašome vartotoja ivesti pažymi iš "GautiSkaiciu()" .
            while ( k < 1 || k > 10 ) {
                cout << "Ivestas skaicius yra per mazas/didelis." << endl;
                cout << "Bandykite dar karta: ";
                k = GautiSkaiciu();
            }
//tikriname ar pažimys yra tarp vieneto ir dešimties tada siunciamas kad butu patikrinamas.
            if ( n % 2 && j == ( n / 2 + 1 ) ) {
                studentai[ i ].med = k;
            } else if ( !( n % 2 ) && ( j == ( n / 2 ) || j == ( n / 2 + 1 ) ) ) {
                studentai[i].med += k;
            }
//Tikrinamas medianos tipas.
            suma += k;
        }

        if ( !( n % 2 ) ) {
            studentai[i].med /= 2;
            //Apskaičiuojame mediana
        }

        studentai[i].vid = suma / n;
//vidurki apskaiciuojame šia formule.
        cout << "Iveskite egzamino rezultata: ";
        studentai[i].egz = GautiSkaiciu();
    }
//Vartotoja yra prašoma ivesti egzamino pažimi iš funkcijos "GautiSkaiciu()".
    cout << "Isvesti mediana (T) ar vidurki (N): ";
    char ats;
    cin >> ats;

    bool mediana = false;

    if ( ats == 'T' || ats == 't' ) {
        mediana = true;
        cout << "Vardas\t" << "Pavarde\t" << "Galutinis (Med.)" << endl;
    } else {
        cout << "Vardas\t" << "Pavarde\t" << "Galutinis (Vid.)" << endl;
    }

    cout << "--------------------------------" << endl;

    double gal = 0;

    for ( int i = 0; i < s; i++, gal = 0 ) {
        cout << studentai[i].vardas << "\t" << studentai[i].pavarde << "\t";

        if ( mediana ) {
            gal = 0.4 * studentai[i].med;
        } else {
            gal = 0.4 * studentai[i].vid;
        }

        gal += 0.6 * studentai[i].egz;

        cout << fixed << setprecision( 2 ) << gal << endl;
    }

    return 0;
}
//viskas išspauzdinama lenteleje.
