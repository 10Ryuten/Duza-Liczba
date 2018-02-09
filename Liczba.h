#pragma once
#include <iostream>

using namespace std;

class Liczba
{
public:
	Liczba();
	virtual ~Liczba();

	virtual char* Wartosc() const = 0;

	virtual void show(ostream&) = 0;

};

