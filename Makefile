cxx   := clang++
proot := $(patsubst %/,%,$(dir $(lastword $(MAKEFILE_LIST))))

space_cat = $(shell $(proot)/misc/space_cat.exe $(proot)/$(1))

cxx_flags  ?= $(call space_cat,compile_flags.txt)
cxx_dflags ?= -g
cxx_rflags ?= -O2

ifeq ($(OS), Windows_NT)
	exe=exe
	cxx_flags += -fuse-ld=lld-link
else
	exe=elf
endif

root-default:
	@echo you$$ make run~program

%.$(exe): %.cxx
	$(cxx) $(cxx_flags) $< -o $@

%.debug.$(exe): %.cxx
	@$(cxx) $(cxx_flags) $(cxx_dflags) $< -o $@

%.release.$(exe): %.cxx
	@$(cxx) $(cxx_flags) $(cxx_rflags) $< -o $@

run~%: %.$(exe)
	@-./$<

debug~%: %.debug.$(exe)
	@

halp/%.exe: halp/%.cpp
	@$(cxx) $(cxx_flags) $< -o $@

halp~%: halp/%.exe
	@-./$<

revision:
	-node $(proot)/misc/revision.js

.SECONDARY:

.PHONY: root-default run~% revision
