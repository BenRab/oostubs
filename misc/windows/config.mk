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

CFLAGS+=-fno-exceptions -fno-leading-underscore -fno-stack-protector
CXXFLAGS+=${CFLAGS} -fno-rtti -nostdinc++
LDFLAGS+=-e entry -T misc/windows/sections.txt -Map ${BUILD}/link.map --file-alignment 0x200
# --disable-long-section-names

OBJDUMPFLAGS=-Cxd
EMUFLAGS+=-kernel
DEBUGFLAGS+=-S -gdb tcp::1234,nowait,nodelay,server,ipv4 
GDBFLAGS+=-x misc/gdb.script
