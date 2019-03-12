#pragma once
#include "Ruutu.h"
#include <string>
#include <iostream>
using namespace std;

class Siirto
{
public:
	Siirto() {}
	Siirto(Ruutu, Ruutu);
	Siirto(Ruutu alku, Ruutu loppu, int korotus);
	Siirto(bool lyhytLinna, bool pitk‰Linna);
	Ruutu getAlkuruutu();
	Ruutu getLoppuruutu();
	bool onkoLyhytLinna();
	bool onkoPitkaLinna();
	void printSiirto();
	bool operator == (Siirto &ruutu);
	int getMiksiKorotetaan();
private:
	Ruutu _alkuruutu;
	Ruutu _loppuRuutu;
	int _miksiKorotetaan = 0;
	bool _lyhytLinna = false;
	bool _pitkaLinna = false;
};

