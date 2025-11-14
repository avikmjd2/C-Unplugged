# --- Variables ---

# Compiler to use
CC = gcc

# Compiler flags:
# -Wall -Wextra  = Show all and extra warnings (good practice)
# -g             = Include debug symbols
# -std=c11       = Use the C11 standard
CFLAGS = -Wall -Wextra -g -std=c11

# Linker flags:
# -lpthread = Link the POSIX threads library
# -lm       = Link the math library
# (These are commonly required by audio libraries like miniaudio)
LDFLAGS = -lpthread -lm

# The name of your final executable
TARGET = CUnplugged

# All your .c source files for the main program
SRCS = \
    main.c \
    audio.c \
    doc.c \
    global.c \
    libplay.c \
    playlist.c \
    song.c

# All your .h header files
# We list them all so 'make' knows to re-compile if a header changes
HEADERS = \
    audio.h \
    doc.h \
    global.h \
    libplay.h \
    miniaudio.h \
    playlist.h \
    song.h \
    structures.h

# Generates a list of .o object files from your .c files
# (e.g., main.c -> main.o)
OBJS = $(SRCS:.c=.o)

# --- Rules ---

# The default rule to build everything.
# This is what runs when you just type 'make'
.PHONY: all
all: $(TARGET)

# Rule to link all the .o files into the final executable
$(TARGET): $(OBJS)
	@echo "Linking $(TARGET)..."
	$(CC) $(OBJS) -o $(TARGET) $(LDFLAGS)
	@echo "Build complete: $(TARGET)"

# Generic pattern rule to compile any .c file into a .o file
# It says that each .o file depends on its .c file AND all the headers
%.o: %.c $(HEADERS)
	@echo "Compiling $<..."
	$(CC) $(CFLAGS) -c $< -o $@

# Rule to clean up all built files
# Run this by typing 'make clean'
.PHONY: clean
clean:
	@echo "Cleaning up..."
	rm -f $(TARGET) $(OBJS)