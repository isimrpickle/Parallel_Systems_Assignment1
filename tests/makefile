CC = gcc
CCFLAGS = -g -Wall

EXERCISE1_TARGET = updating_grid_tests

EXERCISE1_SRCS = updating_grid_tests.c ./../modules/updating_grid.c ./../modules/my_rand.c

ACUTEST_DIR = ./../header_files
ACUTEST_FLAGS = -I$(ACUTEST_DIR)
EXERCISE1_DIR = ./../header_files

all: $(EXERCISE1_TARGET)

$(EXERCISE1_TARGET): $(EXERCISE1_SRCS)
	$(CC) $(CCFLAGS) $(ACUTEST_FLAGS) -I$(EXERCISE1_DIR) -o $(EXERCISE1_TARGET) $(EXERCISE1_SRCS)

clean:
	rm -f $(EXERCISE1_TARGET)

run: $(EXERCISE1_TARGET)
	./$(EXERCISE1_TARGET)
