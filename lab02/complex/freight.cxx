#include <array>
#include <exception>
#include <string>
#include <iostream>
#include <functional>
#include <string_view>
using namespace std;

struct Freight {
	enum class Type {
		Container,
		Pallet,
	};

	Type uld;
	string uldid;
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

// it said main function first
inline Freight *input() noexcept;
inline void output(Freight *) noexcept;

int main() noexcept {
	Freight *freight{input()};
	output(freight);
}

constexpr char const *to_string(Freight::Type t) noexcept {
	return t == Freight::Type::Container ? "Container" : "Pallet";
}

inline Freight::Type id_type(string s) {
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
		return Freight::Type::Container;
	}

	if (false
		|| first3 == "PAG"
		|| first3 == "PMC"
		|| first3 == "PLA"
	) {
		return Freight::Type::Pallet;
	}

	throw exception("Invalid abbreviation");
}

template <class T, class fn_t>
inline auto prompt(char const *question, fn_t const &&fn) noexcept -> T {
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

inline Freight *input() noexcept {
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
				if (type != id_type(s)) {
					cerr
						<< "Inappropriate id " << s << " for type "
						<< to_string(type) << "!\n\n";
					throw 0;
				}
				return s;
			}
		)
	};

	auto aircraft{
		prompt<string>(
			"Enter the aircraft that will be carrying the freight.",
			[](string s) { return s; }
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
				return s;
			}
		)
	};

	return new Freight(type, move(id), move(aircraft), weight, move(dest));
}

inline void output(Freight *freight) noexcept {
	cout << ""
		"uld         = " << to_string(freight->uld) << "\n"
		"uldid       = " << freight->uldid << "\n"
		"aircraft    = " << freight->aircraft << "\n"
		"weight      = " << freight->weight << "\n"
		"destination = " << freight->destination << "\n";
}
