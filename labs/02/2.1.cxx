#include <array>
#include <cstddef>
#include <exception>
#include <string>
#include <iostream>
#include <functional>
#include <string_view>
using namespace std;

struct Freight {
	enum class Type: int {
		Container = 0b010,
		Pallet = 0b100,
	};

	static char const * type_to_string(Type t) {
		return t == Type::Container ? "Container" : "Pallet";
	}
	// AYF12345IB, for example

	Type uld;
	string uldid;
	// we're still waiting for C++20 constexpr strings -_-
	string aircraft;
	int weight;
	string destination;
	explicit Freight(
		Type type, string id, string aircraft, int weight, string dest
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
		string line;
		getline(cin, line);
		try {
			return actual_fn(line);
		} catch (exception const &ex) {
			cerr << ex.what() << "!\n\n";
		} catch (...) {}
	}
}

int id_type(string s) {
	if (s.length() != 10) {
		throw exception("Length is too short");
	}

	auto first3{s.substr(0, 3)};

	if (false
		|| first3 == "AYF"
		|| first3 == "AYK"
		|| first3 == "AAA"
		|| first3 == "AYY"
	) {
		// it's MY gun and I'm pointing it at MY foot
		return static_cast<int>(Freight::Type::Container);
	}

	if (false
		|| first3 == "PAG"
		|| first3 == "PMC"
		|| first3 == "PLA"
	) {
		return static_cast<int>(Freight::Type::Pallet);
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
				throw exception("Invalid selection");
			}
		)
	};

	auto id{
		prompt<string>(
			"Enter an appropriate 10 character id.",
			[type](string s){
				if (static_cast<int>(type) != id_type(s)) {
					cerr
						<< "Inappropriate id " << s << " for type "
						<< Freight::type_to_string(type) << "!\n\n";
					throw 0;
				}
				return move(s);
			}
		)
	};

	auto aircraft{
		prompt<string>(
			"Enter the aircraft that will be carrying the freight.",
			[](string s) { return move(s); }
		)
	};

	auto weight{
		prompt<int>(
			"Enter the weight of the freight.",
			[](string s) {
				auto w{stoi(s)};
				if (w < 0) {
					throw exception("Weight must be greater than zero");
				}
				return w;
			}
		)
	};

	auto dest{
		prompt<string>(
			"Enter the destination of the freight.",
			[](string s) {
				if (s.length() != 3) {
					throw exception("The destination must be three characters");
				}
				return move(s);
			}
		)
	};

	return new Freight(type, id, aircraft, weight, dest);
}

void output(Freight *freight) noexcept {
	cout << ""
		"uld         = " << Freight::type_to_string(freight->uld) << "\n"
		"uldid       = " << freight->uldid << "\n"
		"aircraft    = " << freight->aircraft << "\n"
		"weight      = " << freight->weight << "\n"
		"destination = " << freight->destination << "\n";
}
