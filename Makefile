BINDIR = bin
OBJDIR = obj

CXX = g++
CC  = gcc

release: OPTIMISATION := -g0 -O3
release: tests.elf

debug: OPTIMISATION := -g3 -O0
debug: tests.elf

CXXFLAGS = $(OPTIMISATION) -no-pie -Wall -Werror -Wfatal-errors -mavx -pthread -std=c++17

INCDIRS = inc inc/lak/inc
LIBDIRS = $(OBJDIR)
LIBS    = dl stdc++fs

tests.elf: | $(BINDIR) $(OBJDIR)
	$(CXX) $(CXXFLAGS) -o $(BINDIR)/tests.elf src/main.cpp $(foreach D,$(INCDIRS),-I$D ) $(foreach D,$(LIBDIRS),-L$D ) $(foreach L,$(LIBS),-l$L )

.PHONY: tests.elf

clean:
	rm -f $(BINDIR)/*
	rm -f $(OBJDIR)/*

$(BINDIR):
	mkdir $(BINDIR)

$(OBJDIR):
	mkdir $(OBJDIR)
