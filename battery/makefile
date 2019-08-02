# the compiler
CC = clang

# compiler flags:
# -O0: set optimization to level 0
# -g: add debugging information
# -Werror: turn warnings into errors
# -Wsystem-headers: turn on warnings from system headers
# -pedantic-errors: error on language extensions
# -fuse-ld=lld: use the LLVM linker
CFLAGS = -O0 -g -Werror -Wsystem-headers -pedantic-errors -fuse-ld=lld

# the build target executable:
TARGET = battery

all: $(TARGET)

$(TARGET): $(TARGET).c
	$(CC) $(CFLAGS) -o $(TARGET) $(TARGET).c

clean:
	$(RM) $(TARGET)
