/*
Cole Gannon
Winter 2021
Lab 02
Problem 2.1
Description of problem:
Take user input and store it in a Freight/Cargo struct.
Then output the struct contents.
*/
// can be compiled with -fno-exceptions -fno-rtti
#include <cstdint>
#include <cstdlib>
#include <string>
#include <array>
#include <iostream>
#define loop for(;;)

using namespace std;

struct Freight {
	string uld;
	string abbreviation;
	string uldid;
	string aircraft;
	uint32_t weight;
	string destination;
	// simple init constructor
	explicit Freight(
		string type,
		string abbreviation,
		string id,
		string aircraft,
		uint32_t weight,
		string dest
	) noexcept:
		uld{type},
		abbreviation{abbreviation},
		uldid{id},
		aircraft{aircraft},
		weight{weight},
		destination{dest}
	{};
};

inline Freight *input() noexcept;
inline void output(Freight const *) noexcept;
inline void safe_getline(string &) noexcept;
inline bool is_container_alignment(string) noexcept;
inline bool is_pallet_alignment(string) noexcept;
inline uint32_t parse_u32(string) noexcept;

int main() {
	Freight const *user_freight{input()};
	output(user_freight);
	delete user_freight;
	user_freight = {nullptr};
}

inline Freight *input() noexcept {
	string freight_type;
	cout << "What type of freight is it?\n";
	do {
		cout << "Enter either 'container' or 'pallet'\n> ";
		safe_getline(freight_type);
	} while (freight_type == "container" || freight_type == "pallet");

	string abbr;
	cout << "Enter the unit abbreviation:";
	loop {
		cout << "\n> ";
		safe_getline(abbr);

		if (abbr.length() != 3) {
			cout << "The abbreviation must be three characters!";
			continue;
		}

		if (is_container_alignment(abbr)) {
			if (freight_type == "container") break;

			cout << abbr << " is not an appropriate prefix for Containers!";
			continue;
		}

		if (is_pallet_alignment(abbr)) {
			if (freight_type == "pallet") break;

			cout << abbr << " is not an appropriate prefix for Pallets!";
			continue;
		}

		cout << abbr << " is not a valid prefix!";
	}

	string id;
	cout << "Enter the id:";
	safe_getline(id);

	cout << "Enter the aircraft that will be carrying the freight:\n> ";
	string aircraft;
	safe_getline(aircraft);

	uint32_t weight;
	cout << "Enter the weight of the freight in kilos:";
	loop {
		cout << "\n> ";
		string input;
		safe_getline(input);

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
	loop {
		cout << "\n> ";
		safe_getline(dest);

		if (dest.length() == 3) {
			break;
		}

		cout << "An IANA must be three characters!";
	}

	return new Freight(freight_type, abbr, id, aircraft, weight, dest);
};

inline void output(Freight const *freight) noexcept {
	cout
		<< "\nuld         = " << freight->uld
		<< "\nuldid       = " << freight->uldid
		<< "\naircraft    = " << freight->aircraft
		<< "\nweight      = " << freight->weight
		<< "\ndestination = " << freight->destination
		<< "\n";
}


/// Basically getline except that it exits if there's an error reading.
/// Typically this means that the user has sent SIGINT so we just exit.
inline void safe_getline(string &out) noexcept {
	getline(cin, out);
	if (!cin.good()) {
		terminate();
	}
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

/// String to integer parsing without exceptions using strtoul.
/// Returns zero on error.
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
