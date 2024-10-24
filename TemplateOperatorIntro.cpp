#include<iostream>
#include<fstream>
#include<string>
#include<limits>
#include<exception>
#include<math.h>

using namespace std;

class _Bazowe_Cechy {
public:
	// pola statyczne stałe - dla stałych wartości całkowitych
	static const bool _jest_liczba = false;
	static const bool _nalezy_do_przedzialu = false;
	static const bool _jest_liczba_calkowita = false;
	static const bool _wypisz_4_cyfry_po_przecinku = false;
};

template<typename T>
class _Cechy : public _Bazowe_Cechy {
public:
	// metody statyczne - dla wartości innych typów niż liczby całkowite
	static const T _dolna_granica() { return T(); };
	static const T _gorna_granica() { return T(); };
};

template<typename T>
class Cechy : public _Cechy<T> {
};

class przyspieszenie {
	double a;
public:
	przyspieszenie(double acc = 0) : a(acc) {};
	double operator()() const { return a; };
	przyspieszenie& operator=(double acc) { a = acc; return *this; };
	bool operator<(const przyspieszenie& p) const { return (a < p.a); };
	friend ostream& operator<<(ostream& os, const przyspieszenie&);
};
ostream& operator<<(ostream& os, const przyspieszenie& p) { return os << p.a; };

template<>
class Cechy<przyspieszenie> : public _Cechy<przyspieszenie> {
public:
	static const bool _jest_liczba = true;
};

class temperatura_wody {
	double t;
public:
	temperatura_wody(double temp = 50) : t(temp) {};
	double operator()() const { return t; };
	temperatura_wody& operator=(double temp) { t = temp; return *this; };
	bool operator<(const temperatura_wody& tw) const { return (t < tw.t); };
	friend ostream& operator<<(ostream& os, const temperatura_wody&);
};
ostream& operator<<(ostream& os, const temperatura_wody& tw) { return os << tw.t; };

template<>
class Cechy<temperatura_wody> : public _Cechy<temperatura_wody> {
public:
	static const bool _jest_liczba = true;
	static const bool _nalezy_do_przedzialu = true;
	static const temperatura_wody _dolna_granica() { return temperatura_wody(0); };
	static const temperatura_wody _gorna_granica() { return temperatura_wody(100); };
};

class kostka_do_gry {
	int n;
public:
	kostka_do_gry(int num = 1) : n(num) {};
	int operator()() const { return n; };
	kostka_do_gry& operator=(int num) { n = num; return *this; };
	bool operator<(const kostka_do_gry& k) const { return (n < k.n); };
	friend ostream& operator<<(ostream& os, const kostka_do_gry&);
};
ostream& operator<<(ostream& os, const kostka_do_gry& k) { return os << k.n; };

template<>
class Cechy<kostka_do_gry> : public _Cechy<kostka_do_gry> {
public:
	static const bool _jest_liczba = true;
	static const bool _nalezy_do_przedzialu = true;
	static const bool _jest_liczba_calkowita = true;
	static const kostka_do_gry _dolna_granica() { return kostka_do_gry(1); };
	static const kostka_do_gry _gorna_granica() { return kostka_do_gry(6); };
};

class minuta_dnia {
	int n;
public:
	
	minuta_dnia(int num=1) {
		if (num > 0 && num < 1440) n = num;
		else num = 123;
	};
	int operator()() const { return n; };
	minuta_dnia& operator=(int num) { n = num; return *this; };
	bool operator<(const minuta_dnia& k) const { return (n < k.n); };
	friend ostream& operator<<(ostream& os, const minuta_dnia&);
};

ostream& operator<<(ostream& os, const minuta_dnia& k) { return os << k.n; };

template<>
class Cechy<minuta_dnia> : public _Cechy<minuta_dnia> {
public:
	static const bool _jest_liczba = true;
	static const bool _nalezy_do_przedzialu = true;
	static const bool _jest_liczba_calkowita = true;
	static const minuta_dnia _dolna_granica() { return minuta_dnia(0); };
	static const minuta_dnia _gorna_granica() { return minuta_dnia(1440); };
};

