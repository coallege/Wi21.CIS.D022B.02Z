#include <array>
#include <string>
#include <iostream>
#include <functional>
#include <string_view>
using namespace std;

using IATA = array<char const, 3>;

struct Freight {
	enum class Type: char {
		Container = 0b010,
		Pallet = 0b100,
	};
	// AYF12345IB, for example

	Type uld;
	string uldid;
	// we're still waiting for C++20 constexpr strings -_-
	string aircraft;
	int weight;
	IATA destination;
	explicit Freight(
		Type type, string id, string aircraft, int weight, IATA dest
	) noexcept:
		uld(type),
		uldid(id),
		aircraft(aircraft),
		weight(weight),
		destination(dest)
	{};
};

// Arrange the functions in the order listed above.
// so it says...
Freight *input() noexcept;
void output(Freight *) noexcept;

int main() noexcept {
	Freight *freight{input()};
	output(freight);
	// input |> output |> ignore
}

template <class T, class fn_t>
auto prompt(char const *question, fn_t const &&fn) -> T {
	function<T(string)> actual_fn{fn};
	while (true) {
		cout << question << "\n> ";
		cin.clear();
		cin.ignore();
		string line;
		getline(cin, line);
		try {
			return actual_fn(line);
		} catch (...) {
			cerr << "Invalid input! Try again.\n";
			continue;
		}
	}
}

char id_type(string s) {
	if (s.length() != 10) {
		throw 0;
	}

	auto first3{s.substr(0, 3)};

	if (false
		|| s == "AYF"
		|| s == "AYK"
		|| s == "AAA"
		|| s == "AYY"
	) {
		// it's MY gun and I'm pointing it at MY foot
		return static_cast<char>(Freight::Type::Container);
	}

	if (false
		|| s == "PAG"
		|| s == "PMC"
		|| s == "PLA"
	) {
		return static_cast<char>(Freight::Type::Pallet);
	}

	return 0;
}

Freight *input() noexcept {
	// when you
	// when you can't use fast_io to take input from the user

	auto type{
		prompt<Freight::Type>(
			"What type of freight is it?\n"
			"Enter either 'container' or 'pallet'",
			[](string s) {
				if (s == "container") {
					return Freight::Type::Container;
				}
				if (s == "pallet") {
					return Freight::Type::Pallet;
				}
				throw 0;
			}
		)
	};

	auto id{
		prompt<string>(
			"Enter an appropriate 10 character id.",
			[type](string s){
				if (static_cast<char>(type) != id_type(s)) {
					cerr << "Inappropriate id " << s << " for type.\n";
					throw 0;
				}
				return move(s);
			}
		)
	};

	auto aircraft{
		prompt<string>(
			"Enter the aircraft that will be carrying the freight.\n",
			[](string s) { return move(s); }
		)
	};

	auto weight{
		prompt<int>(
			"Enter the weight of the freight.",
			[](string s) {
				auto w{stoi(s)};
				if (w < 0) {
					cerr << "Weight must be greater than zero!\n";
					throw 0;
				}
				return w;
			}
		)
	};

	auto dest{
		prompt<IATA>(
			"Enter the destination of the freight.",
			[](string s) {
				if (s.length() != 3) {
					cerr << "The destination must be an IATA!\n";
					throw 0;
				}
				return array{s[0], s[1], s[2]};
			}
		)
	};

	return new Freight(type, id, aircraft, weight, dest);
}
