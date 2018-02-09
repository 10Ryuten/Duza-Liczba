#pragma once
#include "ElementListy.h"
#include <iostream>

using namespace std;

class ListaDuzychLiczb
{
	ElementListy *pierwszy;
	ElementListy *ostatni;
	int rozmiar;

	friend ostream& operator<< (ostream & out, ListaDuzychLiczb* wskLista);

	ElementListy* znajdz(int);

public:

	static bool porownajLiczby(const Liczba* const, const Liczba* const);

	ListaDuzychLiczb();
	~ListaDuzychLiczb();

	ListaDuzychLiczb* wstawNaPoczatek(Liczba* const);
	ListaDuzychLiczb* wstawNaKoniec(Liczba* const);
	ListaDuzychLiczb* wstawNaPozycje(Liczba* const, int);

	ListaDuzychLiczb* sortuj();

	ListaDuzychLiczb* usunWszystkieElementy();
	ListaDuzychLiczb* usunPierwszyElement();
	ListaDuzychLiczb* usunOstatniElement();
	ListaDuzychLiczb* usunPozycje(int);

};

