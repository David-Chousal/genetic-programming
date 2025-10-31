# Sin-Yaw Wang <swang24@scu.edu>
CXX=c++
OPT=-g
STD=-std=c++20
CXXFLAGS=$(OPT) $(STD)

%.o:	%.cxx
	$(CXX) -c $(CXXFLAGS) $<

SRCS=select.cxx arena.cxx dna.cxx life.cxx main.cxx
OBJS=$(SRCS:.cxx=.o)
ALL=genetic dnatest

all: $(ALL)

genetic:	$(OBJS)
	$(CXX) -o $@ $(CXXFLAGS) $+

dnatest:	dnamain.o dna.o
	$(CXX) -o $@ $(CXXFLAGS) $+

clean:
	/bin/rm -f $(ALL) $(OBJS) dnamain.o
	/bin/rm -rf $(ALL:=.dSYM)

depend: $(SRCS) 
	TMP=`mktemp -p .`; export TMP; \
	sed -e '/^# DEPENDENTS/,$$d' Makefile > $$TMP; \
	echo '# DEPENDENTS' >> $$TMP; \
	$(CXX) -MM $+ >> $$TMP; \
	/bin/mv -f $$TMP Makefile

# DEPENDENTS
select.o: select.cxx rng.h dna.h life.h select.h arena.h
arena.o: arena.cxx rng.h dna.h life.h select.h arena.h
dna.o: dna.cxx rng.h dna.h
life.o: life.cxx rng.h dna.h life.h
main.o: main.cxx rng.h dna.h life.h select.h arena.h
dnamain.o: dnamain.cxx rng.h dna.h
