/*
Cole Gannon
Winter 2021
Lab 02
Problem 2.1
Description of problem:
Take user input and store it in a Cargo/Cargo class.
Then output the class contents.
*/
#include <cstdint>
#include <cstdlib>
#include <exception>
#include <string>
#include <iostream>
#include <algorithm>
#include <cctype>

using namespace std;

class Cargo {
// Static stuff that needs to be used from the outside
// Methods are marked inline by default but no harm in explicitly saying it
public:
	static inline string id_alignment(string) noexcept;
	static inline bool is_container_alignment(string) noexcept;
	static inline bool is_pallet_alignment(string) noexcept;
private:
	string uld{"unknown"};
	string abbreviation{"---"};
	string uldid{"--------IB"};
	string aircraft{"unknown"};
	uint32_t weight{};
	string destination{"---"};
public:
	explicit inline Cargo() noexcept {};
	/// 5 arg constructor that is never used
	explicit inline Cargo(
		string type,
		string abbr,
		string id,
		string aircraft,
		uint32_t weight,
		string dest
	) noexcept {
		set_uld(type);
		set_abbreviation(abbr);
		set_uldid(id);
		set_aircraft(aircraft);
		set_weight(weight);
		set_destination(dest);
	};
	inline ~Cargo() noexcept { cout << "Cargo destructor called\n"; };

	inline string get_uld()          const noexcept { return uld; }
	inline string get_abbreviation() const noexcept { return abbreviation; }
	inline string get_uldid()        const noexcept { return uldid; }
	inline string get_aircraft()     const noexcept { return aircraft; }
	inline uint32_t get_weight()     const noexcept { return weight; }
	inline string get_destination()  const noexcept { return destination; }

	// Setters can be declared out of line since they include input verification

	inline void set_uld(string);
	inline void set_abbreviation(string);
	inline void set_uldid(string);
	inline void set_aircraft(string) noexcept;
	inline void set_weight(uint32_t) noexcept;
	inline void set_weight(string);
	inline void set_destination(string);

	/// pointer type to one of those string setters declared above
	using setter = void (Cargo::*)(string);
	/// If the setter throws, prints the error message and prompts again
	inline void set_from_input(char const *prompt, setter may_throw) noexcept;
};

/// Will never produce nullptr
inline void input(Cargo *) noexcept;
inline void output(Cargo const *) noexcept;
int main() {
	auto user_cargo{new Cargo};
	output(user_cargo);
	input(user_cargo);
	output(user_cargo);
	delete user_cargo;
	user_cargo = {nullptr};
}

inline void input(Cargo *cargo) noexcept {
	cout << '\n';
	cargo->set_from_input("Enter the type/ULD of the cargo (container/pallet)",
		&Cargo::set_uld);
	cargo->set_from_input("Enter the abbreviation",
		&Cargo::set_abbreviation);
	cargo->set_from_input("Enter a five digit id",
		&Cargo::set_uldid);
	cargo->set_from_input("Enter the aircraft that will be carrying the cargo",
		&Cargo::set_aircraft);
	cargo->set_from_input("Enter the weight of the cargo in kilos",
		&Cargo::set_weight);
	cargo->set_from_input("Enter an IANA for the cargo destination",
		&Cargo::set_destination);
	cout << '\n';
};

inline void output(Cargo const *cargo) noexcept {
	cout << ""
		"Unit load type: "         << cargo->get_uld() << "\n"
		"Unit load abbreviation: " << cargo->get_abbreviation() << "\n"
		"Unit identifier: "        << cargo->get_uldid() << "\n"
		"Aircraft type: "          << cargo->get_aircraft() << "\n"
		"Unit weight: "            << cargo->get_weight() << "\n"
		"Destination code: "       << cargo->get_destination() << "\n";
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
handled in Cargo::setFromInput.
*/
inline void Cargo::set_uld(string uld) {
	if (uld != "container" && uld != "pallet") {
		throw exception("The ULD must be either \"container\" or \"pallet\"!");
	}

	this->uld = {uld};
}

inline void Cargo::set_abbreviation(string abbr) {
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

inline void Cargo::set_uldid(string uldid) {
	if (uldid.length() == 5 && all_of(uldid.begin(), uldid.end(), isdigit)) {
		this->uldid = {this->abbreviation + uldid + "IB"};
		return;
	}

	throw exception("The id must be 5 digits!");
};

inline void Cargo::set_aircraft(string aircraft) noexcept {
	this->aircraft = {aircraft};
};

inline void Cargo::set_weight(uint32_t weight) noexcept {
	this->weight = {weight};
};

inline void Cargo::set_weight(string weightstr) {
	if (weightstr[0] == '-') {
		throw exception("The weight cannot be negative!");
	}

	this->set_weight(stoul(weightstr));
};

inline void Cargo::set_destination(string destination) {
	if (destination.length() != 3) {
		throw exception("The destination string must be three characters!");
	}

	this->destination = {destination};
};

inline void Cargo::set_from_input(char const *prompt, Cargo::setter setter) noexcept {
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
