# Makefile

PROGRAM = rt
SRCS = main.cpp hitable.cpp hitablelist.cpp sphere.cpp material.cpp camera.cpp aabb.cpp bvh.cpp perlin.cpp texture.cpp rect.cpp stb_image.cpp box.cpp
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
