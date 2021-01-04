// this was taken from my last C++ class
#include <iostream> // :death:
using namespace std;

template <class T>
inline T prompt(const char *prompt) {
	T out;
	cout << prompt << "\n> ";
	cin >> out;
	cin.clear();
	cin.ignore();
	return out;
}
