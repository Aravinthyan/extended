# C compiler to use
CC = gcc

# compile-time flags
CFLAGS = -std=c17 -W -Werror -pedantic

# define the C source files
SRCS = main.c extended_io.c # all source files (.cpp) 

# C object files 
# Replace suffix .c with .o suffix for each source file
OBJS = $(SRCS:.c=.o)

# define the executable file 
EXE = final 

all: $(EXE)

debug: $(OBJS)
	$(CC) -g $(CFLAGS) $(OBJS) -o $(EXE)

$(EXE): $(OBJS) 
	$(CC) $(CFLAGS) $(OBJS) -o $(EXE)

# Suffix replacement rule, .c -> .o
# Automatic variables $< (.c) and $@ (.o)
.c.o:
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm *.o $(EXE)
