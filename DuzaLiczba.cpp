#include "stdafx.h"
#include "DuzaLiczba.h"
#include "funkcjeStrumieniowe.h"
#include <iostream>

using namespace std;

const DuzaLiczba DuzaLiczba::ZERO = DuzaLiczba(0);
const DuzaLiczba DuzaLiczba::JEDEN = DuzaLiczba(1);

DuzaLiczba::DuzaLiczba(int liczba) {
	
	if (liczba == 0)
	{
		dlugoscWartosci = 2;
		wartosc = new char[2]{ '0', '\0' };
		return;
	}

	bool ujemna;
	if (liczba < 0)
	{
		ujemna = true;
		liczba *= -1;
	}
	else {
		ujemna = false;
	}
	char* tmp = new char[12];	// int ma max 10 cyfr + bit znaku + '\0'
	size_t i = 0;
	// tmp dodaje kolejne elementy w odwroconej kolejnosci
	tmp[i++] = '\0';	// najpierw koniec char*
	while (liczba)
	{
		tmp[i++] = liczba % 10 + '0';	// pozniej cyfra po cyfrze
		liczba /= 10;
	}
	if (ujemna) tmp[i++] = '-';		// na koncu ewentualny minus
	dlugoscWartosci = i;
	wartosc = new char[dlugoscWartosci];
	for (size_t j = 0; j < dlugoscWartosci; ++j)		// przepisanie odwroconego tmp do atrubutu wartosc
	{
		wartosc[j] = tmp[dlugoscWartosci - j - 1];
	}
	delete[] tmp;
}
DuzaLiczba::DuzaLiczba(const char* const wyraz) {
	dlugoscWartosci = strlen(wyraz) + 1;
	wartosc = new char[dlugoscWartosci];
	strcpy_s(wartosc, dlugoscWartosci, wyraz);
	validacja();
	trim();
}
DuzaLiczba::DuzaLiczba(const DuzaLiczba& duzaLiczba) {
	dlugoscWartosci = duzaLiczba.dlugoscWartosci;
	wartosc = new char[dlugoscWartosci];
	strcpy_s(wartosc, dlugoscWartosci, duzaLiczba.wartosc);
	validacja();
}
DuzaLiczba::~DuzaLiczba() {
	delete[] wartosc;
	wartosc = nullptr;
	dlugoscWartosci = 0;
}

DuzaLiczba & DuzaLiczba::operator= (const DuzaLiczba & duzaLiczba) {

	if (this != &duzaLiczba)
	{
		realokuj(duzaLiczba.dlugoscWartosci);
		strcpy_s(wartosc, duzaLiczba.dlugoscWartosci, duzaLiczba.wartosc);

		validacja();
	}
	return *this;
}

DuzaLiczba DuzaLiczba::operator+ (const DuzaLiczba & duzaLiczba) const
{

	validacja();
	duzaLiczba.validacja();
	
	if (czyDodatnia() && duzaLiczba.czyDodatnia())
		return sumaDodatnich(*this, duzaLiczba);

	if (czyUjemna() && duzaLiczba.czyUjemna())
		return -sumaDodatnich(-*this, -duzaLiczba);
	
	if (czyBezwzglednieWieksza(duzaLiczba))
	{ 
		if (czyDodatnia() && duzaLiczba.czyUjemna())
			return dodatniaWieksza_Minus_DodatniaMniejsza(*this, -duzaLiczba);

		if (czyUjemna() && duzaLiczba.czyDodatnia())
			return -dodatniaWieksza_Minus_DodatniaMniejsza(-*this, duzaLiczba);
	}
	
	if (czyRownaLubBezwglednieMniejsza(duzaLiczba))
	{
		if (duzaLiczba.czyUjemna() && czyDodatnia())
			return -dodatniaWieksza_Minus_DodatniaMniejsza(-duzaLiczba, *this);
		if (duzaLiczba.czyDodatnia() && czyUjemna())
			return dodatniaWieksza_Minus_DodatniaMniejsza(duzaLiczba, -*this);
	}
	throw "Wystapil nieoczekiwany blad: operator + ";
}

bool DuzaLiczba::czyDodatnia() const
{
	return wartosc[0] != '-';
}
bool DuzaLiczba::czyUjemna() const
{
	return wartosc[0] == '-';
}

