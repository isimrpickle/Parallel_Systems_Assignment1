CC = gcc
CFLAGS = -g -Wall -fopenmp

#define the targets
EXERCISE1_TARGET = modules/exercise1
EXERCISE2_TARGET = modules/exercise2

#source files
EXERCISE1_SRCS = modules/exercise1.c modules/updating_grid.c modules/my_rand.c
EXERCISE2_SRCS = modules/exercise2.c 

#linking the header files
EXERCISE1_DIR = header_files



all: $(EXERCISE1_TARGET) $(EXERCISE2_TARGET)


$(EXERCISE1_TARGET): $(EXERCISE1_SRCS)
	$(CC) $(CFLAGS) -I$(EXERCISE1_DIR) -o $(EXERCISE1_TARGET) $(EXERCISE1_SRCS)

$(EXERCISE2_TARGET): $(EXERCISE2_SRCS)
	$(CC) $(CFLAGS) -I$(EXERCISE1_DIR) -o $(EXERCISE2_TARGET) $(EXERCISE2_SRCS)



#clean build files
clean:
	rm -f $(EXERCISE1_TARGET) $(EXERCISE2_TARGET)

