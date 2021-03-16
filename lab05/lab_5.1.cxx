/*
Cole Gannon
Winter 2021
Lab 05
Problem 5.1
Description of problem:
Make Cargo an abstract class using a pure virtual function named `maxweight'
Create two child classes Boeing737Cargo and Boeing767Cargo.
Perform input checking when reading in these Cargos from a file into a vector.
Output the vector contents when finished.
*/
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

class Cargo {
protected:
	string type;
	string abbr;
	string id;
	double lbs;
	string dest;
public:
	Cargo() noexcept:
		type{"unknown"},
		id{"----------"},
		lbs{},
		dest{"---"}
	{}

	Cargo(
		string const type,
		string const abbr,
		string const id,
		double const lbs,
		string const dest
	):
		type{type},
		abbr{abbr},
		id{id},
		lbs{lbs},
		dest{dest}
	{
		if (type != "Container" && type != "Pallet") {
			throw string("The type must be either \"Container\" or \"Pallet\"");
		}

		if (abbr != id.substr(0, 3)) {
			throw string("The abbreviation must equal first three characters of the id");
		}

		if (id.length() != 10) {
			throw string("The id must be ten characters long");
		}

		if (dest.length() != 3) {
			throw string("The destination must be a three character IANA");
		}
	}

	Cargo(Cargo const &from) noexcept:
		type{from.type},
		abbr{from.abbr},
		id{from.id},
		lbs{from.lbs},
		dest{from.dest}
	{}

public:
	// unused getters and setters
	string get_type() const noexcept { return this->type; }
	string get_abbr() const noexcept { return this->abbr; }
	string get_id  () const noexcept { return this->id  ; }
	double get_lbs () const noexcept { return this->lbs ; }
	string get_dest() const noexcept { return this->dest; }

	void output() const noexcept {
		cout <<
			this->name() << " {\n"
			"   type = " << this->type << ",\n"
			"   abbr = " << this->abbr << ",\n"
			"   id   = " << this->id   << ",\n"
			"   lbs  = " << this->lbs  << ",\n"
			"   dest = " << this->dest << ",\n"
			"}\n";
	}

	virtual double maxweight() const noexcept = 0;
	virtual string name() const noexcept = 0;
};

struct Boeing737Cargo final: public Cargo {
	using Cargo::Cargo;

	bool abbr_is_container() const noexcept {
		return false
			|| this->abbr == "AYF"
			|| this->abbr == "AYK"
			|| this->abbr == "AAA"
			|| this->abbr == "AYY";
	}

	bool abbr_is_pallet() const noexcept {
		return false
			|| this->abbr == "PAG"
			|| this->abbr == "PMC"
			|| this->abbr == "PLA";
	}

	// I wouldn't have to define this if we could use virtual functions within
	// the parent constructor but because of how classes are instantiated, we
	// cannot. Quite annoying. Means that I've written basically identical code
	// for both this class and it's sibling class.
	Boeing737Cargo(
		string const type,
		string const abbr,
		string const id,
		double const lbs,
		string const dest
	): Cargo(type, abbr, id, lbs, dest)
	{
		if (type == "Container") {
			if (abbr_is_container()) {
				return;
			}

			throw (
				abbr +
				" is not a valid abbreviation for "
				"Containers on Boeing737 planes"
			);
		} else {
			if (abbr_is_pallet()) {
				return;
			}

			throw (
				abbr +
				" is not a valid abbreviation for "
				"Pallets on Boeing737 planes"
			);
		}
	}

	~Boeing737Cargo() noexcept { cout << this->id << " has been deleted\n"; }

	virtual double maxweight() const noexcept override final {
		return 46000;
	}

	virtual string name() const noexcept override final {
		return {"Boeing737Cargo"};
	}
};

struct Boeing767Cargo final: public Cargo {
	using Cargo::Cargo;

	bool abbr_is_container() const noexcept {
		return false
			|| this->abbr == "AKE"
			|| this->abbr == "APE"
			|| this->abbr == "AKC"
			|| this->abbr == "AQP"
			|| this->abbr == "AQF"
			|| this->abbr == "AAP";
	}

	bool abbr_is_pallet() const noexcept {
		return false
			|| this->abbr == "P1P"
			|| this->abbr == "P6P";
	}

	Boeing767Cargo(
		string const type,
		string const abbr,
		string const id,
		double const lbs,
		string const dest
	): Cargo(type, abbr, id, lbs, dest)
	{
		if (type == "Container") {
			if (abbr_is_container()) {
				return;
			}

			throw (
				abbr + " is not a valid abbreviation for Containers on Boeing767 planes"
			);
		} else {
			if (abbr_is_pallet()) {
				return;
			}

			throw (
				abbr + " is not a valid abbreviation for Pallets on Boeing767 planes"
			);
		}
	}

	~Boeing767Cargo() noexcept { cout << this->id << " has been deleted\n"; }

	virtual double maxweight() const noexcept override final {
		return 116000;
	}

	virtual string name() const noexcept override final {
		return {"Boeing767Cargo"};
	}
};

vector<Boeing737Cargo> cargo737{};
inline void load737(
	string const &type,
	string const &abbr,
	string const &id,
	double const lbs,
	string const &dest
) {
	static double lbs_left{
		(reinterpret_cast<Boeing737Cargo *>(NULL)->Boeing737Cargo::maxweight)()
	};

	if (lbs_left < lbs) {
		cerr
			<< "Failed to load Cargo with weight of " << lbs
			<< "lbs onto Boeing737\n";
		return;
	}

	cargo737.emplace_back(type, abbr, id, lbs, dest);

	lbs_left -= lbs;
};

vector<Boeing767Cargo> cargo767{};
inline void load767(
	string const &type,
	string const &abbr,
	string const &id,
	double const lbs,
	string const &dest
) {
	static double lbs_left{
		(reinterpret_cast<Boeing767Cargo *>(NULL)->Boeing767Cargo::maxweight)()
	};

	if (lbs_left < lbs) {
		cerr
			<< "Failed to load Cargo with weight of " << lbs
			<< "lbs onto Boeing767\nOnly " << lbs_left << "lbs remaining space\n";
		return;
	}

	cargo767.emplace_back(type, abbr, id, lbs, dest);

	lbs_left -= lbs;
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

		string
			type,
			abbr,
			id,
			aircraft,
			s_lbs,
			dest;

		line.clear();

		line
			>> type
			>> abbr
			>> id
			>> aircraft
			>> s_lbs
			>> dest;

		if (line.fail()) {
			cout << "BAD ENTRY\n";
		}

		cout << "ENTRY " << ++i << ": " << id << '\n';

		double lbs;
		try {
			lbs = {stod(s_lbs)};
		} catch (...) {
			cerr << "Could not convert " << s_lbs << " to double!\n";
			continue;
		}

		try {
			if (aircraft == "737") {
				load737(type, abbr, id, lbs, dest);
			} else if (aircraft == "767") {
				load767(type, abbr, id, lbs, dest);
			} else {
				throw aircraft + " is not a valid aircraft";
			}

			cout << "ENTRY " << i << ": OK\n";
		} catch (string err) {
			cerr << "ENTRY " << i << ": " << err << "!\n";
		}
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
	input();
	cout << "-----------------------\n";
	output();
	cout << "-----------------------\n";
}
