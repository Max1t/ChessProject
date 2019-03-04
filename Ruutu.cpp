#include "stdafx.h"
#include "Ruutu.h"


Ruutu::Ruutu(int rivi, int sarake)
{
	_rivi = rivi;
	_sarake = sarake;
}

int Ruutu::getRivi()
{
	return _rivi;
}

int Ruutu::getSarake()
{
	return _sarake;
}

bool Ruutu::operator==(Ruutu &ruutu)
{
	if(this->getRivi() == ruutu.getRivi() && this->getSarake() == ruutu.getSarake())
	{
		return true;
	}
	else return false;
}