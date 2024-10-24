#define _STD_SECURE_NOW_WARNINGS	
#define N 4

#include <iostream>
#include <assert.h>
#include <ctime>

using namespace std;

double randdouble() {
	//srand(time(NULL));
	double pom = rand() / (double(RAND_MAX) + 1) * 10;
	return pom;
}
template <typename T>
class lista;

template <typename T>
class element {
public:
	T wartosc;

	element<T>* nast;

	static int ID;
	element(); 
	~element();

	template <typename T>
	friend class lista;
};
template <typename T>
int element<T>::ID = 0;

template <typename T>
element<T>::element() { wartosc = 0, nast = NULL, ID++; }

template <typename T>
element<T>::~element() { delete nast; }

template <typename T>
class lista {
public:
	element<T>* glowa;
	element<T>* wsk;
	int count;

	lista();
	~lista();
	void push(int amount);
};

template <typename T>
lista<T>::lista() { glowa = wsk = NULL, count = 0; }

template <typename T>
lista<T>::~lista() {
	if (glowa != NULL) delete glowa;
	/*element<T>* usuw;

	while (glowa != wsk) {
		usuw = glowa;
		glowa = glowa->nast;
		delete usuw;
	}
	delete wsk;*/
}


template <typename T>
void lista<T>::push(int amount) { // dodaj "amount" elementow do listy o wartosci randdouble
	count += amount;
	for (int i = 0; i < amount; i++) {
		if (glowa == NULL) {
			glowa = wsk = new element<T>;
			glowa->wartosc = randdouble();
		}
		else {
			wsk->nast = new element<T>;
			wsk->nast->wartosc = randdouble();
			wsk = wsk->nast;
			wsk->nast = NULL;
		}
	}
}

template<typename T, template<typename> class Seq >
class Kontener {
	Seq<T> seq;
public:
	void append(int how_much){ seq.push(how_much); }
	
	class iterator {
		Kontener<T,Seq>& s;
		int index;
	public:
		iterator(Kontener<T, Seq>& is) : s(is), index(0) {}
		iterator(Kontener<T, Seq>& is, bool) : s(is), index(s.seq.count) {}
		//iterator(T) : s(is) {}
		element<T>* operator++() { // Prefix
			assert(index < s.seq.count);
			element<T>* pom = s.seq.glowa;
			for (int i = 0; i < index; i++) {
				pom = pom->nast;
			}
			index++;
			return pom;
		}
		element<T>* operator++(int) { // Postfix
			assert(index < s.seq.count);
			index++;
			element<T>* pom = s.seq.glowa;
			for (int i = 0; i < index; i++) {
				pom = pom->nast;
			}
			return pom;
		}
		bool operator==(const iterator& rv) const {
			return index == rv.index;
		}
		bool operator!=(const iterator& rv) const {
			return index != rv.index;
		}
		T operator*() const {
			element<T>* pom = s.seq.glowa;
			for (int i = 0; i < index; i++) {
				pom = pom->nast;
			}
			return pom->wartosc;
		}
		iterator& operator=(const iterator& rv) { //index = rv.index; return *this;
			element<T>* pom = s.seq.glowa;
			for (int i = 0; i < index; i++) {
				pom = pom->nast;
			}
			element<T>* pom2 = rv.s.seq.glowa;
			for (int i = 0; i < index; i++) {
				pom2 = pom2->nast;
			}
			assert(index == rv.index);

			pom->wartosc = pom2->wartosc;
			return *this;
		}
		
		/*friend iterator& operator=(iterator& lv, const iterator& rv) { 
			element<T>* pom = lv.s.seq.glowa;
			for (int i = 0; i < index; i++) {
				pom = pom->nast;
			}
			element<T>* pom2 = rv.s.seq.glowa;
			for (int i = 0; i < index; i++) {
				pom2 = pom2->nast;
			}
			assert(index == rv.index);

			pom->wartosc = pom2->wartosc;
			return *this;
		}*/

		iterator& operator=(const T& rv) { //iterator = T
			element<T>* pom = s.seq.glowa;
			for (int i = 0; i < index; i++) {
				pom = pom->nast;
			}
			pom->wartosc = rv;
			return *this;
		}
		iterator& operator+=(const T& rv) { //iterator += T
			element<T>* pom = s.seq.glowa;
			/*for (int i = 0; i < index; i++) {
				pom = pom->nast;
			}*/
			pom->wartosc = 0;
			index = 0;
			pom->wartosc += rv;
			return *this;
		}
		T operator-(const iterator& rv) { // iterator - iterator, z T
			element<T>* pom = s.seq.glowa;
			for (int i = 0; i < index; i++) {
				pom = pom->nast;
			}
			element<T>* pom2 = rv.s.seq.glowa;
			for (int i = 0; i < index; i++) {
				pom2 = pom2->nast;
			}
			assert(index == rv.index);

			return pom->wartosc - pom2->wartosc;
		}
		T operator*(const iterator& rv) { // iterator - iterator, z T
			element<T>* pom = s.seq.glowa;
			for (int i = 0; i < index; i++) {
				pom = pom->nast;
			}
			element<T>* pom2 = rv.s.seq.glowa;
			for (int i = 0; i < index; i++) {
				pom2 = pom2->nast;
			}
			assert(index == rv.index);

			return pom->wartosc * pom2->wartosc;
		}
		ostream& operator << (ostream& b) {
		
			return b << s.seq.glowa->wartosc;
		}
	};
	iterator begin() { return iterator(*this); }
	iterator end() { return iterator(*this, true); }
};

template<typename Iter>
void wypisz(Iter start, Iter end)
{
	while (start != end) {
		cout << *start << endl;
		start++;
	}
};

template<typename Iter>
Kontener<double, lista>::iterator Roznicuj1(Iter i1, Iter i2, Iter i3)
{
	Kontener<double, lista> K3;
	K3.append(N);
	Kontener<double, lista>::iterator pomD(K3);

	while (i1 != i2) {
		i1 = i1 - i3;

		pomD += *i1;

		i1++;
		i3++;

	}
	
	pomD = pomD * (1 / N);
	return pomD;
};

//template<typename Iter>
//double Roznicuj1(Iter i1, Iter i2, double d)
//{
//	double temp = 0, cnt = 0;
//
//	while (i1 != i2) {
//		i1 = i1 - i3;
//
//		temp += *i1;
//
//		i1++;
//		i3++;
//
//		cnt++;
//	}
//
//	temp = 1 / cnt * temp;
//	return temp;
//};

int main() {
	
	Kontener<double, lista> K1;
	K1.append(N);
	Kontener<double, lista>::iterator it1(K1);

	Kontener<double, lista> K2;
	K2.append(N);
	Kontener<double, lista>::iterator it2(K2);

	wypisz(K1.begin(), K1.end());
	cout << endl;
	wypisz(K2.begin(), K2.end());
	cout << endl;

	Kontener<double, lista>::iterator D(K1);
	D = Roznicuj1(K1.begin(), K1.end(), K2.begin());
	cout << "D: " << D << endl;


	return 0;
}