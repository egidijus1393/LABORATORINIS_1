#pragma once

#include "student.h"
#include <string>
#include <vector>
using namespace std;
void duomenys( string &, const string & );
void skaityti_is_failo( string &, const string & );
unsigned GautiSkaiciu( const string & );

void skaityti_is_failo( vector<Studentas> & );
void skaityti_is_ivesties( vector<Studentas> & );
void read_data( vector<Studentas> & );
///aprasomos get_input, skaityti_is_failo, GautiSkaiciu, skaityti_is_failo, skaityti_is_ivesties ir read_data funkcijos.
