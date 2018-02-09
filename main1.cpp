#include "stdafx.h"
#include "DuzaLiczba.h"
#include "funkcjeStrumieniowe.h"
#include <iostream>

using namespace std;

int main() {
	// konstruktor bezargumentowy inicjalizuje obiekt wartością 0
	DuzaLiczba l1;
	// konstruktor z argumentem typu int inicjalizuje obiekt wartością stało-liczbową
	DuzaLiczba l2(9999);
	// konstruktor z argumentem typu char* inicjalizuje obiekt podaną wartością
	DuzaLiczba l3("999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999");
	// konstruktor kopiujący głęboko
	DuzaLiczba l4(l3);
	// też konstruktor kopiujący głęboko
	DuzaLiczba l5 = l4;
	DuzaLiczba l6(-987654);

	DuzaLiczba *l7 = new DuzaLiczba("-999999999999999999999999999999");

	// Wszystkie obiekty od l1 do l6 są obiektami statycznymi, 
	// tzn. istnieją od początku do końca działania funkcji main 
	// natomiast obiekt wskazywany przez wskaźnik l7 jest 
	// obiektem dynamicznym, tzn. może być usunięty przez wywołanie 
	// operatora delete.


	// przedefiniowany operator >> 
	cin >> l1;
	// przedefiniowany operator <<
	cout << l1 << l2 << l3 << l4 << l5 << l6 << *l7;

	// usunięcie obiektu wskazywanego przez l7
	delete l7;

	// przedefiniowany operator =
	l1 = l2;
	// przedefiniowane operatory +-*/ dzielenie całkowite
	l1 = l1 + l2 - l3 * l4 / l5;

	// przedefiniowany operator +=
	l1 += 23;
	// przedefiniowany operator += 
	l1 += l4;
	// przedefiniowany operator -=
	l2 -= l3;
	// przedefiniowany operator *=
	l3 *= l4;

	// przedefiniowany operator ==
	if (l4 == "23424")
		// przedefiniowany operator /= dzielenie całkowite
		l4 /= l5;

	// przedefiniowany operator !=
	if (l5 != l4) {
		// przedefiniowany jednoargumentowy operator -
		l5 = -l5;
		cout << l5;
	}

	// przedefiniowany operator =
	l2 = "1221";

	DuzaLiczba silnia = 0;
	// przedefiniowane operatory >= <
	if (l2 >= 0 && l2 < "1223")
	{
		// przedefiniowany operator !
		silnia = !l2;
		cout << silnia;
	}

	return 0;
}