#pragma once

class Ohestaly�nti
{
public:
	int getLy�ntiRivi() { return _ly�ntiRivi; }
	int getLy�ntiSarake() { return _ly�ntiSarake; }
	int getKohdeRivi() { return _kohdeRivi; }
	int getKohdeSarake() { return _kohdeSarake; }
	bool onkoOhestaMahdollinen() { return _onkoOhestaMahdollinen; }

	void setLy�ntiRivi(int arvo) { _ly�ntiRivi = arvo; }
	void setLy�ntiSarake(int arvo) { _ly�ntiSarake = arvo; }
	void setKohdeRivi(int arvo) { _kohdeRivi = arvo; }
	void setKohdeSarake(int arvo) { _kohdeSarake = arvo; }
	void setOnkoOhestaMahdollinen(bool arvo) { _onkoOhestaMahdollinen = arvo; }

private:
	int _ly�ntiRivi = 0; // Ruudun rivi jonka voi ohestaly�d�
	int _ly�ntiSarake = 0; // Ruudun sarake jonka voi ohestaly�d�
	int _kohdeRivi = 0; // Kohde ruudun rivi jossa on poistettava sotilas
	int _kohdeSarake = 0; // Kohde ruudun sarake jossa on poistettava sotilas
	bool _onkoOhestaMahdollinen = false; // Onko ohestaly�nti mahdollista t�ll� hetkell�
};