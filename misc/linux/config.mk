CC=gcc
CXX=g++
ASM=gcc
LD=ld
EMU=qemu-system-i386
EMUTARGET=${TARGET}
GDB=gdb
SED=sed
OBJDUMP=objdump
DOCGEN=doxygen

CFLAGS+=-fno-exceptions -fno-stack-protector
CXXFLAGS+=${CFLAGS} -fno-rtti -nostdinc++
LDFLAGS=-e entry -T misc/sections

OBJDUMPFLAGS=-Cxd
EMUFLAGS+=-no-kvm -net none -vga std -kernel
DEBUGFLAGS+=-s -S
GDBFLAGS+=-x misc/gdb.script
