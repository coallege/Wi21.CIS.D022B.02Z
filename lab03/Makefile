one: run~lab_3.1
	@

two: run~3.1
	@

%.exe: %.cxx
	@clang++ -Wall $< -o $@

%.debug.exe: %.cxx
	@clang++ -Wall -g $< -o $@

%.release.exe: %.cxx
	@clang++ -O2 -Wall $< -o $@

run~%: %.exe
	@-./$<

.SECONDARY:
