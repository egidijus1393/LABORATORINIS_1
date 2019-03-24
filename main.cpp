#include <iostream>
#include <string>
#include <iomanip>

//apsirašiau bibliotekas

using namespace std;

struct Studentas {
    string vardas;
    string pavarde;
    double vid = 0;
    int egzas = 0;
};
//apsirašiau struktūrą
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
//apsirašiu void funkcija kuri patikrina ar įmanomas toks vardas(ar pirmas elemantas mažoji ar didžioji raidė o sekantys elementai iš mažosios) užklausiame vartotojo įvesti studento vardą jį patikriname jei vardas neegzistuoja išvedame i ekraną įveskite dar kartą.
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

// Sukdami while ciklą tikriname ar musu stringas nėra lygus vienam iš nurodytų "find_first_not_of" argumentų, jei yra tada gražiname gerą skaičių jei ne jis gražina" blogai įvestas skaičius".
int main() {
    setlocale( LC_ALL, "Lithuanian" );
//Nustatome lietuvių kalbą.
    int s;

    cout << "Áveskite studentu skaièius: ";
    cin >> s;
//paprašome vartotoją įvesti studentų skaičių tą skaičių panaudojame for ciklui norodyti iki kokios reikšmės sukamas foras.
    Studentas studentai[100];

    for ( int i = 0; i < s; i++ ) {
        cout << "Áveskite " << i+1 << " studento vardà: ";
        cin >> studentai[i].vardas;
        TikrintiPavadinima( studentai[i].vardas );
//Vartotoją prašome įvesti vardą jį siunčiame į void funkciją kad patikritų ar jis egzistuoja.
        cout << endl;
        cout << "Pavardæ: ";
        cin >> studentai[i].pavarde;
        TikrintiPavadinima( studentai[i].pavarde );
//Vartotoją prašome įvesti pavardę jį siunčiame į void funkciją kad patikritų ar jis egzistuoja.
        cout << "Studento "  << i+1 << " namu darbu skaièiø: ";
        int n    = GautiSkaiciu();
        int suma = 0;
//Vartotoją prašome įvesti namų darbų skaičių iš funkcijos"GautiSkaičių".
        for ( int j = 0, k; j < n; j++ ) {
            cout << "Iveskite paþymá: ";
            k = GautiSkaiciu();
//sukame for ciklą ir prašome vartotoją įvesti pažymį iš "GautiSkaiciu()" .
            while ( k < 1 || k > 10 ) {
                cout << "Ivestas skaièius yra per maþas/didelis." << endl;
                cout << "Bandykite dar kartà: ";
                k = GautiSkaiciu();
            }

            suma = suma + k;
        }
//tikriname ar pažimys yra tarp vieneto ir dešimties tada siunčiamas kad butų patikrinamas.
        studentai[i].vid = suma / n;
//vidurkį apskaičiuojame šia formule.
        cout << "Iveskite egzamino rezultatà: ";
        studentai[i].egzas = GautiSkaiciu();
    }
//Vartotoją yra prašoma įvesti egzamino pažimį iš funkcijos "GautiSkaičiu()".
    cout << "Vardas\t" << "Pavarde\t" << "\t" << "Galutinis (Vid.)" << endl;
    cout << "----------------------------------------" << endl;

    for ( int i = 0; i < s; i++ ) {
        cout << studentai[i].vardas << "\t" << studentai[i].pavarde;
        cout.width(29);
        cout<< fixed << setprecision( 2 ) << ( 0.4 * studentai[i].vid + 0.6 * studentai[i].egzas ) << endl;
    }
//viskas išspauzdinama lentelėje.
    return 0;
}
