#define _STD_SECURE_NOW_WARNINGS	

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class beg {
public:
	string begerr;

	beg() { begerr = "brak poczatku '<'"; };
	beg(string s) { begerr = s; };

};

class ende : public beg {
public:
	string enderr;

	ende() { enderr = "brak konca '>'"; };
	ende(string s) { enderr = s; };
};


class no_begg_error {
public:
	string info;
	no_begg_error() { info = "wystapil blad"; }
	no_begg_error(string s) { info = s; }
};
class no_end_error {
public:
	string info;
	no_end_error() { info = "wystapil blad"; }
	no_end_error(string s) { info = s; }
};
//class diff_tag_end_error {
//public:
//	string info;
//	diff_tag_end_error() { info = "wystapil blad"; }
//	diff_tag_end_error(string s) { info = s; }
//};

class element {

	string wartosc;
public:
	element* nast;
	element* poprz;
	element() { nast = NULL, poprz = NULL; }
	element(string s) { nast = NULL, poprz = NULL; wartosc = s; }
	~element() { delete nast; }
	//string get_wartosc(void) { return wartosc; }
	friend class stos;
	friend int sprawdz_tabele(ifstream& f);
};

class stos {
	element* glowa;
	element* wsk;
public:
	stos() { glowa = NULL, wsk = NULL; }
	~stos() {
		element* usuw;
		while (glowa != wsk) {
			usuw = glowa;
			glowa = glowa->nast;
			usuw->nast = NULL;
			delete usuw;
		}
		if (wsk != NULL) { delete wsk; }
	}
	void put(element& elem) {
		if (glowa == NULL) {
			glowa = wsk = new element;
			glowa->wartosc = elem.wartosc;
		}
		else {
			wsk->nast = new element;
			wsk->nast->wartosc = elem.wartosc;

			wsk->nast->poprz = wsk;
			wsk = wsk->nast;
		}
	}
	void get(void) {
		if (glowa == NULL);
		else if (glowa == wsk)  glowa = wsk = NULL;
		else {
			element* usuw = wsk;
			wsk = wsk->poprz;
			wsk->nast = NULL;
			delete usuw;

		}
	}
	friend int sprawdz_tabele(ifstream& f);
};

