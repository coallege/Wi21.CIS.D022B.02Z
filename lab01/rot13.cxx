// clang++ rot13.cxx -fno-exceptions -fno-rtti -flto -Ofast -o rot13.exe
#include <cstdio>
#include <stdio.h>
#include <vcruntime.h>

/// Immutable string
using str = char const *;
/// Mutable string
using mut_str = char *;

static str program_name;

inline void menu() noexcept {
	printf(
		"Cole Gannon's %s\n"
		"Options:\n"
		"   E,e,Encode,encode: Take input and output the ROT13 of it.\n"
		"   D,d,Decode,decode: Exactly the same thing as encode.\n"
		"   Everything else  : Quit\n"
		"-> "
		, program_name
	);
	// I'm pretty sure that printf already flushes since there's a \n
	//fflush(stdout);
}

/// can return nullptr on error
/// caller owns memory, remember to delete[]
inline mut_str getline() noexcept {
	static const size_t buf_size = 256;
	// wow, I sure hope nobody ever decides to enter more than 256 characters
	char *buf = new char[buf_size];
	return fgets(buf, buf_size, stdin);
}

/// Should be consteval but can't use that yet
/// I probably also shouldn't be overriding cstdlib names but whatever
/// I want this to sometimes run at compile time so I gotta do what I gotta do.
constexpr size_t strlen(str str) noexcept {
	size_t i{};
	while (*str++ != '\0') {
		i++;
	}
	return i;
}

constexpr bool streq(str a, str b) noexcept {
	while (*a && *b) {
		if (*a++ != *b++) {
			return false;
		}
	}
	return true;
}

// Better pray that the compiler inlines this puppy
constexpr char rot13_c(char c) noexcept {
	// not A-z
	if (c < 'A' || c > 'z') {
		return c;
	}

	// uppercase branch
	if (c <= 'Z') {
		return ((c + 13 - 'A') % 13) + 'A';
	}

	// lowercase branch
	if (c >= 'a') {
		return ((c + 13 - 'a') % 13) + 'a';
	}

	return c;
}

/// does rot 13 in place
constexpr void rot13(mut_str str) noexcept {
	while (*str != '\0') {
		*str = rot13_c(*str);
	}
}

inline void rot13interactive() noexcept {
	puts("interactive");
}

struct DeferDelete {
	str data;
	DeferDelete(str data) noexcept: data(data) {};
	~DeferDelete() {
		delete[] this->data;
	}
};

int main(int, char const **argv) noexcept {
	if (strlen(*argv) > 20) {
		program_name = "ROT13";
	} else {
		program_name = *argv;
	}

	for(;;) {
		menu();
		// I'm glad it's mutable because we're about to do a lot of mutating
		mut_str choice = getline();
		// I am never going to remember to free this on all paths
		// so I am going to use RAII to do it for me.
		DeferDelete on(choice);
		size_t size = strlen(choice);

		fprintf(stderr, "size = %zu\n", size);
		// let's just make it lowercase so it's easier
		if (size == 0) {
			return 0;
		}

		fputs("size > 0", stderr);
		switch (choice[0]) {
			case 'E': choice[0] = 'e'; break;
			case 'D': choice[0] = 'd'; break;
		}

		if (size == 1) {
			switch (choice[0]) {
				case 'e':
				case 'd':
					rot13interactive();
					continue;
			}
		}

		fprintf(stderr, "strlen(encode) = %zu\n", strlen("encode"));
		if (size == strlen("encode")) {
			fprintf(stderr, "size == %zu\n", strlen("encode"));
			// luckily for me, encode and decode are the same number of characters
			// that means that if the string is anything that's not this
			// I already know that I don't have an option for that user input.
			// the only valid options are encode and decode.

			if (false
				|| streq(choice, "encode")
				|| streq(choice, "decode")
			) {
				rot13interactive();
				continue;
			}
		}

		return 0;
	}
	auto a = getline();
	printf("AAAA%s\n", a);
}
