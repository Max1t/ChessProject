#pragma once


class Ruutu
{

public:
	Ruutu(int rivi, int sarake);
	Ruutu(){}
	int getRivi();
	int getSarake();
	bool operator == (Ruutu &ruutu);

private:
	int _sarake = 0;
	int _rivi = 0;

};

