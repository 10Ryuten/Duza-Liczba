#include "stdafx.h"
#include "ListaDuzychLiczb.h"
#include "ElementListy.h"
#include <iostream>

bool ListaDuzychLiczb::porownajLiczby(const Liczba *const lewa, const Liczba *const prawa)
{
	char * lewaW = lewa->Wartosc();
	char * prawaW = prawa->Wartosc();
	
	size_t lewaDlug = strlen(lewaW) + 1;
	size_t prawaDlug = strlen(prawaW) + 1;

	bool lewaDodatnia = (lewaW[0] != '-') ? 1 : 0;
	bool prawaDodatnia = (prawaW[0] != '-') ? 1 : 0;

	if (lewaDodatnia && prawaDodatnia)
	{
		if (lewaDlug > prawaDlug) return true;
		if (lewaDlug < prawaDlug) return false;
		return strcmp(lewaW, prawaW) > 0;
	}

	if (!lewaDodatnia && !prawaDodatnia)
	{
		if (lewaDlug > prawaDlug) return false;
		if (lewaDlug < prawaDlug) return true;
		return strcmp(lewaW, prawaW) < 0;
	}

	if (lewaDodatnia && !prawaDodatnia)
		return true;

	if (!lewaDodatnia && prawaDodatnia)
		return false;

	throw "Wystapil nieoczekiwany blad: porownajLiczby";
}

ListaDuzychLiczb::ListaDuzychLiczb()
	:rozmiar (0)
{
	pierwszy = nullptr;
	ostatni = nullptr;
}

ListaDuzychLiczb::~ListaDuzychLiczb()
{
	usunWszystkieElementy();
	pierwszy = nullptr;
	ostatni = nullptr;
}

ListaDuzychLiczb* ListaDuzychLiczb::wstawNaPoczatek(Liczba *const wskLiczba)
{
	ElementListy* nowy = new ElementListy(wskLiczba);
	
	if (pierwszy != nullptr)
	{
		pierwszy->setPoprzedniElement(nowy);
		nowy->setNastepnyElement(pierwszy);
	}
	else {
		ostatni = nowy;
	}
	
	pierwszy = nowy;
	++rozmiar;
	return this;
}
ListaDuzychLiczb* ListaDuzychLiczb::wstawNaKoniec(Liczba *const wskLiczba)
{
	ElementListy* nowy = new ElementListy(wskLiczba);
	
	if (ostatni != nullptr)
	{
		ostatni->setNastepnyElement(nowy);
		nowy->setPoprzedniElement(ostatni);
	}
	else {
		pierwszy = nowy;
	}
	
	ostatni = nowy;
	++rozmiar;
	return this;
}
ListaDuzychLiczb* ListaDuzychLiczb::wstawNaPozycje(Liczba *const wskLiczba, int poz)
{
	if (poz <= 0)
	{
		wstawNaPoczatek(wskLiczba);
		return this;
	}
	if (poz >= rozmiar)
	{
		wstawNaKoniec(wskLiczba);
		return this;
	}
	
	ElementListy* nowy = new ElementListy(wskLiczba);
	ElementListy* nastepny = znajdz(poz);
	ElementListy* poprzedni = nastepny->getPoprzedniElement();
	poprzedni->setNastepnyElement(nowy);
	nowy->setPoprzedniElement(poprzedni);
	nastepny->setPoprzedniElement(nowy);
	nowy->setNastepnyElement(nastepny);
	++rozmiar;
	return this;
}

ListaDuzychLiczb* ListaDuzychLiczb::sortuj()
{
	for (int i = 0; i < rozmiar - 1; ++i)
	{
		for (int j = 0; j < rozmiar - 1 - i; ++j)
		{
			ElementListy* lewyElement = znajdz(j);
			Liczba* lewaLiczba = lewyElement->getLiczba();
			ElementListy* prawyElement = lewyElement->getNastepnyElement();
			Liczba* prawaLiczba = prawyElement->getLiczba();
			
			if (porownajLiczby(lewaLiczba, prawaLiczba))
			{
				ElementListy::swapLiczby(lewyElement, prawyElement);
			}
		}
	}

	return this;
}

ListaDuzychLiczb* ListaDuzychLiczb::usunWszystkieElementy()
{
	ElementListy* goniec = pierwszy;
	while (goniec != nullptr)
	{
		ElementListy* tmp = goniec;
		goniec = goniec->getNastepnyElement();
		delete tmp;
	}
	pierwszy = ostatni = nullptr;
	rozmiar = 0;
	return this;
}
ListaDuzychLiczb* ListaDuzychLiczb::usunPierwszyElement()
{
	if (rozmiar < 1) return this;

	ElementListy* tmp = pierwszy;
	pierwszy = pierwszy->getNastepnyElement();
	if (pierwszy != nullptr)
	{
		pierwszy->setPoprzedniElement(nullptr);
	}
	else {
		ostatni = nullptr;
	}
	
	
	delete tmp;
	--rozmiar;
	return this;
}
ListaDuzychLiczb* ListaDuzychLiczb::usunOstatniElement()
{
	if (rozmiar < 1) return this;

	ElementListy* tmp = ostatni;
	ostatni = ostatni->getPoprzedniElement();
	
	if (ostatni != nullptr) 
	{
		ostatni->setNastepnyElement(nullptr);
	}
	else {
		pierwszy = nullptr;
	}
	
	delete tmp;
	--rozmiar;
	return this;
}
ListaDuzychLiczb* ListaDuzychLiczb::usunPozycje(int poz)
{
	if (poz < 0 || poz >= rozmiar) return this;
	
	if (poz == 0) 
	{
		usunPierwszyElement();
		return this;
	}
	if (poz == rozmiar - 1)
	{
		usunOstatniElement();
		return this;
	}

	ElementListy* eleDoUsuniecia = znajdz(poz);
	ElementListy* poprzedni = eleDoUsuniecia->getPoprzedniElement();
	ElementListy* nastepny = eleDoUsuniecia->getNastepnyElement();
	poprzedni->setNastepnyElement(nastepny);
	nastepny->setPoprzedniElement(poprzedni);
	delete eleDoUsuniecia;
	--rozmiar;
	return this;
}

ElementListy* ListaDuzychLiczb::znajdz(int poz)
{
	ElementListy* goniec = pierwszy;
	while (poz != 0)
	{
		goniec = goniec->getNastepnyElement();
		--poz;
	}
	return goniec;
}



