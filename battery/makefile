# the compiler
CC = clang

# compiler flags:
# -O2: turn on level 2 optimizations
# -Werror: turn warnings into errors
# -Wsystem-headers: turn on warnings from system headers
# -pedantic-errors: error on language extensions
CFLAGS = -O2 -Werror -Wsystem-headers -pedantic-errors

# the build target executable:
TARGET = battery

all: $(TARGET)

$(TARGET): $(TARGET).c
	$(CC) $(CFLAGS) -o $(TARGET) $(TARGET).c

clean:
	$(RM) $(TARGET)
