#pragma once
#include "DuzaLiczba.h"
#include "DuzaLiczbaZespolona.h"
#include <iostream>


using namespace std;

// DuzaLiczba

ostream& operator<< (ostream &, DuzaLiczba &);
istream& operator>> (istream &, DuzaLiczba &);


// DuzaLiczbaZespolona

ostream& operator<< (ostream &, DuzaLiczbaZespolona &);
istream& operator>> (istream &, DuzaLiczbaZespolona &);

