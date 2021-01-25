#include <cstdint>
#include <cstdlib>
#include <string>
#include <array>
#include <iostream>

using namespace std;

using IANA = array<char, 3>;

struct Freight {
	enum class Type: uint8_t {
		Container,
		Pallet,
	};

	using weight_t = uint32_t;

	Freight::Type uld;
	string uldid;
	string aircraft;
	/// freight can't be less than 0 anyways
	weight_t weight;
	IANA destination;
	explicit Freight(
		Freight::Type type, string id, string aircraft, weight_t weight, IANA dest
	) noexcept:
		uld{type}, uldid{id}, aircraft{aircraft}, weight{weight}, destination{dest}
	{};
};

inline Freight *input() noexcept;
inline void output(Freight const *) noexcept;
int main() {
	auto user_freight{input()};
	output(user_freight);
}

inline Freight::Type id_type(string const s) noexcept;

inline Freight *input() noexcept {
	Freight::Type freight_type;
	cout << "What type of freight is it?\n";
	while (true) {
		cout << "Enter eight 'container' or 'pallet'\n> ";
		string input;
		getline(cin, input);
		if (cin.bad()) {
			return nullptr;
		}

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
	cout << "Enter an appropriate id:\n";
	while (true) {
		cout << "> ";
		getline(cin, id);
		if (cin.bad()) {
			return nullptr;
		}

		auto first3{id.substr(0, 3)};

		if (0
			|| first3 == "AYF"
			|| first3 == "AYK"
			|| first3 == "AAA"
			|| first3 == "AYY"
		) {
			if (freight_type == Freight::Type::Container) {
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
			if (freight_type == Freight::Type::Pallet) {
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
		getline(cin, input);
		if (cin.bad()) {
			return nullptr;
		}

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
		getline(cin, input);
		if (input.length() == 3) {
			dest = {input[0], input[1], input[2]};
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

inline void output(Freight const *) noexcept {
	
}