DuzaLiczba DuzaLiczba::sumaDodatnich(const DuzaLiczba& duzaLiczba1, const DuzaLiczba & duzaLiczba2) const
{
	DuzaLiczba wynik;
		
	// przy dodawaniu dlugosc wynikowa moze byc maksymalnie o 1 wieksza od wiekszej z dlugosci
	size_t dlugoscWyniku;
	if (duzaLiczba1.dlugoscWartosci > duzaLiczba2.dlugoscWartosci)
		dlugoscWyniku = duzaLiczba1.dlugoscWartosci + 1;
	else dlugoscWyniku = duzaLiczba2.dlugoscWartosci + 1;

	wynik.realokuj(dlugoscWyniku);

	int mod = 0;
	for (size_t i = 2; i <= wynik.dlugoscWartosci; ++i)
	{
		int lewaCyfra;
		if (i <= duzaLiczba1.dlugoscWartosci)
			lewaCyfra = duzaLiczba1.wartosc[duzaLiczba1.dlugoscWartosci - i] - '0';
		else lewaCyfra = 0;

		int prawaCyfra;
		if (i <= duzaLiczba2.dlugoscWartosci)
			prawaCyfra = duzaLiczba2.wartosc[duzaLiczba2.dlugoscWartosci - i] - '0';
		else prawaCyfra = 0;

		wynik.wartosc[wynik.dlugoscWartosci - i] = ((lewaCyfra + prawaCyfra + mod) % 10) + '0';
		mod = (lewaCyfra + prawaCyfra + mod) / 10;
	}
	wynik.trim();
	return wynik;
}
DuzaLiczba DuzaLiczba::dodatniaWieksza_Minus_DodatniaMniejsza(const DuzaLiczba &duzaLiczba1, const DuzaLiczba & duzaLiczba2) const
{
	DuzaLiczba wynik;

	// przy odejmowaniu liczb dodatnich dlugosc wynikowa moze byc maksymalnie dlugosci wiekszej z liczb
	wynik.realokuj(duzaLiczba1.dlugoscWartosci);

	int mod = 0;
	for (size_t i = 2; i <= wynik.dlugoscWartosci; ++i)
	{
		int lewaCyfra = duzaLiczba1.wartosc[duzaLiczba1.dlugoscWartosci - i] - '0' + mod;

		int prawaCyfra;
		if (i <= duzaLiczba2.dlugoscWartosci)
			prawaCyfra = duzaLiczba2.wartosc[duzaLiczba2.dlugoscWartosci - i] - '0';
		else prawaCyfra = 0;

		if (lewaCyfra < 0 || lewaCyfra < prawaCyfra)
		{
			mod = -1;
			lewaCyfra += 10;
		}
		else mod = 0;
		wynik.wartosc[wynik.dlugoscWartosci - i] = lewaCyfra - prawaCyfra + '0';
	}
	wynik.trim();
	return wynik;
}

DuzaLiczba DuzaLiczba::operator- (const DuzaLiczba & duzaLiczba) const {
	
	return *this + (-duzaLiczba);
}

DuzaLiczba DuzaLiczba::operator* (const DuzaLiczba & duzaLiczba) const 
{	
	validacja();
	duzaLiczba.validacja();

	if (czyDodatnia() && duzaLiczba.czyDodatnia())
		return mnozenieLiczbDodatnich(*this, duzaLiczba);

	if (czyUjemna() && duzaLiczba.czyUjemna())
		return mnozenieLiczbDodatnich(-*this, -duzaLiczba);

	if (czyDodatnia() && duzaLiczba.czyUjemna())
		return -mnozenieLiczbDodatnich(*this, -duzaLiczba);
	
	if (czyUjemna() && duzaLiczba.czyDodatnia())
		return -mnozenieLiczbDodatnich(-*this, duzaLiczba);	
	
	throw "Wystapil nieoczekiwany blad: operator * ";
}

