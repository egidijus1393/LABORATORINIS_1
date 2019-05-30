#include "input.h"
#include "student.h"
#include "calculations.h"
#include "random.h"
#include <iostream>
#include <fstream>
#include <string>
#include <exception>
#include <list>

void duomenys( string &ivestis, const string &kartoti ) {
    cin.clear();
    cout << "Neteisinga ivestis." << endl;
    cout << kartoti << ": ";
    getline( cin, ivestis );
}
/// jei bloga ivestis prasoma ja pakartoti.
void TikrintiPavadinima( string &ivestis, const string &kartoti ) {
    cin.clear();
    getline( cin, ivestis );

    while ( ivestis.size() < 2 || ( ivestis[ 0 ] < 65 || ivestis[ 0 ] > 90 ) ||
            ivestis.substr( 1 ).find_first_not_of( "abcdefghijklmnopqrstuvwxyz" ) != std::string::npos ) {
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
        while ( g.empty() || g.find_first_not_of( "0123456789" ) != std::string::npos ||
            ( ( k = stoul( g ) ) < 1 || k > 10 ) ) {
            duomenys( g, kartoti );
        }
    }

    return k;
}
/// Sukdami while cikla tikriname ar musu stringas nera lygus vienam is nurodytu "find_first_not_of" argumentu, jei yra tada graziname gera skaiciu jei ne jis grazina" neteisinga ivestis" ir praso vel ivesti skaiciu.
void skaityti_is_failo( list<Studentas> &studentas ) {
    try {
        ifstream in( "kursiokai.txt" );
        in.exceptions( ifstream::failbit );

        string linija;
        getline( in, linija );

        Studentas s;

        while ( !in.eof() ) {
            in >> s.vardas >> s.pavarde;

            list<unsigned> pazymiai;
            unsigned k;

            for ( size_t i = 0; 5 != i; ++i ) {
                pazymiai.push_back( ( in >> k, k ) );
            }

            in >> s.egzamino_rez;
            skaiciuoti_med_vid( s, pazymiai );
            studentas.push_back( s );
        }

        in.close();
        /// nuskaitoma informacija is failo.
    } catch ( const std::ios_base::failure &e ) {
        cout << "Negalimas failo atidarimas. Klaida: " << e.what() << endl;


}
}

void skaityti_is_ivesties( list<Studentas> &studentas ) {
    Studentas s;
    char ans;

    do {
        cout << "Vardas: ";
        TikrintiPavadinima( s.vardas, "Vardas" );

        cout << "Pavarde: ";
        TikrintiPavadinima( s.pavarde, "Pavarde" );

        cout << "Generuoti pazymius atsitiktine tvarka (T/N): ";
        cin >> ans;
        cin.ignore();

       list<unsigned> pazymiai;
        unsigned k;
/// prasome vartotoja ivesti varda, pavarde ir namu darbu pazymius.
        if ( ans == 'T' || ans == 't' ) {
            pazymiu_generavimas( pazymiai, GautiSkaiciu( "Namu darbu pazimiu skaicius" ), true );
        } else {
            cout << "Paspauskite CTRL + Z kad sustabdytumete." << endl;

            while ( !cin.eof() ) {
                k = GautiSkaiciu( "Namu darbu pazimys" );

                if ( !cin.eof() ) {
                    pazymiai.push_back( k );
                }
            }
        }
/// namu darbu pazymiu irasymas.
        try {
           skaiciuoti_med_vid( s, pazymiai );
        } catch ( const std::overflow_error &e ) {
            cout << "Perteklius Klaida: " << e.what() << endl;

        }

        cin.clear();
        s.egzamino_rez     = GautiSkaiciu( "Egzamino pazimys" );
        s.galutinis_paz    = 0.6 * s.vidurkis + 0.4 * s.egzamino_rez;
        studentas.push_back( s );

        cout << "Prideti kita studenta (T/N): ";
        cin >> ans;
        cin.ignore();
    } while ( !cin.eof() && ( ans == 't' || ans == 'T' ) );
}
///sugeneruojamas egzamino pazimys ir klausiame ar prideti studenta.
void read_data( list<Studentas> &studentas ) {
    char ans;

    std::cout << "Skaityti is failo (T/N): ";
    std::cin >> ans;
    std::cin.ignore();

    if ( ans == 't' || ans == 'T' ) {
        skaityti_is_failo( studentas );
    } else {
        skaityti_is_failo( studentas );
    }
}

/// jei atsakimas t tai skaitome is failo jei n prasome ivesties.