class liczba_sekund {
	double n;
public:
	liczba_sekund(double num = 1.0) {
		if (abs(num - 0.8) < 0.001 || abs(num - 2.8) < 0.001 || abs(num - 4.8) < 0.001 ||
			abs(num - 6.8) < 0.001 || abs(num - 8.8) < 0.001 || abs(num - 10.8) < 0.001 ||
			abs(num - 12.8) < 0.001 || abs(num - 14.8) < 0.001 || abs(num - 16.8) < 0.001 ||
			abs(num - 18.8) < 0.001 || abs(num - 20.8) < 0.001 || abs(num - 22.8) < 0.001 ||
			abs(num - 24.8) < 0.001) {
			n = num;
		}
		else n = 1111.1111;
	};
	double operator()() const { return n; };
	liczba_sekund& operator=(double num) { n = num; return *this; };
	bool operator<(const liczba_sekund& k) const { return (n < k.n); };
	friend ostream& operator<<(ostream& os, const liczba_sekund&);
};

ostream& operator<<(ostream& os, const liczba_sekund& k) { return os << k.n; };

template<>
class Cechy<liczba_sekund> : public _Cechy<liczba_sekund> {
public:
	static const bool _jest_liczba = true;
	static const bool _nalezy_do_przedzialu = false;
	static const bool _jest_liczba_calkowita = false;
	static const bool _wypisz_4_cyfry_po_przecinku = true;
	static const liczba_sekund _dolna_granica() { return liczba_sekund(0); };
	static const liczba_sekund _gorna_granica() { return liczba_sekund(25); };
};

class ilosc_piwa {
	double n;
public:
	ilosc_piwa(double num = 1)  {
		if (num > 0) n = num * 0.568;	
	};
	double operator()() const { return n; };
	ilosc_piwa& operator=(double num) { n = num; return *this; };
	bool operator<(const ilosc_piwa& k) const { return (n < k.n); };
	friend ostream& operator<<(ostream& os, const ilosc_piwa&);
};

ostream& operator<<(ostream& os, const ilosc_piwa& k) { return os << k.n; };

template<>
class Cechy<ilosc_piwa> : public _Cechy<ilosc_piwa> {
public:
	static const bool _jest_liczba = true;
	static const bool _nalezy_do_przedzialu = false;
	static const bool _jest_liczba_calkowita = false;
	static const bool _wypisz_4_cyfry_po_przecinku = true;
	static const ilosc_piwa _dolna_granica() { return ilosc_piwa(0); };
	static const ilosc_piwa _gorna_granica() { return ilosc_piwa(157); };
};

class liczba_pierwsza {
	int n;
public:
	liczba_pierwsza(int num = 1)  {
		int count = 0;
		if (num > 2) {
			for (int i = 2; i < num; i++)
				if (num % i == 0) {
					n = 1111111;
				}
				else count++;
		}
		if (count == num - 2) n = num;
	};
	int operator()() const { return n; };
	liczba_pierwsza& operator=(int num) { n = num; return *this; };
	bool operator<(const liczba_pierwsza& k) const { return (n < k.n); };
	friend ostream& operator<<(ostream& os, const liczba_pierwsza&);
};

ostream& operator<<(ostream& os, const liczba_pierwsza& k) { return os << k.n; };

template<>
class Cechy<liczba_pierwsza> : public _Cechy<liczba_pierwsza> {
public:
	static const bool _jest_liczba = true;
	static const bool _nalezy_do_przedzialu = false;
	static const bool _jest_liczba_calkowita = true;
	static const liczba_pierwsza _dolna_granica() { return liczba_pierwsza(0); };
	static const liczba_pierwsza _gorna_granica() { return liczba_pierwsza(157); };
};