DuzaLiczba DuzaLiczba::mnozenieLiczbDodatnich(const DuzaLiczba & duzaLiczba1, const DuzaLiczba & duzaLiczba2) const
{
	DuzaLiczba wynik = ZERO;

	for (size_t i = 2; i <= duzaLiczba1.dlugoscWartosci; ++i)
	{
		int lewaCyfra = wartosc[dlugoscWartosci - i] - '0';
		wynik += mnozenieLiczbyDodatniejPrzezCyfre(duzaLiczba2, lewaCyfra, i - 2);
	}
	wynik.trim();

	return wynik;
}
DuzaLiczba DuzaLiczba::mnozenieLiczbyDodatniejPrzezCyfre(const DuzaLiczba & duzaLiczba,const int cyfra, const size_t offset) const
{
	DuzaLiczba wynik;
	
	// przy mnozeniu liczby przez cyfre, dlugosc wyniku moze byc maksymalnie o jeden wieksza od liczby, dodaje jeszcze przesuniecie (ktora cyfra od prawej)
	size_t dlugoscWyniku = duzaLiczba.dlugoscWartosci + 1 + offset;
	
	wynik.realokuj(dlugoscWyniku);
	
	// zeruje cyfry offsetu
	for (size_t i = wynik.dlugoscWartosci - 2; i >= wynik.dlugoscWartosci - offset - 1; --i)
		wynik.wartosc[i] = '0';
	
	int mod = 0;
	for (size_t i = 2; i <= duzaLiczba.dlugoscWartosci + 1; ++i)
	{
		int prawaCyfra;
		if (i <= duzaLiczba.dlugoscWartosci)
			prawaCyfra = duzaLiczba.wartosc[duzaLiczba.dlugoscWartosci - i] - '0';
		else prawaCyfra = 0;
		
		wynik.wartosc[wynik.dlugoscWartosci - i - offset] = ((cyfra * prawaCyfra + mod) % 10) + '0';
		mod = (cyfra * prawaCyfra + mod) / 10;
	}
	wynik.trim();
	return wynik;
}

DuzaLiczba DuzaLiczba::operator/ (const DuzaLiczba & duzaLiczba) const
{
	validacja();
	duzaLiczba.validacja();

	if (czyDodatnia() && duzaLiczba.czyDodatnia())
		return dzielenieLiczbDodatnich(*this, duzaLiczba);

	if (czyUjemna() && duzaLiczba.czyUjemna())
		return dzielenieLiczbDodatnich(-*this, -duzaLiczba);

	if (czyDodatnia() && duzaLiczba.czyUjemna())
		return -dzielenieLiczbDodatnich(*this, -duzaLiczba);

	if (czyUjemna() && duzaLiczba.czyDodatnia())
		return -dzielenieLiczbDodatnich(-*this, duzaLiczba);
	
	throw "Wystapil nieoczekiwany blad: operator / ";
}

DuzaLiczba DuzaLiczba::dzielenieLiczbDodatnich(const DuzaLiczba &duzaLiczba1, const DuzaLiczba& duzaLiczba2) const
{
	if (duzaLiczba1 < duzaLiczba2)
		return ZERO;
	
	if (duzaLiczba2 == ZERO)
	{
		throw "Nie wolno dzielic przez zero!!!";
	}
	
	DuzaLiczba wynik;
	
	// przy dzieleniu, wynik moze miec maksymalnie dlugosc pierwszej liczby (dzielnej)
	wynik.realokuj(duzaLiczba1.dlugoscWartosci);

	// zerowanie tablicy wynikow
	for (size_t i = 0; i < wynik.dlugoscWartosci - 1; ++i)
	{
		wynik.wartosc[i] = '0';
	}

	DuzaLiczba czescDzielnej;
	DuzaLiczba backupCzesciDzielnej;
	
	backupCzesciDzielnej.realokuj(duzaLiczba2.dlugoscWartosci - 1);

	for (size_t i = 0; i < backupCzesciDzielnej.dlugoscWartosci - 1; ++i)
	{
		backupCzesciDzielnej.wartosc[i] = duzaLiczba1.wartosc[i];
	}

	for (size_t i = duzaLiczba2.dlugoscWartosci - 2; i < duzaLiczba1.dlugoscWartosci - 1; ++i)
	{
		czescDzielnej.realokuj(backupCzesciDzielnej.dlugoscWartosci + 1);

		for (size_t j = 0; j < backupCzesciDzielnej.dlugoscWartosci - 1; ++j)
		{
			czescDzielnej.wartosc[j] = backupCzesciDzielnej.wartosc[j];
		}
		czescDzielnej.wartosc[czescDzielnej.dlugoscWartosci - 2] = duzaLiczba1.wartosc[i];
		czescDzielnej.trim();
		
		int krotnosc = -1;
		while (czescDzielnej >= ZERO)
		{
			++krotnosc;
			czescDzielnej -= duzaLiczba2;
		}

		if (krotnosc == -1) krotnosc = 0;
		wynik.wartosc[i] = krotnosc + '0';
		czescDzielnej += duzaLiczba2;
		backupCzesciDzielnej = czescDzielnej;
	}
	
	wynik.trim();
	return wynik;
}

