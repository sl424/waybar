# the compiler
CC = clang

# compiler flags:
# -O2: turn on level 2 optimizations
# -Werror: turn warnings into errors
# -Wsystem-headers: turn on warnings from system headers
# -pedantic-errors: error on language extensions
# -fuse-ld=lld: use the LLVM linker
CFLAGS = -O2 -Werror -Wsystem-headers -pedantic-errors -fuse-ld=lld

# the build target executable:
TARGET = battery

all: $(TARGET)

$(TARGET): $(TARGET).c
	$(CC) $(CFLAGS) -o $(TARGET) $(TARGET).c

clean:
	$(RM) $(TARGET)
