#include "stdafx.h"
#include "ElementListy.h"


ElementListy::ElementListy(Liczba* const liczba)
	: liczba(liczba)
{
	nastepnyElement = nullptr;
	poprzedniElement = nullptr;
}


ElementListy::~ElementListy()
{
	delete liczba;
	liczba = nullptr;
	nastepnyElement = nullptr;
	poprzedniElement = nullptr;
}


ElementListy* ElementListy::getNastepnyElement() const
{
	return nastepnyElement;
}
ElementListy* ElementListy::getPoprzedniElement() const
{
	return poprzedniElement;
}
void ElementListy::setNastepnyElement(ElementListy * const wskEleListy)
{
	nastepnyElement = wskEleListy;
}
void ElementListy::setPoprzedniElement(ElementListy * const wskEleListy)
{
	poprzedniElement = wskEleListy;
}

Liczba* ElementListy::getLiczba() const
{
	return liczba;
}

void ElementListy::swapLiczby(ElementListy* const lewy, ElementListy* const prawy)
{
	Liczba* tmp = lewy->liczba;
	lewy->liczba = prawy->liczba;
	prawy->liczba = tmp;
}