int sprawdz_tabele(ifstream& f) {
	stos STOS;
	int cont = 0;
	int nr_linii = 1;
	try {

		element* linia = new element;
		getline(f, linia->wartosc);

		size_t start_pos = linia->wartosc.find('<');

		if (start_pos == string::npos) { throw beg("Nie znaleziono znaku '<' w linii"); }//nie znaleziono ani jednego '<'

		else if (start_pos != string::npos) {				// znaleziono pierwszy '<'
			size_t end_pos = linia->wartosc.find('>'); //znajdz pierwsze wystapienie ">"
			if (end_pos == string::npos) { throw ende("Nie znaleziono znaku '>' w linii"); }	// nie ma konca taga ">"
			else {	///// znaleziono caly tag
				int len = end_pos - start_pos + 1;				// ustal odleglosc miedzy < oraz >
				string sub;
				if (linia->wartosc[start_pos + 1] == '/')  sub = linia->wartosc.substr(start_pos + 2, len - 3); // jesli w lini jest tylko </TAG>
				else { sub = linia->wartosc.substr(start_pos + 1, len - 2); }//stworz substring tak aby powstal tag z HTML

				if (sub == "TABLE") cont = 1;
				element temp(sub);				// substring z tagiem na stos
				STOS.put(temp);

				if (linia->wartosc.find('<', start_pos + 1) == string::npos && linia->wartosc.find('<', end_pos + 1 ) != string::npos) throw no_begg_error("Nie znaleziono znaku '<' w linii");
				if (linia->wartosc.find('<', start_pos + 1) != string::npos) {	// jesli da sie znalezc inne wystapienie'<'

					size_t pom_pos = start_pos; // od tego bedzie sprawdzal dalej
					start_pos = linia->wartosc.find('<', pom_pos + 1);
					pom_pos += end_pos; // zeby potem uzyc do find('>')
					if (start_pos == string::npos) { throw beg("Nie znaleziono znaku '<' w linii"); }		// nie znaleziono taga na drugim koncu linii mimo ze jest cos w tej linii wpisane
					else {
						size_t ukosnik_pos = start_pos + 1;
						if (linia->wartosc[ukosnik_pos] != '/');				//{ throw diff_tag_end_error("Koniec tagu powinien miec '/'"); }//inny operator niz '/'
						else {
							size_t end_pos = linia->wartosc.find('>', pom_pos + 1); //znajdz drugie wystapienie ">"
							if (end_pos == string::npos) { throw ende("Nie znaleziono znaku '>' w linii"); } //nie znaleziono drugiego '>'
							else {  /////// znaleziono caly tag
								int len = end_pos - start_pos + 1;				// ustal odleglosc miedzy < oraz >
								string sub = linia->wartosc.substr(start_pos + 2, len - 3); //stworz substring tak aby powstal tag z HTML

								element temp(sub);	// substring z tagiem na stos
								STOS.put(temp);
							}
						}
					}
				}
			}
		}
		if (cont != 1) {
			if (STOS.wsk->poprz == NULL) { //albo STOS.glowa->wartosc!=NULL && STOS.glowa->nast==NULL) czyli jest 1 element
				STOS.get();
				return 0;
			}
			else if (STOS.wsk->wartosc == STOS.wsk->poprz->wartosc) { // jesli dwa elementy na gorze stosu są takie same to usun je
				STOS.get();
				STOS.get();
			}
		}


	}
	catch (no_begg_error& my) {
		cout << my.info; exit(0);
	}
	catch (no_end_error& my) {
		cout << my.info; exit(0);
	}

	catch (beg& b) {

		cout << "linia nr " << nr_linii;
		throw;
	}


	try {
		while (f.good()) { // powtarzaj az do wyczerpania pliku
			nr_linii++;
			element* linia = new element;
			getline(f, linia->wartosc);

			size_t start_pos = linia->wartosc.find('<');

			if (start_pos == string::npos) { throw beg("Nie znaleziono znaku '<' w linii"); }//nie znaleziono ani jednego '<'

			else if (start_pos != string::npos) {				// znaleziono pierwszy '<'
				size_t end_pos = linia->wartosc.find('>'); //znajdz pierwsze wystapienie ">"
				if (end_pos < start_pos) throw beg("Nie znaleziono znaku '<' w linii");
				if (end_pos == string::npos) { throw ende("Nie znaleziono znaku '>' w linii"); }	// nie ma konca taga ">"
				else {	///// znaleziono caly tag
					int len = end_pos - start_pos + 1;				// ustal odleglosc miedzy < oraz >
					string sub;
					if (linia->wartosc[start_pos + 1] == '/')  sub = linia->wartosc.substr(start_pos + 2, len - 3); // jesli w lini jest tylko </TAG>
					else { sub = linia->wartosc.substr(start_pos + 1, len - 2); }//stworz substring tak aby powstal tag z HTML

					element temp(sub);				// substring z tagiem na stos
					STOS.put(temp);

					if (linia->wartosc.find('<', start_pos + 1) == string::npos && linia->wartosc.find('<', end_pos + 1) != string::npos) throw no_begg_error("Nie znaleziono znaku '<' w linii");
					if (linia->wartosc.find('<', start_pos + 1) != string::npos) {	// jesli da sie znalezc inne wystapienie'<'

						size_t pom_pos = start_pos; // od tego bedzie sprawdzal dalej
						start_pos = linia->wartosc.find('<', pom_pos + 1);
						pom_pos += end_pos; // zeby potem uzyc do find('>')
						if (start_pos == string::npos) { throw beg("Nie znaleziono znaku '<' w linii"); }		// nie znaleziono taga na drugim koncu linii mimo ze jest cos w tej linii wpisane
						else {
							size_t ukosnik_pos = start_pos + 1;
							if (linia->wartosc[ukosnik_pos] != '/');				//{ throw diff_tag_end_error("Koniec tagu powinien miec '/'"); }//inny operator niz '/'
							else {
								size_t end_pos = linia->wartosc.find('>', pom_pos + 1); //znajdz drugie wystapienie ">"
								if (end_pos == string::npos) { throw ende("Nie znaleziono znaku '>' w linii"); } //nie znaleziono drugiego '>'
								else {  /////// znaleziono caly tag
									int len = end_pos - start_pos + 1;				// ustal odleglosc miedzy < oraz >
									string sub = linia->wartosc.substr(start_pos + 2, len - 3); //stworz substring tak aby powstal tag z HTML

									element temp(sub);	// substring z tagiem na stos
									STOS.put(temp);
								}
							}
						}
					}
				}
			}
			if (STOS.wsk->poprz == NULL); // jesli nie ma 2 elementow to nie ma co porownywac
			else if (STOS.wsk->wartosc == STOS.wsk->poprz->wartosc) { // jesli dwa elementy na gorze stosu są takie same to usun je
				STOS.get();
				STOS.get();
			}

		}
		if (STOS.glowa == NULL) cout << "TO JEST TABLICA" << endl;

	}
	catch (no_begg_error& my) {
		cout << my.info; exit(0);
	}
	catch (no_end_error& my) {
		cout << my.info; exit(0);
	}
	/*catch (diff_tag_end_error& my) {
		cout << my.info; exit(0);
	}*/
	catch (beg& b) {

		cout << "linia nr " << nr_linii;
		throw;
	}
}

int main(char argc, int* argv) {

	ifstream in("dane.txt");
	try {
		sprawdz_tabele(in);
	}
	catch (ende& e) {
		cout << e.enderr;
	}
	catch (beg& b) {
		cout << b.begerr;
	}

	return 0;
}