DuzaLiczba & DuzaLiczba::operator+= (const DuzaLiczba & duzaLiczba) {
	*this = *this + duzaLiczba;
	return *this;
}
DuzaLiczba & DuzaLiczba::operator-= (const DuzaLiczba & duzaLiczba) {
	*this = *this - duzaLiczba;
	return *this;
}
DuzaLiczba & DuzaLiczba::operator*= (const DuzaLiczba & duzaLiczba) {
	*this = *this * duzaLiczba;
	return *this;
}
DuzaLiczba & DuzaLiczba::operator/= (const DuzaLiczba & duzaLiczba) {
	*this = *this / duzaLiczba;
	return *this;
}

bool DuzaLiczba::operator== (const DuzaLiczba & duzaLiczba) const{

	validacja();
	duzaLiczba.validacja();

	if (czyDodatnia() && duzaLiczba.czyDodatnia())
	{
		if (dlugoscWartosci != duzaLiczba.dlugoscWartosci) return false;
		return !strcmp(wartosc, duzaLiczba.wartosc);
	}

	if (czyUjemna() && duzaLiczba.czyUjemna())
	{
		if (dlugoscWartosci != duzaLiczba.dlugoscWartosci) return false;
		return !strcmp(wartosc + 1, duzaLiczba.wartosc + 1);
	}

	if (czyDodatnia() && duzaLiczba.czyUjemna())
		return false;

	if (czyUjemna() && duzaLiczba.czyDodatnia())
		return false;

	throw "Wystapil nieoczekiwany blad: operator == ";
}
bool DuzaLiczba::operator!= (const DuzaLiczba & duzaLiczba) const {
	return !(*this == duzaLiczba);
}

bool DuzaLiczba::operator> (const DuzaLiczba & duzaLiczba) const
{
	validacja();
	duzaLiczba.validacja();

	if (czyDodatnia() && duzaLiczba.czyDodatnia())
	{
		if (dlugoscWartosci > duzaLiczba.dlugoscWartosci) return true;
		if (dlugoscWartosci < duzaLiczba.dlugoscWartosci) return false;
		return strcmp(wartosc, duzaLiczba.wartosc) > 0;
	}
	
	if (czyUjemna() && duzaLiczba.czyUjemna())
	{
		if (dlugoscWartosci > duzaLiczba.dlugoscWartosci) return false;
		if (dlugoscWartosci < duzaLiczba.dlugoscWartosci) return true;
		return strcmp(wartosc, duzaLiczba.wartosc) < 0;
	}

	if (czyDodatnia() && duzaLiczba.czyUjemna())
		return true;
	
	if (czyUjemna() && duzaLiczba.czyDodatnia())
		return false;

	throw "Wystapil nieoczekiwany blad: operator > ";
}

bool DuzaLiczba::operator< (const DuzaLiczba & duzaLiczba) const
{
	validacja();
	duzaLiczba.validacja();

	if (czyDodatnia() && duzaLiczba.czyDodatnia())
	{
		if (dlugoscWartosci > duzaLiczba.dlugoscWartosci) return false;
		if (dlugoscWartosci < duzaLiczba.dlugoscWartosci) return true;
		return strcmp(wartosc, duzaLiczba.wartosc) < 0;
	}
	
	if (czyUjemna() && duzaLiczba.czyUjemna())
	{
		if (dlugoscWartosci > duzaLiczba.dlugoscWartosci) return true;
		if (dlugoscWartosci < duzaLiczba.dlugoscWartosci) return false;
		return strcmp(wartosc + 1, duzaLiczba.wartosc + 1) > 0;
	}
	
	if (czyDodatnia() && duzaLiczba.czyUjemna())
		return false;
	
	if (czyUjemna() && duzaLiczba.czyDodatnia())
		return true;

	throw "Wystapil nieoczekiwany blad: operator < ";
}

bool DuzaLiczba::operator>= (const DuzaLiczba & duzaLiczba) const {
	return !(*this < duzaLiczba);
}

bool DuzaLiczba::operator<= (const DuzaLiczba & duzaLiczba) const
{
	return !(*this > duzaLiczba);
}

DuzaLiczba DuzaLiczba::operator- () const {
	
	validacja();
	
	if (*this == ZERO) return *this;

	DuzaLiczba wynik;
	
	if (czyDodatnia())
	{
		wynik.realokuj(dlugoscWartosci + 1);
		wynik.wartosc[0] = '-';
		strcpy_s(wynik.wartosc + 1, dlugoscWartosci, wartosc);

	}
	if (czyUjemna())
	{
		wynik.realokuj(dlugoscWartosci - 1);
		strcpy_s(wynik.wartosc, wynik.dlugoscWartosci, wartosc + 1);
	}
	
	return wynik;
}

