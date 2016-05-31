#
# Makefile
#
# Computer Science 50
# Problem Set 5
#


# compiler to use
CC = clang

# flags to pass compiler
CFLAGS = -ggdb3 -O0 -Qunused-arguments -std=c11 -Wall -Werror

# name for executable
EXE = speller

# space-separated list of header files
HDRS = dictionary.h List.h PrimeHelper.h Slot.h HashSet.h

# space-separated list of libraries, if any,
# each of which should be prefixed with -l
LIBS = -lm

# space-separated list of source files
SRCS = speller.c dictionary.c List.c PrimeHelper.c Slot.c HashSet.c

# automatically generated list of object files
OBJS = $(SRCS:.c=.o)

# default target
$(EXE): $(OBJS) $(HDRS) Makefile
	$(CC) $(CFLAGS) -o $@ $(OBJS) $(LIBS)

# dependencies 
$(OBJS): $(HDRS) Makefile

# housekeeping
clean:
	rm -f core $(EXE) *.o
