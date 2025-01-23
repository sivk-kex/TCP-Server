# Compiler and flags
CC = gcc
CFLAGS = -Wall -g

# Source and object files
SRCS = tcpserver.c
OBJS = tcpserver.o

# Target executable name
TARGET = tcpserver

# Libraries
LIBS = -lnsl

# Default target to build the program
all: $(TARGET)

# Rule to link object files to create the executable
$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET) $(LIBS)

# Rule to compile .c files into .o files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up generated files
clean:
	rm -f $(OBJS) $(TARGET)

# Rebuild the program
rebuild: clean all
