#include "stdafx.h"
#include "DuzaLiczbaZespolona.h"
#include "funkcjeStrumieniowe.h"
#include <iostream>

using namespace std;

int main2() {
	// konstruktor bezargumentowy inicjalizuje obiekt wartością (0,0)
	DuzaLiczbaZespolona l1;
	// konstruktor z argumentem typu int inicjalizuje obiekt 
	// wartością stało-liczbową (172834,0)
	DuzaLiczbaZespolona l2(172834);
	// konstruktor z dwoma argumentami typu int inicjalizuje  
	// inicjalizuje obiekt wartością (134,394)
	DuzaLiczbaZespolona l2a(134, 394);

	// konstruktor z argumentem typu char* inicjalizuje obiekt podaną 
	// wartością (“1728390”)
	DuzaLiczbaZespolona l3("1728390");

	// konstruktor z argumentem typu char* inicjalizuje obiekt 
	// podaną wartością (17283,-420)
	DuzaLiczbaZespolona l3a("17283", "-420");

	// konstruktor kopiujący głęboko
	DuzaLiczbaZespolona l4(l3);
	// konstruktor z argumentem typu char* inicjalizuje 
	DuzaLiczbaZespolona l5 = l4;
	DuzaLiczbaZespolona l6(-172834);

	DuzaLiczbaZespolona *l7 = new DuzaLiczbaZespolona("-172839023498234792834798237494");

	// Wszystkie obiekty od l1 do l6 są obiektami statycznymi, 
	// tzn. istnieją od początku do końca działania funkcji main 
	// natomiast obiekt wskazywany przez wskaźnik l7 jest obiektem
	// dynamicznym, tzn. może być usunięty przez wywołanie operatora delete.
	// przedefiniowany operator >>
	cin >> l1;
	// przedefiniowany operator <<              
	cout << l1 << l2 << l3 << l4 << l5 << l6 << *l7;
	cout << l2a << l3a;
	// usunięcie obiektu wskazywanego przez l7
	delete l7;

	// przedefiniowany operator =
	l1 = l2;
	// przedefiniowane operatory +-*/  dzielenie całkowite            
	l1 = l1 + l2 - l3 * l4 / l5;

	// przedefiniowany operator += - zwiększenie składowej rzeczywistej liczby l1 o 23
	l1 += 23;
	// przedefiniowany operator +=
	l1 += l4;
	// przedefiniowany operator -=
	l2 -= l3;
	// przedefiniowany operator *=
	l3 *= l4;

	// przedefiniowany operator ==
	if (l4 == "23424")
		// przedefiniowany operator /=  dzielenie całkowite        
		l4 /= l5;

	// przedefiniowany operator ==
	if (l4 == l5)
		// przedefiniowany operator /=  dzielenie całkowite          
		l4 /= l5;

	// przedefiniowany operator !=
	if (l5 != l4) {
		// przedefiniowany operator – zmiana wartości składowych na przeciwne          
		l5 = -l5;
		cout << l5;
	}

	// przedefiniowany operator =
	l2 = "1221";
	// przedefiniowane operatory >=  <
	if (l2 >= 0 && l2 < "1223") {
		cout << "ok";
	}

	return 0;
}