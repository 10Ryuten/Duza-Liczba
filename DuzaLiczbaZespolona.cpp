#include "stdafx.h"
#include "DuzaLiczba.h"
#include "DuzaLiczbaZespolona.h"
#include "funkcjeStrumieniowe.h"
#include <iostream>

using namespace std;

const DuzaLiczbaZespolona DuzaLiczbaZespolona::ZERO = DuzaLiczbaZespolona();

DuzaLiczbaZespolona::DuzaLiczbaZespolona(int r, int i)
{
	real = new DuzaLiczba(r);
	imagine = new DuzaLiczba(i);
}
DuzaLiczbaZespolona::DuzaLiczbaZespolona(const char * r, const char * i)
{
	real = new DuzaLiczba(r);
	imagine = new DuzaLiczba(i);	
}
DuzaLiczbaZespolona::DuzaLiczbaZespolona(const DuzaLiczba& r, const DuzaLiczba& i)
{
	real = new DuzaLiczba(r);
	imagine = new DuzaLiczba(i);
}
DuzaLiczbaZespolona::DuzaLiczbaZespolona(const DuzaLiczbaZespolona& duzaLiczbaZespolona)
{
	real = new DuzaLiczba(duzaLiczbaZespolona.getReal());
	imagine = new DuzaLiczba(duzaLiczbaZespolona.getImagine());
}

DuzaLiczbaZespolona::~DuzaLiczbaZespolona()
{
	delete real;
	real = nullptr;
	delete imagine;
	imagine = nullptr;
}

DuzaLiczbaZespolona& DuzaLiczbaZespolona::operator= (const DuzaLiczbaZespolona& duzaLiczbaZespolona)
{
	if (this != &duzaLiczbaZespolona)
	{
		delete real;
		real = new DuzaLiczba(duzaLiczbaZespolona.getReal());
		delete imagine;
		imagine = new DuzaLiczba(duzaLiczbaZespolona.getImagine());
	}
	return *this;
}

DuzaLiczbaZespolona DuzaLiczbaZespolona::operator+ (const DuzaLiczbaZespolona& duzaLiczbaZespolona) const
{
	return DuzaLiczbaZespolona(
		getReal() + duzaLiczbaZespolona.getReal(),
		getImagine() + duzaLiczbaZespolona.getImagine()
	);
}
DuzaLiczbaZespolona DuzaLiczbaZespolona::operator- (const DuzaLiczbaZespolona& duzaLiczbaZespolona) const
{
	return DuzaLiczbaZespolona(
		getReal() - duzaLiczbaZespolona.getReal(),
		getImagine() - duzaLiczbaZespolona.getImagine()
	);
}
DuzaLiczbaZespolona DuzaLiczbaZespolona::operator* (const DuzaLiczbaZespolona& duzaLiczbaZespolona) const
{
	return DuzaLiczbaZespolona(
		getReal() * duzaLiczbaZespolona.getReal() - getImagine() * duzaLiczbaZespolona.getImagine(),
		getReal() * duzaLiczbaZespolona.getImagine() + getImagine() * duzaLiczbaZespolona.getReal()
	);
}
DuzaLiczbaZespolona DuzaLiczbaZespolona::operator/ (const DuzaLiczbaZespolona& duzaLiczbaZespolona) const
{
	if (duzaLiczbaZespolona == ZERO) throw "Nie mozna dzielic przez ZERO! ";

	DuzaLiczba mianownik = DuzaLiczba(
		duzaLiczbaZespolona.getReal() * duzaLiczbaZespolona.getReal()
		+ duzaLiczbaZespolona.getImagine() * duzaLiczbaZespolona.getImagine()
	);

	return DuzaLiczbaZespolona(
		( getReal() * duzaLiczbaZespolona.getReal() + getImagine() * duzaLiczbaZespolona.getImagine() ) / mianownik,
		( getImagine() * duzaLiczbaZespolona.getReal() - getReal() * duzaLiczbaZespolona.getImagine() ) / mianownik 
	);
}

DuzaLiczbaZespolona& DuzaLiczbaZespolona::operator+= (const DuzaLiczbaZespolona& duzaLiczbaZespolona)
{
	*this = *this + duzaLiczbaZespolona;
	return *this;
}
DuzaLiczbaZespolona& DuzaLiczbaZespolona::operator-= (const DuzaLiczbaZespolona& duzaLiczbaZespolona)
{
	*this = *this - duzaLiczbaZespolona;
	return *this;
}
DuzaLiczbaZespolona& DuzaLiczbaZespolona::operator*= (const DuzaLiczbaZespolona& duzaLiczbaZespolona)
{
	*this = *this * duzaLiczbaZespolona;
	return *this;

}
DuzaLiczbaZespolona& DuzaLiczbaZespolona::operator/= (const DuzaLiczbaZespolona& duzaLiczbaZespolona)
{
	*this = *this / duzaLiczbaZespolona;
	return *this;

}

bool DuzaLiczbaZespolona::operator== (const DuzaLiczbaZespolona& duzaLiczbaZespolona) const
{
	if (getReal() == duzaLiczbaZespolona.getReal() && getImagine() == duzaLiczbaZespolona.getImagine())
	{
		return true;
	} else 
	{
		return false;
	}
}
bool DuzaLiczbaZespolona::operator!= (const DuzaLiczbaZespolona& duzaLiczbaZespolona) const
{
	return !(*this == duzaLiczbaZespolona);
}
bool DuzaLiczbaZespolona::operator< (const DuzaLiczba& duzaLiczba) const
{
	return getReal() < duzaLiczba;
}
bool DuzaLiczbaZespolona::operator> (const DuzaLiczba& duzaLiczba) const
{
	return getReal() > duzaLiczba;
}
bool DuzaLiczbaZespolona::operator<= (const DuzaLiczba& duzaLiczba) const
{
	return getReal() <= duzaLiczba;
}
bool DuzaLiczbaZespolona::operator>= (const DuzaLiczba& duzaLiczba) const
{
	return getReal() >= duzaLiczba;
}

DuzaLiczbaZespolona DuzaLiczbaZespolona::operator- () const
{
	return DuzaLiczbaZespolona(-getReal(), -getImagine());
}

const DuzaLiczba& DuzaLiczbaZespolona::getReal() const
{
	return *real;
}
const DuzaLiczba& DuzaLiczbaZespolona::getImagine() const
{
	return *imagine;
}

char* DuzaLiczbaZespolona::Wartosc() const
{
	return getReal().Wartosc();
}

void DuzaLiczbaZespolona::show(ostream& out)
{
	out << *this;
}