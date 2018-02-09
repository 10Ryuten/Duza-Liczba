#pragma once
#include "Liczba.h"
#include "DuzaLiczba.h"


class DuzaLiczbaZespolona : public Liczba
{
	DuzaLiczba *real;
	DuzaLiczba *imagine;

	static const DuzaLiczbaZespolona ZERO;

public:

	DuzaLiczbaZespolona(const int = 0, const int = 0);
	DuzaLiczbaZespolona(const char *, const char * = "0");
	DuzaLiczbaZespolona(const DuzaLiczba&, const DuzaLiczba&);
	DuzaLiczbaZespolona(const DuzaLiczbaZespolona&);
	~DuzaLiczbaZespolona();

	DuzaLiczbaZespolona& operator= (const DuzaLiczbaZespolona&);

	DuzaLiczbaZespolona operator+ (const DuzaLiczbaZespolona&) const;
	DuzaLiczbaZespolona operator- (const DuzaLiczbaZespolona&) const;
	DuzaLiczbaZespolona operator* (const DuzaLiczbaZespolona&) const;
	DuzaLiczbaZespolona operator/ (const DuzaLiczbaZespolona&) const;

	DuzaLiczbaZespolona& operator+= (const DuzaLiczbaZespolona&);
	DuzaLiczbaZespolona& operator-= (const DuzaLiczbaZespolona&);
	DuzaLiczbaZespolona& operator*= (const DuzaLiczbaZespolona&);
	DuzaLiczbaZespolona& operator/= (const DuzaLiczbaZespolona&);

	bool operator== (const DuzaLiczbaZespolona&) const;
	bool operator!= (const DuzaLiczbaZespolona&) const;
	bool operator< (const DuzaLiczba&) const;
	bool operator> (const DuzaLiczba&) const;
	bool operator<= (const DuzaLiczba&) const;
	bool operator>= (const DuzaLiczba&) const;

	DuzaLiczbaZespolona operator- () const;

	const DuzaLiczba& getReal() const;
	const DuzaLiczba& getImagine() const;

	virtual char* Wartosc() const;
	virtual void show(ostream&);
};

