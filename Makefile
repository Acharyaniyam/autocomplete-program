# Define the compiler and compiler flags
CC = gcc
CFLAGS = -Wall -g

# Define the target executable
TARGET = auto

# Build the target executable
all: $(TARGET)

$(TARGET): main.c
    $(CC) $(CFLAGS) -o $(TARGET) main.c

# Clean up the build files
clean:
    rm -f $(TARGET)

