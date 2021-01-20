run: rot13.exe
	@cls
	@$<

rot13_iostream.exe: rot13_iostream.cxx
	clang++ $< -o $@

braindeath: rot13_iostream.exe
	@$<

rot13.exe: rot13.cxx
	clang++ $< -std=c++17 -Wall -fno-exceptions -fno-rtti -fuse-ld=lld-link -Ofast -o $@

.PHONY: run
