#include <array>
#include <string>
#include <iostream>
#include <functional>
#include <string_view>
using namespace std;

using IATA = array<char const, 3>;

struct Freight {
	enum class Type {
		Container,
		Pallet,
	};
	// AYF12345IB, for example
	using id = array<char const, 10>;

	Type uld;
	id uldid;
	// we're still waiting for C++20 constexpr strings -_-
	string_view aircraft;
	int weight;
	IATA destination;
	explicit constexpr Freight(
		Type type, id id, string_view aircraft, int weight, IATA dest
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

template <class T>
auto prompt(char const *question, function<T(string)> const &&p) -> T {
	while (true) {
		cout << question << "\n> ";
		cin.clear();
		cin.ignore();
		string line;
		getline(cin, line);
		try {
			return p(line);
		} catch (...) {
			cout << "Invalid input! Try again.\n";
			continue;
		}
	}
}

Freight *input() noexcept {
	// when you
	// when you can't use fast_io to take input from the user

	auto type{
		prompt<Freight::Type>(
			"What type of freight is it?\n"
			"Enter either 'container' or 'pallet'",
			{[](string s) {
				if (s == "container") {
					return Freight::Type::Container;
				}
				if (s == "pallet") {
					return Freight::Type::Pallet;
				}
				throw 0;
			}}
		)
	};
}
