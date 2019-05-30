#pragma once

#include "student.h"
#include <string>
#include <list>
using namespace std;
void duomenys( string &, const string & );
void skaityti_is_failo( string &, const string & );
unsigned GautiSkaiciu( const string & );

void skaityti_is_failo( list<Studentas> & );
void skaityti_is_ivesties( list<Studentas> & );
void read_data( list<Studentas> & );
///aprasomos get_input, skaityti_is_failo, GautiSkaiciu, skaityti_is_failo, skaityti_is_ivesties ir read_data funkcijos.
