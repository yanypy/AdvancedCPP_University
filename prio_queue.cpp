#define _STD_SECURE_NO_WARNINGS

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <queue>
#include <list>

using namespace std;

template <class T>
struct wiekszy {
	bool operator() (const T& x, const T& y) const {
		return x > y;
	};
	typedef T first_argument_type;
	typedef T second_argument_type;
	typedef bool result_type;
};

class kolejka_prio_list {
public:
	priority_queue<list<string>/*, wiekszy<string>*/> kontener;


};

class FileEditor :
	public kolejka_prio_list {
public:
	void open(const char* filename);
	FileEditor(const char* filename)
	{
		open(filename);
	};
	FileEditor() {};
	void write(std::ostream& out =	std::cout);
	void SORT(void) {
		
	}
	~FileEditor() {};
};

void FileEditor::open(
	const char* filename) {
	ifstream in(filename);
	string line;
	while (getline(in, line)) {
		list<string> wiersz;
		istringstream ss(line);
		string slowo;
		int count = 0;
		while (ss >> slowo) {
			wiersz.push_back(slowo);
			count++;
		}
		wiersz.sort();
		if (count <= 6) wiersz.reverse();
		if(count!=0)kontener.push(wiersz);
	}
};

ostream& operator<<(ostream& out, list<string> L)
{
	list<string>::iterator it;
	for (it = L.begin(); it != L.end(); it++)
		out << *it<<' ';
	out << endl;
	return out;
}

void FileEditor::write(ostream& out) {
	while (!kontener.empty()) {
		int top_size = kontener.top().size();
		list<string> topowa = kontener.top();
		out << top_size; 
		out << ':';
		out<< topowa;

		kontener.pop();
	}
};

int main(int argc, char* argv[]) {
	FileEditor file;
	if (argc > 1) {
		file.open(argv[1]);
	}
	else {
		file.open("mistrz.txt"); // tu następuje przeniesienie danych
	}
	
	//int i = 1;
	//FileEditor::iterator w = file.begin();
	//while (w != file.end()) {
	//	ostringstream ss;
	//	ss << i++;
	//	*w = ss.str() + ": " + *w; // dopisanie numeru na początku wiersza
	//	++w;
	//}
	file.write(cout);
	return 0;
}