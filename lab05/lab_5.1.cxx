/*
Cole Gannon
Winter 2021
Lab 05
Problem 5.1
Description of problem: Suffer
*/
#include <stdexcept>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

template<class Child>
class Cargo {
protected:
	string type;
	string id;
	double lbs;
	string dest;
public:
	explicit inline Cargo() noexcept:
		type{"unknown"},
		id{"----------"},
		lbs{},
		dest{"---"}
	{};

	inline Cargo(
		string const type,
		string const id,
		double const lbs,
		string const dest
	):
		type{type},
		id{id},
		lbs{lbs},
		dest{dest}
	{
		if (dest.length() != 3) {
			throw string("The destination must be a three character IANA");
		};

		if (Child::lbs_left < lbs) {
			throw string("The weight of this cargo exceeds the remaining capacity");
		}

		Child::lbs_left -= lbs;
	};

	inline Cargo(Cargo const &from) noexcept:
		type{from.type},
		id{from.id},
		lbs{from.lbs},
		dest{from.dest}
	{
		cout << "eeee\n";
		Child::lbs_left -= lbs;
	};

	inline ~Cargo() noexcept {
		Child::lbs_left += lbs;
		cout << "Cargo destructor called\n" << flush;
	};

	inline void output() const noexcept {
		cout <<
			Child::name << " {\n"
			"   type: " << this->type << ",\n"
			"   abbr: " << this->id.substr(0, 3) << ",\n"
			"   id  : " << this->id << ",\n"
			"   lbs : " << this->lbs << ",\n"
			"   dest: " << this->dest << ",\n"
			"}\n"
		;
	}
};

struct Boeing737Cargo final: public Cargo<Boeing737Cargo> {
	static constexpr char const *name{"Boeing737Cargo"};
	static double lbs_left;
	using Cargo<Boeing737Cargo>::Cargo;
};
double Boeing737Cargo::lbs_left{46000};

struct Boeing767Cargo final: public Cargo<Boeing767Cargo> {
	static constexpr char const *name{"Boeing767Cargo"};
	static double lbs_left;
	using Cargo<Boeing767Cargo>::Cargo;
};
double Boeing767Cargo::lbs_left{116000};

vector<Boeing737Cargo> cargo737{};
template <class ...Ts>
inline void load737(Ts ...args) noexcept {
	try {
		cargo737.emplace_back(forward<Ts>(args)...);
	} catch (string err) {
		cerr << err << "!\n";
	}
};

vector<Boeing767Cargo> cargo767{};
template <class ...Ts>
inline void load767(Ts ...args) noexcept {
	try {
		cargo767.emplace_back(forward<Ts>(args)...);
	} catch (string err) {
		cerr << err << "!\n";
	}
};

#define data_file "lab5data.txt"

inline void input() noexcept {
	ifstream input_file;
	input_file.open(data_file);

	if (!input_file.is_open()) {
		cerr << "Could not open " data_file "!\n";
		return;
	}

	// not required but it's a good idea so we don't have to resize
	cargo737.reserve(20);
	cargo767.reserve(20);

	size_t i{};
	string s_line;
	while (getline(input_file, s_line)) {
		istringstream line{s_line};

		string type;
		string abbr;
		string id;
		string aircraft;
		string s_lbs;
		string dest;

		line >> type;
		line >> abbr;
		line >> id;
		line >> aircraft;
		line >> s_lbs;
		line >> dest;

		cout << "ENTRY " << ++i << ": " << id << '\n';

		if (abbr != id.substr(0, 3)) {
			cerr << "The abbreviation must match the first three characters of the id!\n";
			continue;
		}

		double lbs;
		try {
			lbs = {stod(s_lbs)};
		} catch (...) {
			cerr << "Could not convert " << s_lbs << " to double!\n";
			continue;
		}

		if (aircraft == "737") {
			load737(type, id, lbs, dest);
			continue;
		}

		if (aircraft == "767") {
			load767(type, id, lbs, dest);
			continue;
		}

		cerr << "Unknown aircraft \"" << aircraft << "\"!\n";
	}
};

inline void output() noexcept {
	for (auto &b737 : cargo737) {
		b737.output();
	}

	for (auto &b767 : cargo767) {
		b767.output();
	}
}

int main() noexcept {
	cout << "-----------------------\n";
	input();
	cout << "-----------------------\n";
	cout << "-----------------------\n";
	output();
	cout << "-----------------------\n";
}
