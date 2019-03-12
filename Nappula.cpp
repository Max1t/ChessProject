#include"stdafx.h"
#include "Nappula.h" 


Nappula::Nappula(std::wstring code, int vari, int koodi)
{
	setUnicode(code);
	setKoodi(koodi);
	setVari(vari);
}


void Nappula::setKoodi(int koodi) {
	_koodi = koodi;
}

int Nappula::getKoodi() {
	return _koodi;
}

void Nappula::setUnicode(std::wstring code) {
	_unicode = code;
}

std::wstring Nappula::getUnicode() {
	return _unicode;
}
void Nappula::setVari(int vari) {
	_vari = vari;
}

int Nappula::getVari() {
	return _vari;
}