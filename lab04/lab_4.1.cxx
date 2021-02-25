/*
Cole Gannon
Winter 2021
Lab 04
Problem 4.1
Description of problem:
Make a friend operator== for the Cargo class
*/
#include <string>
#include <iostream>
#include <iomanip>

using namespace std;

class Cargo {
public:
	static inline bool is_container_alignment(string) noexcept;
	static inline bool is_pallet_alignment(string) noexcept;
private:
	string uld{"unknown"};
	string abbreviation{"---"};
	string uldid{"--------IB"};
	string aircraft{"unknown"};
	double weight{};
	string destination{"---"};
public:
	explicit inline Cargo() noexcept {};
	explicit Cargo(
		string type,
		string abbreviation,
		string id,
		string aircraft,
		double weight,
		string dest
	) noexcept:
		uld{type},
		abbreviation{abbreviation},
		uldid{id},
		aircraft{aircraft},
		weight{weight},
		destination{dest}
	{};
	/// copy constructor
	inline Cargo(Cargo const &from) noexcept:
		uld{from.uld},
		abbreviation{from.abbreviation},
		uldid{from.uldid},
		aircraft{from.aircraft},
		weight{from.weight},
		destination{from.destination}
	{};
	inline ~Cargo() noexcept { cout << "Cargo destructor called\n"; };

	inline string get_uld()          const noexcept { return uld; }
	inline string get_abbreviation() const noexcept { return abbreviation; }
	inline string get_uldid()        const noexcept { return uldid; }
	inline string get_aircraft()     const noexcept { return aircraft; }
	inline double get_weight()       const noexcept { return weight; }
	inline string get_destination()  const noexcept { return destination; }

	// Setters can be declared out of line since they include input verification
	inline void set_uld(string);
	inline void set_abbreviation(string);
	inline void set_uldid(string);
	inline void set_aircraft(string) noexcept;
	inline void set_weight(double) noexcept;
	inline void set_weight(string);
	inline void set_destination(string);

	using setter = void (Cargo::*)(string);
	inline void set_from_input(char const *prompt, setter may_throw) noexcept;

	friend inline void kilotopound(Cargo *) noexcept;
	friend inline bool operator==(Cargo const &, Cargo const &);
};

inline void input(Cargo *) noexcept;
inline void output(Cargo const *) noexcept;
inline string nextline() noexcept;
int main() {
	Cargo unit1{};
	cout << "initial unit1:\n";
	output(&unit1);
	cout << "\nenter info for unit1:\n";
	input(&unit1);
	cout << "\nunit1:\n";
	output(&unit1);
	cout << '\n';

	cout << "unit2 = unit1\n";
	Cargo unit2 = unit1;
	cout << "\nunit2:\n";
	output(&unit2);
	cout << '\n';

	cout << "unit1 is ";
	if (!(unit1 == unit2)) cout << "not ";
	cout << "the same as unit2\n";

	Cargo unit3{};
	cout << "unit2 is ";
	if (!(unit2 == unit3)) cout << "not ";
	cout << "the same as unit3\n";
	cout << '\n';
}

inline void input(Cargo *cargo) noexcept {
	cargo->set_from_input("Enter the type/ULD of the cargo (container/pallet)",
		&Cargo::set_uld);
	cargo->set_from_input("Enter the abbreviation",
		&Cargo::set_abbreviation);
	cargo->set_from_input("Enter a five digit id",
		&Cargo::set_uldid);
	cargo->set_from_input("Enter the aircraft that will be carrying the cargo",
		&Cargo::set_aircraft);
	cargo->set_from_input("Enter the weight of the cargo",
		&Cargo::set_weight);
	cargo->set_from_input("Enter an IANA for the cargo destination",
		&Cargo::set_destination);
};

