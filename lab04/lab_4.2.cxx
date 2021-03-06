/*
Cole Gannon
Winter 2021
Lab 04
Problem 4.2
Description of problem:
Decouple the input function from the class (already done). Move most of the
functionality to the input function. Read input from a file.
*/
#include <string>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>

using namespace std;

/// The Cargo class is an-all-in-one representation of pallets and containers.
/// Some data is duplicated for whatever reason but this is what-we-have-to-do.
class Cargo {
public:
	/// Since this class actually uses getters and setters correctly for input
	/// verification, the abbreviation also needs to match with the uld/type.
	/// Here, we check if a certain string like "AYF" is a container or pallet
	/// abbreviation.
	static inline bool is_container_alignment(string) noexcept;
	static inline bool is_pallet_alignment(string) noexcept;
private:
	string uld{"unknown"};
	/// Duplicated data. Abbreviation is also stored within the uldid...
	string abbreviation{"---"};
	string uldid{"----------"};
	string aircraft{"unknown"};
	double weight{};
	string destination{"---"};
public:
	explicit inline Cargo() noexcept {};
	/// unused for this program
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
	/// also unused copy constructor
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

	inline void set_uld(string);
	inline void set_abbreviation(string);
	inline void set_uldid(string);
	inline void set_aircraft(string) noexcept;
	inline void set_weight(double) noexcept;
	inline void set_weight(string);
	inline void set_destination(string);
};

/// no-arg input that should probably just be called main.
/// we open cardata4.txt and deserialize each line into a Cargo object temp.
/// temp is then outputted and destroyed.
inline void input() noexcept;
inline void output(Cargo const *) noexcept;
int main() {
	input();
}

inline void input() noexcept {
	// RAII closes this automatically
	ifstream inputFile;
	try {
		inputFile.open("cardata4.txt");
	} catch (...) {
		cerr << "Could not open cardata4.txt!\n";
	}

	string line;
	while (getline(inputFile, line)) {
		istringstream oline{line};
		string type;
		string abbr;
		string id;
		string aircraft;
		string pounds;
		string dest;

		oline >> type;
		oline >> abbr;
		oline >> id;
		oline >> aircraft;
		oline >> pounds;
		oline >> dest;

		cout << '\n';
		Cargo temp{};
		try {
			temp.set_uld(type);
			temp.set_abbreviation(abbr);
			temp.set_uldid(id);
			temp.set_aircraft(aircraft);
			temp.set_weight(pounds);
			temp.set_destination(dest);
		} catch (string e) {
			cerr << e << "\n";
			return;
		}
		output(&temp);
	}
};

inline void output(Cargo const *cargo) noexcept {
	cout << fixed;
	cout << ""
		"Unit load type: "         << cargo->get_uld() << "\n"
		"Unit load abbreviation: " << cargo->get_abbreviation() << "\n"
		"Unit identifier: "        << cargo->get_uldid() << "\n"
		"Aircraft type: "          << cargo->get_aircraft() << "\n";
	cout << ""
		"Unit weight (lbs): " << setprecision(2) << cargo->get_weight() << "\n"
		"Destination code: "  << cargo->get_destination() << "\n";
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
parsed correctly. If not, they'll throw a `string`. I know, exceptions are
bloody slow but what can you do? I don't have another choice if I want control
flow like this.
*/
inline void Cargo::set_uld(string uld) {
	if (uld != "Container" && uld != "Pallet") {
		throw string("The ULD must be either \"Container\" or \"Pallet\"!");
	}

	this->uld = {uld};
}

inline void Cargo::set_abbreviation(string abbr) {
	if (abbr.length() != 3) {
		throw string("The abbreviation must be three characters!");
	}

	if (is_container_alignment(abbr)) {
		if (this->uld != "Container") {
			throw string("Container abbreviation does not match the current uld!");
		}
	} else if (is_pallet_alignment(abbr)) {
		if (this->uld != "Pallet") {
			throw string("Pallet abbreviation does not match the current uld!");
		}
	} else {
		throw string("Invalid abbreviation!");
	}

	this->abbreviation = {abbr};
}

inline void Cargo::set_uldid(string uldid) {
	if (uldid.length() != 10) {
		throw string("The id must be 10 characters!");
	}

	this->uldid = {uldid};
};

inline void Cargo::set_aircraft(string aircraft) noexcept {
	this->aircraft = {aircraft};
};

inline void Cargo::set_weight(double weight) noexcept {
	this->weight = {weight};
};

inline void Cargo::set_weight(string weightstr) {
	double weight;
	try {
		weight = {stod(weightstr)};
	} catch (...) {
		throw string("Invalid double! Try again:");
	}

	this->weight = {weight};
};

inline void Cargo::set_destination(string destination) {
	if (destination.length() != 3) {
		throw string("The destination string must be three characters!");
	}

	this->destination = {destination};
};
