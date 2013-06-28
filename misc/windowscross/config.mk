CC=i686-pc-linux-gcc
CXX=i686-pc-linux-g++
ASM=i686-pc-linux-gcc
LD=i686-pc-linux-ld
AS=i686-pc-linux-as
EMU=qemu-system-i386
EMUTARGET=${TARGET}
GDB=i686-pc-linux-gdb
SED=sed
OBJDUMP=i686-pc-linux-objdump
DOCGEN=doxygen
GCC_EXEC_PREFIX=i686-pc-linux-

CFLAGS+=-fno-exceptions -fno-use-linker-plugin -ffreestanding
# -I${CYGWINPATH}/lib/gcc/i686-linux/4.6.1/include
CXXFLAGS+=${CFLAGS} -fno-rtti -nostdinc++
LDFLAGS+=-e entry -T misc/sections -Map ${BUILD}/link.map
ASMFLAGS+=-fno-use-linker-plugin
ASMEFLAGS+=-fno-use-linker-plugin

OBJDUMPFLAGS=-Cxd
EMUFLAGS+=-kernel
DEBUGFLAGS+=-S -gdb tcp::1234,nowait,nodelay,server,ipv4 
GDBFLAGS+=-x misc/gdb.script

