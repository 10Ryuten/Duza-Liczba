#include "stdafx.h"
#include "funkcjeStrumieniowe.h"
#include "DuzaLiczba.h"
#include "DuzaLiczbaZespolona.h"
#include "ListaDuzychLiczb.h"
#include <iostream>

using namespace std;


ostream & operator<< (ostream& out, DuzaLiczba& duzaLiczba)
{
	cout << duzaLiczba.Wartosc() << endl;

	return out;
}
istream & operator>> (istream& in, DuzaLiczba& duzaLiczba)
{
	bool validacja = false;
	char* bufor;
	while (!validacja)
	{
		validacja = true;	// zakladamy, ze zostana wprowadzone poprawne dane
		bufor = new char[1000000]{};
		in >> bufor;
		

		try {
			duzaLiczba = bufor;
		}
		catch (const char* e)
		{
			cout << e << endl;
			validacja = false;
		}

		if (!validacja) cout << "Prosze wprowadzic poprawna liczbe: " << endl;
	}
	
	delete[] bufor;
	return in;
}



ostream& operator<< (ostream& out, DuzaLiczbaZespolona& duzaLiczbaZespolona) 
{
	out << duzaLiczbaZespolona.getReal().Wartosc() << ", " << duzaLiczbaZespolona.getImagine().Wartosc() << endl;
	return out;
}
istream& operator>> (istream& in, DuzaLiczbaZespolona& duzaLiczbaZespolona)
{
	DuzaLiczba r;
	DuzaLiczba i;
	in >> r;
	in >> i;
	duzaLiczbaZespolona = DuzaLiczbaZespolona(r, i);
	return in;
}



ostream& operator<< (ostream & out, ListaDuzychLiczb* wskLista)
{
	cout << "Lista: " << endl;
	ElementListy* goniec = wskLista->pierwszy;
	while (goniec != nullptr)
	{
		goniec->getLiczba()->show(out);
		goniec = goniec->getNastepnyElement();
	}
	cout << endl;
	return out;
}