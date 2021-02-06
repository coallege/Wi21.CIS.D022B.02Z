#include <cstdint>
#include <cstdlib>
#include <string>
#include <array>
#include <iostream>

using namespace std;

struct Freight {
	enum class Type: uint8_t {
		Container,
		Pallet,
	};

	/// weight can't be negative so let's make it impossible to represent
	using weight_t = uint32_t;

	Type uld;
	string uldid;
	string aircraft;
	weight_t weight;
	string destination;
	explicit Freight(
		Type type, string id, string aircraft, weight_t weight, string dest
	) noexcept:
		uld{type}, uldid{id}, aircraft{aircraft}, weight{weight}, destination{dest}
	{};
};

inline Freight *input() noexcept;
inline void output(Freight const *) noexcept;
inline string nextline() noexcept;
inline bool is_container_alignment(string str3) noexcept;
inline bool is_pallet_alignment(string str3) noexcept;
inline uint32_t parse_u32(string s) noexcept;
constexpr char const *type_to_string(Freight::Type t) noexcept;

int main() {
	auto user_freight{input()};
	output(user_freight);
	delete user_freight;
}

inline Freight *input() noexcept {
	Freight::Type freight_type;
	cout << "What type of freight is it?\n";
	while (true) {
		cout << "Enter eight 'container' or 'pallet'\n> ";
		auto const input{nextline()};

		if (input == "container") {
			freight_type = {Freight::Type::Container};
			break;
		}

		if (input == "pallet") {
			freight_type = {Freight::Type::Pallet};
			break;
		}
	}

	string id;
	cout << "Enter an appropriate id:";
	while (true) {
		cout << "\n> ";
		id = {nextline()};

		auto const first3{id.substr(0, 3)};

		if (is_container_alignment(first3)) {
			if (freight_type == Freight::Type::Container) {
				break;
			} else {
				cout << first3 << " is not an appropriate prefix for Containers!";
				continue;
			}
		}

		if (is_pallet_alignment(first3)) {
			if (freight_type == Freight::Type::Pallet) {
				break;
			} else {
				cout << first3 << " is not an appropriate prefix for Pallets!";
				continue;
			}
		}

		cout << first3 << " is not a valid prefix!";
	}

	cout << "Enter the aircraft that will be carrying the freight:\n> ";
	auto const aircraft{nextline()};

	Freight::weight_t weight{};
	cout << "Enter the weight of the freight in kilos:";
	while (true) {
		cout << "\n> ";
		auto const input{nextline()};

		weight = {parse_u32(input)};

		if (weight != 0) {
			break;
		}

		cout <<
			"Invalid input!\n"
			"Please enter an integral value greater than zero!";
	}

	string dest;
	cout << "Enter an IANA for the freight destination:";
	while (true) {
		cout << "\n> ";
		auto const input{nextline()};
		if (input.length() == 3) {
			dest = {input};
			break;
		}

		cout << "An IANA must be three characters!";
	}

	return new Freight(
		freight_type,
		id,
		aircraft,
		weight,
		dest
	);
};

inline void output(Freight const *freight) noexcept {
	cout
		<< "\nuld         = " << type_to_string(freight->uld)
		<< "\nuldid       = " << freight->uldid
		<< "\naircraft    = " << freight->aircraft
		<< "\nweight      = " << freight->weight
		<< "\ndestination = " << freight->destination.data()
		<< "\n";
}

inline string nextline() noexcept {
	string temp;
	getline(cin, temp);
	if (!cin.good()) {
		terminate();
	}
	return temp;
}

inline bool is_container_alignment(string str3) noexcept {
	return 0
		|| str3 == "AYF"
		|| str3 == "AYK"
		|| str3 == "AAA"
		|| str3 == "AYY";
}

inline bool is_pallet_alignment(string str3) noexcept {
	return 0
		|| str3 == "PAG"
		|| str3 == "PMC"
		|| str3 == "PLA";
}

/// Returns zero on failure
inline uint32_t parse_u32(string s) noexcept {
	auto const size{s.size()};
	auto const start{s.c_str()};

	uint32_t temp;

	if (start[0] == '-') {
		return 0;
	}

	char *last_parsed;
	temp = {strtoul(start, &last_parsed, 10)};

	auto const chars_parsed{last_parsed - start};
	if (temp && chars_parsed == size) {
		return temp;
	}

	return 0;
}

constexpr char const *type_to_string(Freight::Type t) noexcept {
	return t == Freight::Type::Container ? "container" : "pallet";
}
