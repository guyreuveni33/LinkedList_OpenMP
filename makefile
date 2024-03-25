CC = gcc
CFLAGS = -std=c99 -fsanitize=address -fno-omit-frame-pointer -g $(OPENMP_FLAGS)
LDFLAGS = -fsanitize=address $(OPENMP_LIBS)

# Detect if OpenMP is available and set the appropriate compiler and linker flags
OPENMP_FLAGS = $(shell gcc -fopenmp -dM -E - < /dev/null | grep -q _OPENMP && echo '-fopenmp')
OPENMP_LIBS = $(shell gcc -fopenmp -dM -E - < /dev/null | grep -q _OPENMP && echo '-fopenmp')

# Name of your executable. Omit or set to a.out for the default a.out name.
EXEC = a.out

# Source files
SRC = main.c linkedList.c

# Object files are the same as source files, but with .o extension
OBJ = $(SRC:.c=.o)

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) $(OBJ) -o $@ $(LDFLAGS)

%.o: %.c
	$(CC) -c $< -o $@ $(CFLAGS)

clean:
	rm -f $(OBJ) $(EXEC)

