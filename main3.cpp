#include "stdafx.h"
#include "ListaDuzychLiczb.h"
#include "DuzaLiczbaZespolona.h"
#include <iostream>

using namespace std;

// wstawNaPozycje numeruje od 0

int main3() {

	ListaDuzychLiczb *lista = new ListaDuzychLiczb();

	lista->wstawNaPoczatek(new DuzaLiczba("9129081391"));
	lista->wstawNaPoczatek(new DuzaLiczbaZespolona(12908, 1391));
	lista->wstawNaKoniec(new DuzaLiczba("81391"));
	lista->wstawNaKoniec(new DuzaLiczbaZespolona(12908, 1391));
	for (int i = 0; i<15; i++) {
		lista->wstawNaPozycje(new DuzaLiczba(rand() * 9283), 1);
		lista->wstawNaPozycje(new DuzaLiczbaZespolona(rand() * 9293, rand() * 92983), 1);
	}

	cout << lista;

	lista->sortuj();

	cout << lista;

	lista->usunPierwszyElement();
	cout << lista;
	lista->usunOstatniElement();
	cout << lista;
	lista->usunPozycje(3);
	cout << lista;
	lista->usunWszystkieElementy();
	cout << lista;

	delete lista;
	return 0;
}