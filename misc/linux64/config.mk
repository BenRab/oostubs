CC=gcc
CXX=g++
ASM=gcc
LD=g++
EMU=qemu-system-i386
#EMU=qemu-kvm
EMUTARGET=${TARGET}
GDBSRV=gdbserver
GDB=gdb
SED=sed
OBJDUMP=objdump
DOCGEN=doxygen

#CFLAGS+=-fno-exceptions -m32 -fno-stack-protector
#CXXFLAGS+=${CFLAGS} -fno-rtti -nostdinc++
#LDFLAGS=-e entry -T misc/sections -melf_i386
ASMFLAGS := 
CFLAGS   := -pthread -Wall -g
CXXFLAGS := ${CFLAGS}
LDFLAGS  := -lncurses ${CFLAGS}

OBJDUMPFLAGS=-Cxd
EMUFLAGS+=-no-kvm -net none -vga std -kernel
DEBUGFLAGS+=-s -S
GDBFLAGS+=-x misc/gdb.script
