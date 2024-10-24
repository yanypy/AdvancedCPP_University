#define _STD_SECURE_NO_WARNINGS

#include <iostream>
#include <deque>
#include <vector>
#include <list>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

vector<vector<double>>* transpozycja(string plik) {

	ifstream str;					//pobieranie danych
	deque<deque<double>> Macierz;
	str.open(plik, ios::in);

	if (str.good()) {
		string line;
		while (getline(str, line)) {
			deque<double> pom;
			istringstream iss(line);
			double num;

			while (iss >> num) {
				pom.push_back(num);
			}
			Macierz.push_back(pom);
		}	
	}
	//transpozycja i zapis do wektora
	vector<vector<double>>* Transpoz = new vector<vector<double>>;
	
	int row_count = Macierz.size();
	int collumn_count = Macierz[0].size();

	for (int i = 0; i < collumn_count; i++) {
		vector<double> temp;
		for (int j = 0; j < row_count; j++) {
			temp.push_back(Macierz[j][i]);
		}
		Transpoz->push_back(temp);
	}
	return Transpoz;
}

void wypisz(vector<vector<double>>* Vector) {
	for (int i = 0; i < (*Vector).size(); i++) {
		for (int j = 0; j < (*Vector)[i].size(); j++) {
			cout << (*Vector)[i][j] << ' ';
		}
		cout << endl;
	}
	//vector<vector<double>>::iterator* it;
}

//template <class T>
//struct greater {
//	bool operator() (const T& x, const T& y) const {
//		return x > y;
//	};
//	typedef T first_argument_type;
//	typedef T second_argument_type;
//	typedef bool result_type;
//};

void sortowanie(string plik) {

	list<list<string>> lista;
	ifstream str;
	str.open(plik, ios::in);
	if (str.good()) {
		string line;
		while (getline(str, line)) {
			list<string> pom;
			istringstream iss(line);
			string slowo;
			while (iss >> slowo) {
				pom.push_back(slowo);
			}
			pom.sort();
			lista.push_back(pom);
		}
	}
	//scalanie
	list<string> scalona;
	list<string>::iterator scIT = scalona.begin();

	list<list<string>>::iterator It;
	for (It = lista.begin(); It != lista.end(); It++) {
		list<string> wew = *It;
		scalona.splice(scIT, wew);
		scIT = scalona.end();
		
	}
	for (scIT = scalona.begin(); scIT != scalona.end(); scIT++) {
		cout << *scIT << endl;
	}

	/*list<list<string>>::iterator It;
	for (It = lista.begin(); It != lista.end(); It++) {
		list<string> wew = *It;
		list<string>::iterator it;
		for (it = wew.begin(); it != wew.end(); it++) {
			cout << *it << endl;
		}
	}*/
}

int main() {

	vector<vector<double>>* Vector = transpozycja("dane.txt");
	wypisz(Vector);

	sortowanie("mistrz.txt");

	return 0;
}