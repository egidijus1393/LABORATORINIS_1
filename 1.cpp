#include "input.h"
#include "output.h"
#include <algorithm>
using namespace std;
int main() {
    vector<Studentas> studentas;

    read_data( studentas );

    sort( studentas.begin(), studentas.end(),
               []( const Studentas &lhs, const Studentas &rhs ) {
        return lhs.vardas > rhs.vardas;
    } );

    teksto_isvedimas( studentas );

    return 0;
}
/// yra iskvieciamos read_data ir teksto_isvedimas funkcijos ir atliekamas rusiavimas vardu rusiavimas pagal abecele.