class Przepelnienie : public exception {
	char opis[100];
public:
	Przepelnienie(const char* o) { strcpy_s(opis, o); }
	const char* what() const throw() { return opis; };
};
class BrakDanych : public exception {
	char opis[100];
public:
	BrakDanych(const char* o) { strcpy_s(opis, o); }
	const char* what() const throw() { return opis; };
};

template<typename T, int rozmiar, typename CechyT = Cechy<T>>
class SzablonStosu {
	T stos[rozmiar];
	int top;
public:
	int zajetosc() { return top; };
	SzablonStosu() : top(0) {}
	void push(const T& i) {
		if (top == rozmiar)
			throw Przepelnienie(typeid(i).name());
		stos[top++] = i;
	}
	void push(int i) {
		if (top == rozmiar)
			throw Przepelnienie(typeid(i).name());

		
		// walidacja wartości przekazanej do zapisu
		if (CechyT::_jest_liczba && CechyT::_jest_liczba_calkowita) {
			if (CechyT::_nalezy_do_przedzialu) {
				if (!(T(i) < CechyT::_dolna_granica()) && !(CechyT::_gorna_granica() < T(i)))
					stos[top++] = i;
			}
			else
				stos[top++] = i;
		}
		
	}
	void push(double i) {
		if (top == rozmiar)
			throw Przepelnienie(typeid(i).name());

		// walidacja wartości przekazanej do zapisu
		if (CechyT::_jest_liczba && !CechyT::_jest_liczba_calkowita) {
			stos[top++] = i;
		}
			
	}
	T pop() {
		if (top == 0)
			throw BrakDanych(typeid(stos[0]).name());

		return stos[--top];
	}
	template<typename U1, int r, typename U2>
	friend ostream& operator<<(ostream& os, const SzablonStosu<U1, r, U2>&);
};
template<typename U1, int r, typename U2>
ostream& operator<<(ostream& os, const SzablonStosu<U1, r, U2>& S)
{
	cout.setf(ios::fixed);
	cout.precision(0);
	if (Cechy<U2>::_wypisz_4_cyfry_po_przecinku == true)
		cout.precision(4);
	for (int i = 0; i < S.top; i++) cout << S.stos[i] << endl;
	return os;
};

int main() {
	SzablonStosu<minuta_dnia, 5> K1;
	SzablonStosu<liczba_sekund, 10> K2;
	SzablonStosu<ilosc_piwa, 10> K3;
	SzablonStosu<liczba_pierwsza, 10> K4;
	//SzablonStosu<minuta_dnia, 10> K5;
	K1.push(minuta_dnia(50));
	K1.push(minuta_dnia(181));
	K1.push(116);
	cout << K1;
	cout << "Danych na stosie K1: " << K1.zajetosc() << endl << endl;

	K2.push(liczba_sekund(0.8));
	K2.push(liczba_sekund(2.8));
	K2.push(4.8);
	cout << K2;
	cout << "Danych na stosie K2: " << K2.zajetosc() << endl << endl;

	K3.push(ilosc_piwa(2));
	K3.push(ilosc_piwa(7));
	K3.push(10.0);
	cout << K3;
	cout << "Danych na stosie K3: " << K3.zajetosc() << endl << endl;

	K4.push(liczba_pierwsza(3));
	K4.push(liczba_pierwsza(17));
	K4.push(7);
	cout << K4;
	cout << "Danych na stosie K4: " << K4.zajetosc() << endl << endl;
	
	// opróżnianie stosów
	try {
		while (true)
			K1.pop();
	}
	catch (BrakDanych& e) {
		cout << "K1 pusty: " << e.what() << endl;
	}
	try {
		while (true)
			K2.pop();
	}
	catch (BrakDanych& e) {
		cout << "K2 pusty: " << e.what() << endl;
	}
	try {
		while (true)
			K3.pop();
	}
	catch (BrakDanych& e) {
		cout << "K3 pusty: " << e.what() << endl;
	}
	try {
		while (true)
			K4.pop();
	}
	catch (BrakDanych& e) {
		cout << "K4 pusty: " << e.what() << endl;
	}
	system("pause");
	return 0;
}