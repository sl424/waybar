# Compiler flags
CFLAGS = -Wall -Werror

# Project files
TARGET = vpn
SRCS = $(TARGET).c

# Debug build settings
DBGCC = clang
DBGEXE = $(TARGET)_debug
DBGCFLAGS = -O0 -g -Wsystem-headers -pedantic-errors -fuse-ld=lld

# Release build settings
RELCC = gcc
RELEXE = $(TARGET)
RELCFLAGS = -march=x86-64 -mtune=generic -O2 -pipe -fno-plt -fstack-protector-all

# Default build
all: clean release

# Debug rules
debug: $(DBGEXE)

$(DBGEXE): $(SRCS)
	$(DBGCC) $(CFLAGS) $(DBGCFLAGS) -o $(DBGEXE) $(SRCS)

# Release rules
release: $(RELEXE)

$(RELEXE): $(SRCS)
	$(RELCC) $(CFLAGS) $(RELCFLAGS) -o $(RELEXE) $(SRCS)

# Clean up files
clean:
	rm -f $(DBGEXE) $(RELEXE)

