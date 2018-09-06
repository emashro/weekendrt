# Makefile

PROGRAM = rt
SRCS = main.cpp hitablelist.cpp sphere.cpp
OBJS = $(SRCS:.cpp=.o)
CPP = clang++
CPPFLAGS = -Wall -O2
.SUFFIXES: .cpp .o

.PHONY: all
all: depend $(PROGRAM)

$(PROGRAM): $(OBJS)
	$(CPP) -o $(PROGRAM) $^

.cpp.o:
	$(CPP) $(CPPFLAGS) -c $<

.PHONY: clean
clean:
	$(RM) $(PROGRAM) $(OBJS) depend.inc

.PHONY: depend
depend: $(SRCS)
	-@ $(RM) depend.inc
	-@ for i in $^; do $(CPP) -MM $$i >> depend.inc; done

-include depend.inc
