iba_2.1.release.exe: iba_2.1.cxx
	clang++ -fno-exceptions -fno-rtti -O2 -Wall $< -o $@

iba_2.2.release.exe: iba_2.2.cxx
	clang++ -O2 -Wall $< -o $@

run~2.1: iba_2.1.release.exe
	@-$<

run~2.2: iba_2.2.release.exe
	@-$<
