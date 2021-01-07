/*
Cole Gannon
Winter 2021
Lab 01
Problem 1?
Description of problem:
Build a rot13 interface for "encryption" and "decryption".
*/
#include <cstdio>

/// Immutable string
using str = char const *;
/// Mutable string
using mut_str = char *;

// in-house string functions
constexpr bool streq(str a, str b) noexcept;
constexpr size_t strlen(str str) noexcept;

// in-house io
inline void print(str str) noexcept;
inline mut_str getline() noexcept;

/// Core rot13 algo
constexpr char rot13_c(char c) noexcept;
/// Does rot13 in place
constexpr void rot13(mut_str str) noexcept;
inline void rot13interactive() noexcept;
/// Never run at runtime, for testing only
/// Tests if the rot13 of str a is str b
constexpr bool rot13_eq(str a, str b) noexcept;

int main(int, char const *argv[]) noexcept {
	// menu
	printf(
		"Cole Gannon's %s\n"
		"Options:\n"
		"   E,e,Encode,encode: Take input and output the ROT13 of it.\n"
		"   D,d,Decode,decode: Exactly the same thing as encode.\n"
		"   Everything else  : Quit\n"
		, strlen(argv[0]) > 20 ? "ROT13" : argv[0]
	);

	// unfortunate, printf flushes stdout and we do it again...
	for(;;) {
		print("OPTION> ");

		// remember to delete before leaving scope!
		mut_str choice = getline();

		if (choice == nullptr) {
			// If this is null, it's probably because the user hit ctrl+c
			// we can let them off with a zero error code
			return 0;
		}

		// I am never going to remember to free this on all paths
		// so I am going to use RAII to do it for me.
		size_t len = strlen(choice);
		// let's slice off the newline at the end
		size_t last_index = len - 1;
		choice[last_index] = '\0';
		// and since we have, let's adjust len
		len--;

		if (len == 0) {
			return 0;
		}

		// let's just make it lowercase so it's easier
		switch (choice[0]) {
			case 'E': choice[0] = 'e'; break;
			case 'D': choice[0] = 'd'; break;
		}

		if (len == 1) {
			switch (choice[0]) {
				case 'e':
				case 'd':
					delete[] choice;
					rot13interactive();
					continue;
			}
		}

		if (len == strlen("encode")) {
			// luckily for me, encode and decode are the same number of characters
			// that means that if the string is anything that's not this
			// I already know that I don't have an option for that user input.
			// the only valid options are encode and decode.
			if (false
				|| streq(choice, "encode")
				|| streq(choice, "decode")
			) {
				delete[] choice;
				rot13interactive();
				continue;
			}
		}

		return 0;
	}
}

// Better pray that the compiler inlines this puppy
constexpr char rot13_c(char c) noexcept {
	// not A-z
	if (c < 'A' || c > 'z') {
		return c;
	}

	// uppercase branch
	if (c <= 'Z') {
		return ((c + 13 - 'A') % 26) + 'A';
	}

	// lowercase branch
	if (c >= 'a') {
		return ((c + 13 - 'a') % 26) + 'a';
	}

	return c;
}

constexpr void rot13(mut_str str) noexcept {
	while (*str != '\0') {
		*str = rot13_c(*str);
		str++;
	}
}

inline void rot13interactive() noexcept {
	print("<- ");
	mut_str line = getline();

	if (line == nullptr) {
		// not much we can do here if the line is null
		// sometimes the user hit ctrl+c
		fputs("\n", stdout);
		return;
	}

	rot13(line);
	// we can forget the newline since getline already includes one
	printf("-> %s", line);
	delete[] line;
}

/// Always calls fflush after fwrite
inline void print(str str) noexcept {
	// this could fail
	// too bad!
	fwrite(str, sizeof(char), strlen(str), stdout);
	fflush(stdout);
}

constexpr bool rot13_eq(str a, str b) noexcept {
	size_t len = strlen(a);
	size_t blen = strlen(b);

	if (blen != len) {
		return false;
	}

	while (len --> 0) {
		if (rot13_c(a[len]) != b[len]) {
			return false;
		}
	}

	return true;
}

/// can return nullptr on error
/// caller owns memory, remember to delete[]
inline mut_str getline() noexcept {
	static const size_t buf_size = 256;
	// wow, I sure hope nobody ever decides to enter more than 256 characters
	char *buf = new char[buf_size];
	return fgets(buf, buf_size, stdin);
}

constexpr bool streq(str a, str b) noexcept {
	while (*a && *b) {
		if (*a++ != *b++) {
			return false;
		}
	}
	return true;
}

constexpr size_t strlen(str str) noexcept {
	size_t i{};
	while (*str++ != '\0') {
		i++;
	}
	return i;
}

static_assert(rot13_eq("ALPHABET", "NYCUNORG"));
static_assert(rot13_eq("NYCUNORG", "ALPHABET"));
static_assert(rot13_eq("TAF VF"  , "GNS IS"  ));
static_assert(rot13_eq("paddrpf" , "cnqqecs" ));
static_assert(rot13_eq("zvpebor" , "microbe" ));
static_assert(rot13_eq(" ,.?!"   , " ,.?!"   ));
