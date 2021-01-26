#include <cstdint>
#include <cstdlib>
#include <stdint.h>
#include <string>
#include <array>
#include <iostream>

using namespace std;

// we're gonna borrow a character for the null byte
using IANA = array<char, 4>;

class Freight {
public:
	enum class Type: uint8_t {
		Container = 0,
		Pallet    = 1,
	};

	// You can't extend enums in C++
	enum class MaybeType: uint8_t {
		Container = 0,
		Pallet    = 1,
		None      = 2
	};

	using weight_t = uint32_t;
private:
	Type uld;
	string uldid;
	string aircraft;
	weight_t weight;
	IANA destination;

	// Would be nice if you could declare methods on enums like you can in Rust
	static inline Type type_from_str(string s);
	static inline string str_from_type(Type t) noexcept;

	static inline bool is_container_alignment(string str3) noexcept;
	static inline bool is_pallet_alignment(string str3) noexcept;
	inline Type *id_alignment() noexcept;
public:
	explicit Freight() noexcept = delete;
	explicit Freight(
		Type type, string id, string aircraft, weight_t weight, IANA dest
	) noexcept:
		uld{type}, uldid{id}, aircraft{aircraft}, weight{weight}, destination{dest}
	{};

	// Methods are marked inline by default but no harm in explicitly saying it
	inline Type getULD()  const noexcept { return uld; }
	inline string getULDID()     const noexcept { return uldid; }
	inline string getAircraft()  const noexcept { return aircraft; }
	inline weight_t getWeight()  const noexcept { return weight; }
	inline IANA getDestination() const noexcept { return destination; }

	// Setters can be declared out of line since they are more complex
	inline void setULD(Type uld);
	inline void setULD(string uld);
	inline void setULDID(string uldid);
	inline void setAircraft(string aircraft);
	inline void setWeight(weight_t weight);
	inline void setWeight(string weight);
	inline void setDestination(IANA destination);
	inline void setDestination(string destination);
};

inline Freight::Type Freight::type_from_str(string s) {
	if (s == "container") {
		return Freight::Type::Container;
	}

	if (s == "pallet") {
		return Freight::Type::Pallet;
	}

	throw exception("The input string must be either 'container' or 'pallet'");
};

inline string Freight::str_from_type(Freight::Type t) noexcept {
	return t == Freight::Type::Container ? "Container" : "Pallet";
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

inline Freight::Type *Freight::id_alignment() noexcept {
	if (uldid.empty()) {
		return nullptr;
	}
}


inline void Freight::setULD(Type uld) {
	
}

inline void Freight::setULD()
inline Freight *input() noexcept;
inline void output(Freight const *) noexcept;
int main() {
	auto user_freight{input()};
	if (user_freight == nullptr) {
		cout << "Interrupt...\n";
		return 1;
	}
	output(user_freight);
}

/// Returns true on success
inline bool sgetline(string &output) noexcept {
	getline(cin, output);
	return cin.good();
}

inline Freight *input() noexcept {
	using FreightType = Freight::FreightType;
	FreightType freight_type;
	cout << "What type of freight is it?\n";
	while (true) {
		cout << "Enter eight 'container' or 'pallet'\n> ";
		string input;
		if (!sgetline(input)) return nullptr;

		if (input == "container") {
			freight_type = {FreightType::Container};
			break;
		}

		if (input == "pallet") {
			freight_type = {FreightType::Pallet};
			break;
		}
	}

	string id;
	cout << "Enter an appropriate id:\n";
	while (true) {
		cout << "> ";
		if (!sgetline(id)) return nullptr;

		auto first3{id.substr(0, 3)};

		if (0
			|| first3 == "AYF"
			|| first3 == "AYK"
			|| first3 == "AAA"
			|| first3 == "AYY"
		) {
			if (freight_type == FreightType::Container) {
				break;
			}
			cout << first3 << " is not an appropriate prefix for Containers!\n";
			continue;
		}

		if (0
			|| first3 == "PAG"
			|| first3 == "PMC"
			|| first3 == "PLA"
		) {
			if (freight_type == FreightType::Pallet) {
				break;
			}
			cout << first3 << " is not an appropriate prefix for Pallets!\n";
			continue;
		};

		cout << first3 << " is not a valid prefix!\n";
	}

	string aircraft;
	cout << "Enter the aircraft that will be carrying the freight:\n> ";
	getline(cin, aircraft);

	Freight::weight_t weight;
	cout << "Enter the weight of the freight in kilos:\n";
	while (true) {
		cout << "> ";
		string input;
		if (!sgetline(input)) return nullptr;

		auto const size{input.size()};
		auto const start{input.c_str()};

		if (start[0] != '-') {
			char *last_parsed;
			weight = {strtoul(start, &last_parsed, 10)};

			auto const chars_parsed{last_parsed - start};
			if (weight && chars_parsed == size) {
				break;
			}
		}

		cout << ""
			"Invalid input!\n"
			"Please enter an integral value greater than zero!\n";
	}

	IANA dest{};
	cout << "Enter an IANA for the freight destination:\n";
	while (true) {
		cout << "> ";
		string input;
		if (!sgetline(input)) return nullptr;
		if (input.length() == 3) {
			dest = {input[0], input[1], input[2], '\0'};
			break;
		}

		cout << "An IANA must be three characters!\n";
	}

	return new Freight(
		freight_type,
		id,
		aircraft,
		weight,
		dest
	);
};

constexpr char const *type_to_string(Freight::Type t) noexcept {
	return t == Freight::Type::Container ? "Container" : "Pallet";
}

inline void output(Freight const *freight) noexcept {
	cout << ""
	"uld         = " << type_to_string(freight->uld) << "\n"
	"uldid       = " << freight->uldid << "\n"
	"aircraft    = " << freight->aircraft << "\n"
	"weight      = " << freight->weight << "\n"
	"destination = " << freight->destination.data() << "\n";
}
