# Compiler flags
CFLAGS = -Wall

# Project files
TARGET = wbm_battery
SRCS = $(TARGET).c

# Debug build settings
DBGCC = clang
DBGEXE = $(TARGET)_debug
DBGCFLAGS = -O0 -g -Wsystem-headers -pedantic-errors -fuse-ld=lld

# Release build settings
RELCC = gcc
RELEXE = $(TARGET)
# See https://developers.redhat.com/blog/2018/03/21/compiler-and-linker-flags-gcc/
# Excluded flags:
# -fpic -shared: only for shared libraries
# -fplugin=annobin: only for generating data for "hardening quality control"
# -fasynchronous-unwind-tables: only for debugging/performance analysis
RELCFLAGS = -Werror=format-security -Werror=implicit-function-declaration -march=x86-64 -mtune=generic -O2 -pipe -fno-plt -D_FORTIFY_SOURCE=2 -fexceptions -fpie -Wl,-pie -fstack-clash-protection -fstack-protector-strong -fcf-protection -Wl,-z,defs -Wl,-z,now -Wl,-z,relro -flto

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

