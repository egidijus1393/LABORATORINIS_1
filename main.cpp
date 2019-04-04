#include <iostream>
#include <string>
#include <iomanip>
#include <vector>
#include <fstream>

//apsiraðiau bibliotekas
using namespace std;

struct Studentas {

    string vardas;
    string pavarde;
    double vid = 0;
    double med = 0;
    int egz = 0;
};

//apsiraðiau struktura
void TikrintiPavadinima( string &pav ) {
    const int n = pav.length();

    for ( int i = ( pav[0] >= 65 && pav[0] <= 90 ); i < n; i++ ) {
        if ( pav[i] >= 97 && pav[i] <= 122 && pav[0] >= 65 && pav[0] <= 90 ) {
            continue;
        } else {
            cout <<  "Blogai ivestas studento vardas"  << endl;
            cout << "Áveskite dar kartà: ";
            cin >> pav;

            i = 0;
        }
    }
}

//apsiraðiu void funkcija kuri patikrina ar imanomas toks vardas(ar pirmas elemantas maþoji ar didþioji raide o sekantys elementai ið maþosios) uþklausiame vartotojo ivesti studento varda ji patikriname jei vardas neegzistuoja iðvedame i ekrana iveskite dar karta.
int GautiSkaiciu() {
    string input;
    cin >> input;

    while ( input.find_first_not_of( "0123456789" ) != string::npos ) {
        cout << "Blogai ivestas skaicius" << endl;
        cout << "Áveskite dar karta: ";
        cin >> input;
    }
if ( !cin ) { //Jeigu nëra inpto graþinamas vienetas.
        return 1;
    }
    return stoi( input );
}
// Sukdami while cikla tikriname ar musu stringas nera lygus vienam ið nurodytu "find_first_not_of" argumentu, jei yra tada graþiname gera skaiciu jei ne jis graþina" blogai ivestas skaicius".
int main() {
        ifstream fr;

    fr.open("FAILAS.txt");

    string v, a, b, c;


    fr >> v >> a >> b >> c;

    fr.close();


    return 0;

    setlocale( LC_ALL, "Lithuanian" );
//Nustatome lietuviu kalba.
    int s;

    cout << "Iveskite studentu skaiciu: ";
    cin >> s;
//papraðome vartotoja ivesti studentu skaiciu ta skaiciu panaudojame for ciklui norodyti iki kokios reikðmes sukamas foras.
    Studentas studentai[ 100 ];

    for ( int i = 0; i < s; i++ ) {
        cout << "Iveskite " << i+1 << " studento varda: ";
        cin >> studentai[i].vardas;
        TikrintiPavadinima( studentai[i].vardas );
//Vartotoja praðome ivesti varda ji siunciame i void funkcija kad patikritu ar jis egzistuoja.
        cout << endl;
        cout << "Pavarde: ";
        cin >> studentai[i].pavarde;
        TikrintiPavadinima( studentai[i].pavarde );

//Vartotoja praðome ivesti pavarde ji siunciame i void funkcija kad patikritu ar jis egzistuoja.

       vector<int> pazymiai;
        int k;
        char  o;
        cout << "Sugeneruotas pazimys: ";
        k = rand() % 10 + 1 ;//generuojam atsitiktin5 skaièiø nuo 1 iki 10
        cout << k << endl;
            cout << "Ar testi pazymiu generavima? ";
            cin >> o;
            cout << endl;

while ( o == 'T' || o == 't') {//suksis ciklas kol 5vestis yra t
            cout << "Sugeneruotas pazimys: ";
            k = rand() % 10 + 1 ;
            cout << k << endl;
//Kol paþimys maþesnis uz vienetà ir didesnis uþ deðimt iðvesti nurodytà tekstà.
            if ( cin ) {
                pazymiai.push_back( k );//gautà atsakymà stumia i vektoriaus galà
            }
            cout << "Ar testi pazymiu generavima? ";
            cin >> o;
            cout << endl;
        }
//pridedame elementà pabaigoje
        cin.clear();

//Iðtrina bloga ávestá.
        int n = pazymiai.size();
// nuskaitome kiek paþymiø.
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
            //Apskaièiuojame mediana
        }

        studentai[i].vid = suma / n;
    }
//vidurki apskaiciuojame ðia formule.
        cout << "Iveskite egzamino rezultata: ";
        studentai[i].egz = rand()% 10 + 1;
        cout << studentai[i].egz<<endl;
    }
//Vartotoja yra praðoma ivesti egzamino paþimi ið funkcijos "GautiSkaiciu()".
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
        cout.width(10); cout << left<<studentai[i].vardas << " ";
        cout.width(10); cout <<left<< studentai[i].pavarde << " ";

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
//viskas iðspauzdinama lenteleje.
