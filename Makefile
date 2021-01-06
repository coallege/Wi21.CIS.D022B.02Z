proot := $(dir $(lastword $(MAKEFILE_LIST)))
flags := $(shell misc/kinda_cat.exe compile_flags.txt)

default:
	@echo $(flags)
	@echo you$$ make run~program.exe

%.exe: %.cxx
	clang++ $(flags) $< -o $@

run~%: %.exe
	@echo --- BEG $< ---
	@$<
	@echo --- END $< ---

.SECONDARY:
