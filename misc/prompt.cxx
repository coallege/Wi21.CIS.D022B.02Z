#include <exception>
#include <string>
#include <functional>
#include <iostream>
using namespace std;

template <class T>
auto prompt(function<T(string)> &p) noexcept -> T *{
	cout << "> ";
	cin.clear();
	cin.ignore();
	string line;
	getline(cin, line);
	try {
		return p(line);
	} catch (...) {
		return nullptr;
	}
}

template <class T>
auto prompt(char const *question, function<T(string)> &p) noexcept -> T *{
	cout << question << '\n';
	return prompt(p);
}
