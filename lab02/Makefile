lab_2.1.release.exe: lab_2.1.cxx
	clang++ -fno-exceptions -fno-rtti -O2 -Wall $< -o $@

lab_2.2.release.exe: lab_2.2.cxx
	clang++ -O2 -Wall $< -o $@

run~2.1: lab_2.1.release.exe
	@-$<

run~2.2: lab_2.2.release.exe
	@-$<
