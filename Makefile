cxx   := clang++
proot := $(dir $(lastword $(MAKEFILE_LIST)))

space_cat = $(shell $(proot)/misc/space_cat.exe $(proot)/$(1))

cxx_flags      = $(call space_cat,compile_flags.txt)
release_flags ?= $(call space_cat,release_flags.txt)

root-default:
	@echo you$$ make run~program.exe

%.debug.exe: %.cxx
	$(cxx) $(cxx_flags) -g $< -o $@

run~%: %.debug.exe
	@$<

%.release.exe: %.cxx
	$(cxx) $(cxx_flags) $(release_flags) $< -o $@

run-release~%: %.release.exe
	@$<

.SECONDARY:

.PHONY: root-default run run-release
