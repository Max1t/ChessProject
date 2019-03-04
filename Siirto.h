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
	Siirto(bool lyhytLinna, bool pitk‰Linna);
	Ruutu getAlkuruutu();
	Ruutu getLoppuruutu();
	bool onkoLyhytLinna();
	bool onkoPitkaLinna();
	void printSiirto();


private:
	Ruutu _alkuruutu;
	Ruutu _loppuRuutu;
	int miksiKorotetaan = 0;
	bool _lyhytLinna = false;
	bool _pitkaLinna = false;
};

