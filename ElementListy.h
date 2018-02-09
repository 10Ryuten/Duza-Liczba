#pragma once
#include "Liczba.h"

class ElementListy
{
	Liczba * liczba;
	ElementListy *nastepnyElement;
	ElementListy *poprzedniElement;
	
public:

	static void swapLiczby(ElementListy* const, ElementListy* const);

	ElementListy(Liczba *const);
	~ElementListy();

	ElementListy* getNastepnyElement() const;
	ElementListy* getPoprzedniElement() const;
	void setNastepnyElement(ElementListy* const);
	void setPoprzedniElement(ElementListy* const);
	Liczba* getLiczba() const;

};


