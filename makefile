CC = gcc
CFLAGS = -g -Wall -fopenmp

# Define target
EXERCISE1_TARGET = exercise1

# Source files
EXERCISE1_SRCS = modules/exercise1.c modules/updating_grid.c modules/my_rand.c

# Include directory for header files
EXERCISE1_DIR = header_files

# Build all
all: $(EXERCISE1_TARGET)

# Build target
$(EXERCISE1_TARGET): $(EXERCISE1_SRCS)
	$(CC) $(CFLAGS) -I$(EXERCISE1_DIR) -o $(EXERCISE1_TARGET) $(EXERCISE1_SRCS)

# Clean build files
clean:
	rm -f $(EXERCISE1_TARGET)

# Run the program
run: $(EXERCISE1_TARGET)
	./$(EXERCISE1_TARGET)
