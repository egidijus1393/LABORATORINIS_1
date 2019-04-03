#include <iostream>
#include <string>
#include <iomanip>
#include <vector>//Itraukiame papildoma vektoriaus biblioteka.
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
if ( !cin ) { //Jeigu nėra inpto gražinamas vienetas.
        return 1;
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
        cout << "Iveskite " << i+1 << " studento varda: ";
        cin >> studentai[i].vardas;
        TikrintiPavadinima( studentai[i].vardas );
//Vartotoja prašome ivesti varda ji siunciame i void funkcija kad patikritu ar jis egzistuoja.
        cout << endl;
        cout << "Pavarde: ";
        cin >> studentai[i].pavarde;
        TikrintiPavadinima( studentai[i].pavarde );

//Vartotoja prašome ivesti pavarde ji siunciame i void funkcija kad patikritu ar jis egzistuoja.

       vector<int> pazymiai;
        int k;
        char  o;
        cout << "Iveskite pazymi: ";
        k = rand() % 10 + 1 ;//generuojam atsitiktin5 skaičių nuo 1 iki 10
        cout << k << endl;
            cout << "Ar dar bus? ";
            cin >> o;
            cout << endl;

while ( o == 'T' || o == 't') {//suksis ciklas kol 5vestis yra t
            cout << "Iveskite pazymi: ";
            k = rand() % 10 + 1 ;
            cout << k << endl;
//Kol pažimys mažesnis uz vienetą ir didesnis už dešimt išvesti nurodytą tekstą.
            if ( cin ) {
                pazymiai.push_back( k );//gautą atsakymą stumia i vektoriaus galą
            }
            cout << "Ar dar bus? ";
            cin >> o;
            cout << endl;
        }
//pridedame elementą pabaigoje
        cin.clear();

//Ištrina bloga įvestį.
        int n = pazymiai.size();
// nuskaitome kiek pažymių.
        if ( n ) {
            int suma = 0;

            for ( int j = 0; j < n; j++ ) {
                suma += pazymiai[ i ];

                if ( n % 2 && j == ( n / 2 + 1 ) ) {
                    studentai[ i ].med = pazymiai[ i ];
                } else if ( !( n % 2 ) && ( j == ( n / 2 ) || j == ( n / 2 + 1 ) ) ) {
                    studentai[ i ].med += pazymiai[ i ];
                }
            }
//Nustatomas medianos tipas.

        if ( !( n % 2 ) ) {
            studentai[i].med /= 2;
            //Apskaičiuojame mediana
        }

        studentai[i].vid = suma / n;
    }
//vidurki apskaiciuojame šia formule.
        cout << "Iveskite egzamino rezultata: ";
        studentai[i].egz = rand()% 10 + 1;
        cout << studentai[i].egz<<endl;
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
