/*
Cole Gannon
Winter 2021
Lab 02
Problem 2.1
Description of problem:
Take user input and store it in a Freight/Cargo class.
Then output the class contents.
*/
#include <cstdint>
#include <cstdlib>
#include <exception>
#include <string>
#include <iostream>

using namespace std;

class Freight {
// Static stuff that needs to be used from the outside
public:
	static inline string id_alignment(string) noexcept;
	static inline bool is_container_alignment(string) noexcept;
	static inline bool is_pallet_alignment(string) noexcept;
private:
	string uld;
	string abbreviation;
	string uldid;
	string aircraft;
	uint32_t weight;
	string destination;
public:
	// Methods are marked inline by default but no harm in explicitly saying it
	explicit inline Freight() noexcept {};
	inline ~Freight() noexcept { cout << "Cargo destructor called\n"; };

	inline string get_uld()          const noexcept { return uld; }
	inline string get_abbreviation() const noexcept { return abbreviation; }
	inline string get_uldid()        const noexcept { return uldid; }
	inline string get_aircraft()     const noexcept { return aircraft; }
	inline uint32_t get_weight()     const noexcept { return weight; }
	inline string get_destination()  const noexcept { return destination; }

	// Setters can be declared out of line since they include input verification

	inline void set_uld(string);
	inline void set_abbreviation(string);
	inline void set_uldid(string) noexcept;
	inline void set_aircraft(string) noexcept;
	inline void set_weight(uint32_t) noexcept;
	inline void set_weight(string);
	inline void set_destination(string);

	/// pointer type to one of those string setters declared above
	using setter = void (Freight::*)(string);
	/// If the setter throws, prints the error message and prompts again
	inline void set_from_input(char const *prompt, setter may_throw) noexcept;
};

/// Will never produce nullptr
inline Freight *input() noexcept;
inline void output(Freight const *) noexcept;
int main() {
	auto const user_freight{input()};
	output(user_freight);
	delete user_freight;
}

inline Freight *input() noexcept {
	Freight *freight = new Freight();

	freight->set_from_input("Enter the type/ULD of the freight",
		&Freight::set_uld);
	freight->set_from_input("Enter the abbreviation",
		&Freight::set_abbreviation);
	freight->set_from_input("Enter an appropriate id",
		&Freight::set_uldid);
	freight->set_from_input("Enter the aircraft that will be carrying the freight",
		&Freight::set_aircraft);
	freight->set_from_input("Enter the weight of the freight in kilos",
		&Freight::set_weight);
	freight->set_from_input("Enter an IANA for the freight destination",
		&Freight::set_destination);

	return freight;
};

inline void output(Freight const *freight) noexcept {
	cout << "\n"
		"Unit load type: "         << freight->get_uld() << "\n"
		"Unit load abbreviation: " << freight->get_abbreviation() << "\n"
		"Unit identifier: "        << freight->get_uldid() << "\n"
		"Aircraft type: "          << freight->get_aircraft() << "\n"
		"Unit weight: "            << freight->get_weight() << "\n"
		"Unit weight: "            << freight->get_destination() << "\n";
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

inline bool Freight::is_container_alignment(string str3) noexcept {
	return 0
		|| str3 == "AYF"
		|| str3 == "AYK"
		|| str3 == "AAA"
		|| str3 == "AYY";
}

inline bool Freight::is_pallet_alignment(string str3) noexcept {
	return 0
		|| str3 == "PAG"
		|| str3 == "PMC"
		|| str3 == "PLA";
}

/* Setters Implementation
Setters that take `string` will perform checking to make sure the string can be
parsed correctly. Some setters may throw `exception` which will be caught and
handled in Freight::setFromInput.
*/
inline void Freight::set_uld(string uld) {
	if (uld != "container" && uld != "pallet") {
		throw exception("The ULD must be either \"container\" or \"pallet\"!");
	}

	this->uld = {uld};
}

inline void Freight::set_abbreviation(string abbr) {
	if (abbr.length() != 3) {
		throw exception("The abbreviation must be three characters!");
	}

	if (is_container_alignment(abbr)) {
		if (this->uld != "container") {
			throw exception("Container abbreviation does not match the current uld!");
		}
	} else if (is_pallet_alignment(abbr)) {
		if (this->uld != "pallet") {
			throw exception("Pallet abbreviation does not match the current uld!");
		}
	} else {
		throw exception("Invalid abbreviation!");
	}

	this->abbreviation = {abbr};
}

inline void Freight::set_uldid(string uldid) noexcept {
	this->uldid = {uldid};
};

inline void Freight::set_aircraft(string aircraft) noexcept {
	this->aircraft = {aircraft};
};

inline void Freight::set_weight(uint32_t weight) noexcept {
	this->weight = {weight};
};

inline void Freight::set_weight(string weightstr) {
	if (weightstr[0] == '-') {
		throw exception("The weight cannot be negative!");
	}

	this->set_weight(stoul(weightstr));
};

inline void Freight::set_destination(string destination) {
	if (destination.length() != 3) {
		throw exception("The destination string must be three characters!");
	}

	this->destination = {destination};
};

inline void Freight::set_from_input(char const *prompt, Freight::setter setter) noexcept {
	cout << prompt << ':';
	while (true) {
		cout << "\n> ";
		try {
			(*this.*setter)(nextline());
		} catch (exception e) {
			cout << e.what();
			continue;
		}
		break;
	}
}
