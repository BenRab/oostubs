# define your prefix to the corss compiler
CPREFIX=
#CPREFIX=./misc/osxcross/linux32/bin/i586-pc-linux-

CC=${CPREFIX}gcc
CXX=${CPREFIX}g++
ASM=${CPREFIX}gcc
LD=${CPREFIX}ld
EMU=qemu-system-i386
EMUTARGET=${TARGET}
GDB=gdb
SED=sed
OBJDUMP=objdump
DOCGEN=/Applications/Doxygen.app/Contents/Resources/doxygen

CFLAGS+=-fno-exceptions
CXXFLAGS+=${CFLAGS} -fno-rtti -nostdinc++
LDFLAGS=-e entry -T misc/sections -melf_i386

OBJDUMPFLAGS=-Cxd
EMUFLAGS+=-no-kvm -net none -vga std -kernel
DEBUGFLAGS+=-s -S
GDBFLAGS+=-x misc/gdb.script
