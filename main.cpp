#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iomanip>
#include <algorithm>

///apsirasau bibliotekas.

using namespace std;

struct Studentas {
    string vardas;
    string pavarde;
    unsigned egzamino_rez  = 0;
    double vidurkis      = 0;
    double mediana       = 0;
};
///apsirasiau struktura.

void duomenys( string &ivestis, const string &kartoti ) {
    cin.clear();
    cout << "neteisinga ivestis." << endl;
    cout << kartoti << ": ";
    getline( cin, ivestis );
}
/// jei bloga ivestis prasoma kartoti varda.

void TikrintiPavadinima( string &ivestis, const string &kartoti ) {
    cin.clear();
    getline( cin, ivestis );

    while ( ivestis.size() < 2 || ( ivestis[ 0 ] < 65 || ivestis[ 0 ] > 90 ) ||
            ivestis.substr( 1 ).find_first_not_of( "abcdefghijklmnopqrstuvwxyz" ) != string::npos ) {
        duomenys( ivestis, kartoti );
    }
}
///apsirasiu void funkcijas kurios patikrina ar imanomas toks vardas(ar pirmas elemantas mazoji ar didzioji raide o sekantys elementai is mazosios) jei blogas vardas iskvieciama funkcija.
unsigned GautiSkaiciu( const string &kartoti ) {
    string g;
    unsigned k = 0;

    cout << kartoti << ": ";
    getline( cin, g );

    if ( !cin.eof() ) {
        while ( g.empty() || g.find_first_not_of( "0123456789" ) != string::npos ||
            ( ( k = stoul( g ) ) < 1 || k > 10 ) ) {
            duomenys( g, kartoti );
        }
    }

    return k;
}
/// Sukdami while cikla tikriname ar musu stringas nera lygus vienam is nurodytu "find_first_not_of" argumentu, jei yra tada graziname gera skaiciu jei ne jis grazina" neteisinga ivestis" ir praso vel ivesti skaiciu.

void skaiciuoti_med_vid( Studentas &s, const vector<unsigned> &pazymiai ) {
    if ( pazymiai.size() ) {
        unsigned sum = 0;

        for ( vector<unsigned>::size_type i = 0, n = pazymiai.size(); n != i; ++i ) {
            if ( n % 2 && i == ( n / 2 ) ) {
                s.mediana = pazymiai[ i ];
            } else if ( !( n % 2 ) && ( i == ( n / 2 ) || i == ( n / 2 + 1 ) ) ) {
                s.mediana += pazymiai[ i ];
            }

            sum += pazymiai[ i ];
        }

        s.mediana    = ( pazymiai.size() % 2 ) ? s.mediana : s.mediana / 2;
        s.vidurkis   = sum / pazymiai.size();
    }
}
/// su vektorium nustatom kiek yra pazymiu, jei lyginis skaicius skaiciuojame vienaip jei nelyginis kitaip.
int main() {
    srand( time( NULL ) );

    vector<Studentas> studentas;
    Studentas s;

    char ans;

    cout << "skaityti is failo (T/N): ";
    cin >> ans;
    cin.ignore();

    unsigned k;
///klausiame vartotojo ar nuskaityti duomenis is failo
    if ( ans == 't' || ans == 'T' ) {
        ifstream in( "kursiokai.txt" );
/// jei ivestis 't' arba 'T' nuskaitome duomenis is txt dokumento "kursiokai"
        if ( !in ) {
            cout << "klaida atidarant faila." << endl;
            return -1;
        }
/// jei nerandama tokio failo ivedame klaida.
        string linija;
        getline( in, linija );

        while ( !in.eof() ) {
            in >> s.vardas >> s.pavarde;
///kol nesibags tekstinis failas nebaigs nuskaitymas
            vector<unsigned> pazymiai;
            for ( size_t i = 0; 5 != i; ++i ) {
                pazymiai.push_back( ( in >> k, k ) );
            }
/// nuskaito pazymi ir ji nukelia i gala.
            in >> s.egzamino_rez;
            skaiciuoti_med_vid( s, pazymiai );
            studentas.push_back( s );
        }
/// nuskaito egzamino pazumi ir studento duomenis nukelia i gala
        in.close();
    } else {
        ///jeigu vartotojas nusprendzia kad nenuskaityti is failo.
        do {
            cout << "Vardas: ";
            TikrintiPavadinima( s.vardas, "Vardas" );

            cout << "Pavarde: ";
           TikrintiPavadinima( s.pavarde, "Pavarde" );

            cout << "Generuoti pazymius atsitiktinai (T/N): ";
            cin >> ans;
            cin.ignore();
/// vartotoja prasome tam tikru ivesciu
            vector<unsigned> pazymiai;

            if ( ans == 'T' || ans == 't' ) {
                unsigned n = GautiSkaiciu( "namu darbu skaicius" );

                while ( n-- ) {
                    cout << "Atsitiktinis pazimys: " << ( k = rand() % 10 + 1 ) << endl;

                    pazymiai.push_back( k );
                }
                ///sugeneruojami atsitiktiniai pazymiai ir jie nukeiami i gala.
            } else {
                cout << "paspauskite CTRL + Z kad sustabdytumete." << endl;

                while ( !cin.eof() ) {
                    k = GautiSkaiciu( "namu darbo pazimys" );

                    if ( !cin.eof() ) {
                        pazymiai.push_back( k );
                    }
                }
            }
/// ivedamas pazimys ir nukeliamas i gala.
            skaiciuoti_med_vid( s, pazymiai );

            cin.clear();
            s.egzamino_rez = GautiSkaiciu( "Egzamino Pazimys" );
            studentas.push_back( s );
/// ivedamas pazimys ir nukeliamas i gala
            cout << "Prideti studenta (T/N): ";
            cin >> ans;
            cin.ignore();
        } while ( !cin.eof() && ( ans == 't' || ans == 'T' ) );
    }
/// uzklausa del pridedamo studento.
    sort( studentas.begin(), studentas.end(),
               [] ( const Studentas &lhs, const Studentas &rhs ) {
        return lhs.vardas > rhs.vardas;
    } );
/// atrusiuojame vardus bei pavardes pagal abecele.
    cout << "\nVardas\tPavarde\tPazimys (Vid.)\tPazimys (Med.)" << endl;
    cout << string( 61, '-' ) << endl;

   for ( const auto &s : studentas ) {
        cout << left << setw( 16 ) << s.vardas << setw( 15 ) << s.pavarde
            << setw( 13 ) << right << ( 0.6 * s.vidurkis + 0.4 * s.egzamino_rez )
            << setw( 17 ) << ( 0.6 * s.mediana + 0.4 * s.egzamino_rez ) << endl;
    }

    return 0;
}
///rezultatai atspauzdinami lenteleje.