inline void output(Cargo const *cargo) noexcept {
	cout << ""
		"Unit load type: "         << cargo->get_uld() << "\n"
		"Unit load abbreviation: " << cargo->get_abbreviation() << "\n"
		"Unit identifier: "        << cargo->get_uldid() << "\n"
		"Aircraft type: "          << cargo->get_aircraft() << "\n";
	cout
		<< fixed
		<< "Unit weight: " << setprecision(2) << cargo->get_weight() << "\n"
		<< "Destination code: " << cargo->get_destination() << "\n";
}

/// Gets the nextline from cin.
/// If user inputs ctrl+c, exits the entire program.
inline string nextline() noexcept {
	string temp;
	getline(cin, temp);
	if (!cin.good()) {
		cout << "Interrupt..." << endl;
		terminate();
	}
	return temp;
}

inline bool Cargo::is_container_alignment(string str3) noexcept {
	return 0
		|| str3 == "AYF"
		|| str3 == "AYK"
		|| str3 == "AAA"
		|| str3 == "AYY";
}

inline bool Cargo::is_pallet_alignment(string str3) noexcept {
	return 0
		|| str3 == "PAG"
		|| str3 == "PMC"
		|| str3 == "PLA";
}

/* Setters Implementation
Setters that take `string` will perform checking to make sure the string can be
parsed correctly. Some setters may throw `exception` which will be caught and
handled in Cargo::set_from_input.
*/
inline void Cargo::set_uld(string uld) {
	if (uld != "container" && uld != "pallet") {
		throw string("The ULD must be either \"container\" or \"pallet\"!");
	}

	this->uld = {uld};
}

inline void Cargo::set_abbreviation(string abbr) {
	if (abbr.length() != 3) {
		throw string("The abbreviation must be three characters!");
	}

	if (is_container_alignment(abbr)) {
		if (this->uld != "container") {
			throw string("Container abbreviation does not match the current uld!");
		}
	} else if (is_pallet_alignment(abbr)) {
		if (this->uld != "pallet") {
			throw string("Pallet abbreviation does not match the current uld!");
		}
	} else {
		throw string("Invalid abbreviation!");
	}

	this->abbreviation = {abbr};
}

inline bool all_digits(string s) noexcept {
	for (auto &&c : s) {
		if (!isdigit(c)) {
			return false;
		}
	}
	return true;
}

inline void Cargo::set_uldid(string uldid) {
	if (uldid.length() == 5 && all_digits(uldid)) {
		this->uldid = {this->abbreviation + uldid + "IB"};
		return;
	}

	throw string("The id must be 5 digits!");
};

inline void Cargo::set_aircraft(string aircraft) noexcept {
	this->aircraft = {aircraft};
};

inline void Cargo::set_weight(double weight) noexcept {
	this->weight = {weight};
};

inline void kilotopound(Cargo *self) noexcept {
	self->weight *= 2.2;
}

inline void Cargo::set_weight(string weightstr) {
	double weight;
	try {
		weight = {stod(weightstr)};
	} catch (...) {
		throw string("Invalid double! Try again:");
	}

	this->weight = {weight};

	cout << "Is the weight in 'kilos' or 'pounds'?";
	while (true) {
		cout << "\n> ";
		string units{nextline()};
		if (units == "pounds") {
			break;
		}

		if (units == "kilos") {
			kilotopound(this);
			break;
		}

		cout << "The weight must be in either 'kilos' or 'pounds'!";
	}
};

inline void Cargo::set_destination(string destination) {
	if (destination.length() != 3) {
		throw string("The destination string must be three characters!");
	}

	this->destination = {destination};
};

inline void Cargo::set_from_input(char const *prompt, Cargo::setter setter) noexcept {
	cout << prompt << ':';
	while (true) {
		cout << "\n> ";
		try {
			(*this.*setter)(nextline());
			break;
		} catch (string e) {
			cout << e;
		}
	}
}

inline bool operator==(Cargo const &left, Cargo const &right) {
	return true
		&& left.abbreviation == right.abbreviation
		&& left.uldid == right.uldid;
}