DuzaLiczba DuzaLiczba::silniaRekurencyjna(const DuzaLiczba& dl) const
{
	if (dl == ZERO)
		return JEDEN;
	return dl * silniaRekurencyjna(dl - 1);
}

DuzaLiczba DuzaLiczba::operator! () const{
	
	validacja();
	
	// silnia rekurencyjna - dziala szybko, ale przerywa dzialanie programu przy zbyt duzych liczbach (przepelnienie stosu)
	DuzaLiczba wynik = silniaRekurencyjna(*this);

	// silnia iteracyjna - dziala dlugo, ale nie przepelnia pamieci przy bardzo duzych liczbach
	
	/*DuzaLiczba wynik = *this;
	for (DuzaLiczba i = *this - 1; i > JEDEN; i -= JEDEN)
	{
		wynik *= i;
	}*/
	
	return wynik;
}

char* DuzaLiczba::Wartosc() const
{
	return wartosc;
}

void DuzaLiczba::realokuj(const size_t size)
{
	delete[] wartosc;
	dlugoscWartosci = size;
	wartosc = new char[dlugoscWartosci];
	wartosc[dlugoscWartosci - 1] = '\0';
}

void DuzaLiczba::trim()
{
	if (dlugoscWartosci <= 2) return;

	size_t znak;
	if (czyDodatnia())
	{
		znak = 0;
	}
	else {
		znak = 1;
	}
	size_t offset = 0;
	while (wartosc[offset + znak] == '0') ++offset;

	if (offset == 0) return;

	if (offset == dlugoscWartosci - 1 - znak && wartosc[dlugoscWartosci - 2] == '0')
	{
		realokuj(2);
		wartosc[0] = '0';
		return;
	}

	size_t nowaDlugosc = dlugoscWartosci - offset;
	char * nowaWartosc = new char[nowaDlugosc];
	if (znak == 1) nowaWartosc[0] = '-';
	strcpy_s(nowaWartosc + znak, nowaDlugosc - znak, wartosc + offset + znak);
	
	delete[] wartosc;
	wartosc = nowaWartosc;
	dlugoscWartosci = nowaDlugosc;
}

bool DuzaLiczba::czyBezwzglednieWieksza(const DuzaLiczba& duzaLiczba) const
{
	size_t znak1;
	if (czyDodatnia())
		znak1 = 0;
	else znak1 = 1;

	size_t znak2;
	if (duzaLiczba.czyDodatnia())
		znak2 = 0;
	else znak2 = 1;

	if (dlugoscWartosci - znak1 > duzaLiczba.dlugoscWartosci - znak2) return true;
	if (dlugoscWartosci - znak1 < duzaLiczba.dlugoscWartosci - znak2) return false;

	for (size_t i = 0; i < dlugoscWartosci - znak1; ++i)
	{
		if (wartosc[i + znak1] > duzaLiczba.wartosc[i + znak2]) return true;
		if (wartosc[i + znak1] < duzaLiczba.wartosc[i + znak2]) return false;
	}
	return false;

}

bool DuzaLiczba::czyRownaLubBezwglednieMniejsza(const DuzaLiczba & duzaLiczba) const
{
	return !czyBezwzglednieWieksza(duzaLiczba);
}

void DuzaLiczba::validacja() const
{
	if (dlugoscWartosci < 2) throw "Nieprawidlowa liczba: za krotka ";
	if (wartosc == nullptr) throw "Nieprawdlowa liczba: brak liczby ";
	if (wartosc[dlugoscWartosci - 1] != '\0') throw "Nieprawidlowa liczba: brak znaku NULL na koncu liczby ";
	
	size_t znak;
	if (czyDodatnia()) znak = 0;
	else znak = 1;
	
	if (wartosc[znak] == '0' && dlugoscWartosci > 2) throw "Nieprawidlowa liczba: zera wiodace lub \"-0\" ";
	for (size_t i = znak; i < dlugoscWartosci - 1; ++i)
	{
		if (wartosc[i] < '0' || wartosc[i] > '9')
			throw "Nieprawidlowa liczba: liczba moze miec tylko cyfry i opcjonalny znak '-' na poczatku ";
	}
}

void DuzaLiczba::show(ostream& out)
{
	out << *this;
}