run: rot13.exe
	@cls
	@$<

rot13.exe: rot13.cxx
	clang++ $< -std=c++17 -Wall -fno-exceptions -fno-rtti -fuse-ld=lld-link -Ofast -o $@

.PHONY: run
