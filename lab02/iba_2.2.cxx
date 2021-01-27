#include <cstdint>
#include <cstdlib>
#include <exception>
#include <string>
#include <array>
#include <iostream>

using namespace std;

// three characters and a null byte
using IANA = array<char, 4>;

class Freight {
// Static stuff that needs to be used from the outside
public:
	enum class Type: uint8_t {
		None,
		Container,
		Pallet,
	};

	using weight_t = uint32_t;
	// Would be nice if you could declare methods on enums like you can in Rust
	static inline Type type_from_str(string s);
	static inline string str_from_type(Type t) noexcept;

	static inline Type id_alignment(string id) noexcept;
	static inline bool is_container_alignment(string str3) noexcept;
	static inline bool is_pallet_alignment(string str3) noexcept;
private:
	Type uld{Type::None};
	string uldid;
	string aircraft;
	weight_t weight;
	IANA destination;
public:
	explicit inline Freight() noexcept {};
	inline ~Freight() noexcept { cout << "Cargo destructor called\n"; };

	// Methods are marked inline by default but no harm in explicitly saying it
	inline Type getULD()         const noexcept { return uld; }
	inline string getULDID()     const noexcept { return uldid; }
	inline string getAircraft()  const noexcept { return aircraft; }
	inline weight_t getWeight()  const noexcept { return weight; }
	inline IANA getDestination() const noexcept { return destination; }

	inline string getULDID3() const;

	// Setters can be declared out of line since they are more complex
	inline void setULD(Type uld);
	inline void setULD(string uld);
	inline void setULDID(string uldid);
	inline void setAircraft(string aircraft) noexcept;
	inline void setWeight(weight_t weight) noexcept;
	inline void setWeight(string weight);
	inline void setDestination(IANA destination) noexcept;
	inline void setDestination(string destination);

	/// pointer type to one of those string setters declared above
	using setter = void (Freight::*)(string);
	/// If the setter throws, prints the error message and prompts again
	inline void setFromInput(char const *prompt, setter may_throw) noexcept;
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

	freight->setFromInput("Enter the type/ULD of the freight",
		&Freight::setULD);
	freight->setFromInput("Enter an appropriate id",
		&Freight::setULDID);
	freight->setFromInput("Enter the aircraft that will be carrying the freight",
		&Freight::setAircraft);
	freight->setFromInput("Enter the weight of the freight in kilos",
		&Freight::setWeight);
	freight->setFromInput("Enter an IANA for the freight destination",
		&Freight::setDestination);

	return freight;
};

inline void output(Freight const *freight) noexcept {
	cout << "\n"
		"Unit load type: "         << Freight::str_from_type(freight->getULD()) << "\n"
		"Unit load abbreviation: " << freight->getULDID3() << "\n"
		"Unit identifier: "        << freight->getULDID() << "\n"
		"Aircraft type: "          << freight->getAircraft() << "\n"
		"Unit weight: "            << freight->getWeight() << "\n"
		"Unit weight: "            << freight->getDestination().data() << "\n";
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

/* Class Implementation */

inline Freight::Type Freight::type_from_str(string s) {
	if (s == "container") {
		return Freight::Type::Container;
	}

	if (s == "pallet") {
		return Freight::Type::Pallet;
	}

	if (s == "none") {
		return Freight::Type::None;
	}

	throw exception("The input string must be either 'container' or 'pallet'");
};

inline string Freight::str_from_type(Freight::Type t) noexcept {
	switch (t) {
		case Freight::Type::Container: return "container";
		case Freight::Type::Pallet: return "pallet";
		default: return "None";
	}
}

/// id must be at least three characters or else ub
inline Freight::Type Freight::id_alignment(string id) noexcept {
	if (id.empty()) {
		return Freight::Type::None;
	}

	auto first3{id.substr(0, 3)};

	if (is_container_alignment(first3)) {
		return Freight::Type::Container;
	}

	if (is_pallet_alignment(first3)) {
		return Freight::Type::Pallet;
	}

	return Freight::Type::None;
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

/// First three characters of this->uldid
inline string Freight::getULDID3() const {
	if (this->uldid.size() < 3) {
		throw exception("The provided string should be at least three characters!");
	}
	return this->uldid.substr(0, 3);
}

/* Setters Implementation */
/*
Setters that take `string` will perform checking to make sure the string can be
parsed correctly. Some setters may throw `exception` which will be caught and
handled in Freight::setFromInput.
*/

inline void Freight::setULD(Type uld) {
	if (uld == Freight::Type::None) {
		throw exception("The freight's type must be either Container or Pallet!");
	}

	this->uld = uld;
}

inline void Freight::setULD(string uld) {
	this->setULD(Freight::type_from_str(uld));
}

inline void Freight::setULDID(string uldid) {
	if (uldid.length() < 3) {
		throw exception("The provided uldid should be at least three characters!");
	}

	if (Freight::id_alignment(uldid) != this->uld) {
		throw exception("The provided uldid does not match the uld of the Freight!");
	}

	this->uldid = uldid;
};

inline void Freight::setAircraft(string aircraft) noexcept {
	this->aircraft = aircraft;
};

inline void Freight::setWeight(Freight::weight_t weight) noexcept {
	this->weight = weight;
};

inline void Freight::setWeight(string weightstr) {
	auto const size{weightstr.size()};
	auto const start{weightstr.c_str()};

	if (start[0] == '-') {
		throw exception("The weight cannot be negative!");
	}

	char *last_parsed;
	auto const weight{strtoul(start, &last_parsed, 10)};

	auto const chars_parsed{last_parsed - start};

	if (weight == 0 || chars_parsed != size) {
		throw exception("Invalid input or weight was zero!");
	}

	this->setWeight(weight);
};

inline void Freight::setDestination(IANA destination) noexcept {
	this->destination = destination;
};

inline void Freight::setDestination(string destination) {
	if (destination.length() != 3) {
		throw exception("The destination string must be three characters!");
	}

	this->destination = {destination[0], destination[1], destination[2], '\0'};
};

inline void Freight::setFromInput(char const *prompt, Freight::setter setter) noexcept {
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
