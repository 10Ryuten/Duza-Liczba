#pragma once
#include "Liczba.h"

class DuzaLiczba : public Liczba
{
	char *wartosc;
	size_t dlugoscWartosci;

	static const DuzaLiczba ZERO;
	static const DuzaLiczba JEDEN;

	void realokuj(const size_t size);
	void trim();
	bool czyBezwzglednieWieksza(const DuzaLiczba& duzaLiczba) const;
	bool czyRownaLubBezwglednieMniejsza(const DuzaLiczba& duzaLiczba) const;
	bool czyDodatnia() const;
	bool czyUjemna() const;

	DuzaLiczba sumaDodatnich(const DuzaLiczba & duzaLiczba1, const DuzaLiczba & duzaLiczba2) const;
	DuzaLiczba dodatniaWieksza_Minus_DodatniaMniejsza(const DuzaLiczba & duzaLiczba1, const DuzaLiczba & duzaLiczba2) const;

	DuzaLiczba mnozenieLiczbDodatnich(const DuzaLiczba & duzaLiczba1, const DuzaLiczba & duzaLiczba2) const;
	DuzaLiczba mnozenieLiczbyDodatniejPrzezCyfre(const DuzaLiczba & duzaLiczba, const int cyfra, const size_t offset) const;

	DuzaLiczba dzielenieLiczbDodatnich(const DuzaLiczba& duzaLiczba1,const DuzaLiczba& duzaLiczba2) const;

	DuzaLiczba silniaRekurencyjna(const DuzaLiczba& dl) const;
	
	
public:

	DuzaLiczba(int liczba = 0);
	DuzaLiczba(const char* const wyraz);
	DuzaLiczba(const DuzaLiczba& duzaLiczba);
	~DuzaLiczba();

	DuzaLiczba & operator= (const DuzaLiczba & duzaLiczba);

	DuzaLiczba operator+ (const DuzaLiczba & duzaLiczba) const;
	DuzaLiczba operator- (const DuzaLiczba & duzaLiczba) const;
	
	DuzaLiczba operator* (const DuzaLiczba & duzaLiczba) const;
	
	DuzaLiczba operator/ (const DuzaLiczba & duzaLiczba) const;

	DuzaLiczba & operator+= (const DuzaLiczba & duzaLiczba);
	DuzaLiczba & operator-= (const DuzaLiczba & duzaLiczba);
	DuzaLiczba & operator*= (const DuzaLiczba & duzaLiczba);
	DuzaLiczba & operator/= (const DuzaLiczba & duzaLiczba);

	bool operator== (const DuzaLiczba & duzaLiczba) const;
	bool operator!= (const DuzaLiczba & duzaLiczba) const;
	bool operator> (const DuzaLiczba & duzaLiczba) const;
	bool operator< (const DuzaLiczba & duzaLiczba) const;
	bool operator>= (const DuzaLiczba & duzaLiczba) const;
	bool operator<= (const DuzaLiczba & duzaLiczba) const;

	DuzaLiczba operator- () const;
	DuzaLiczba operator! () const;

	void validacja() const;
	virtual char* Wartosc() const;
	virtual void show(ostream&);
};

