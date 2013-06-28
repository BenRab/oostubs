BUILD=./build
BIN=./bin
SRC=./src
INTERNAL=${SRC}/internal
DOC=./doc
INCLUDE=./include

CXX:=@${CXX}
CC:=@${CC}
ASM:=@${ASM}
LD:=@${LD}
EMU:=@${EMU}
RAWGDB:=${GDB}
GDB:=@${GDB}
SED:=@${SED}
OBJDUMP:=@${OBJDUMP}

#INTERNAL_OBJECTS := $(addprefix ${BUILD}/, boot.o cppInit.o pow.o compat.o)
#INTERNAL_OBJECTS := $(addprefix ${BUILD}/, boot.o)
SOURCES          := $(wildcard ${SRC}/*/*.cc ${SRC}/*.cc ${SRC}/*/*.c ${SRC}/*/*.S )
HEADERS          := $(filter %.h, $(wildcard ${INCLUDE}/*/*.h))
DOXS             := $(wildcard ${DOC}/*.dox)
BOOT_OBJECT      := ${BUILD}/boot.o
SYSTEM_OBJECTS   := $(filter-out ${BOOT_OBJECT}, $(addprefix ${BUILD}/,$(filter-out ${OBJECT_IGNORE}, $(addsuffix .o,$(basename $(notdir ${SOURCES}))))))
DEPS             := $(addsuffix .d,${SYSTEM_OBJECTS})
OBJECTS          := ${BOOT_OBJECT} ${SYSTEM_OBJECTS}
TARGET           := ${BIN}/${TARGET}
EMTARGET         := ${BIN}/${EMUTARGET}
INCPATHS         := $(addprefix -I,${INCLUDE} ${INCPATHS})
LIBPATHS         := $(addprefix -L,${LIBPATHS})
LIBS             := $(addprefix -l,${LIBS})
ASMFLAGS         := $(foreach VAR, ${ASMFLAGS}, -Wa,${VAR})
BUILD_GARBAGE    := $(wildcard *~ *.sw?) ${BIN} ${BUILD} $(wildcard *.dump)
DOC_GARBAGE      := ${DOC}/html ${DOC}/log
GARBAGE          := $(BUILD_GARBAGE) $(DOC_GARBAGE)

.PHONY: all clean run debug_server debug_client doc dump cleanDoc cleanBuild

vpath %.cc ${INTERNAL} ${SRC} ${SRC}/machine ${SRC}/user ${SRC}/object ${SRC}/syscall ${SRC}/thread ${SRC}/meetings ${SRC}/guard ${SRC}/device
vpath %.c  ${INTERNAL} ${SRC}/machine 
vpath %.S  ${INTERNAL} ${SRC}/machine

all: ${TARGET}

${TARGET}: ${OBJECTS} | ${BIN}
	@echo "(LD   ) $@ <- [$(notdir ${SYSTEM_OBJECTS})]"
	${LD} ${LDFLAGS} ${OBJECTS} -o $@ -lncurses

${BUILD}/%.o: %.S Makefile | ${BUILD}
	@echo "(AS   ) $@ <- $<"
	${CC} -M -MT $@ ${ASMFLAGS} $< ${INCPATHS} -MF $@.d
	${CC} -c ${ASMFLAGS} $< ${INCPATHS} -o $@

${BUILD}/%.o: %.c Makefile | ${BUILD}
	@echo "(CC   ) $@ <- $<"
	${CC} -M -MT $@ ${CFLAGS} $< ${INCPATHS} -MF $@.d
	${CC} -c ${CFLAGS} $< ${INCPATHS} -o $@

${BUILD}/%.o: %.cc Makefile | ${BUILD}
	@echo "(CXX  ) $@ <- $<"
	${CXX} -M -MT $@ ${CXXFLAGS} $< ${INCPATHS} -MF $@.d
	${CXX} -c ${CXXFLAGS} $< ${INCPATHS} -o $@

dump: $(notdir ${TARGET}).dump

$(notdir ${TARGET}).dump: ${TARGET}
	@echo "(DUMP ) $@ <- $<"
	${OBJDUMP} ${OBJDUMPFLAGS} $< > $@

%.dump:	${BUILD}/%.o
	@echo "(DUMP ) $@ <- $<"
	${OBJDUMP} ${OBJDUMPFLAGS} $< > $@

${BIN} ${BUILD}:
	@mkdir -p $@

clean:
	@echo "(CLEAN)"
	@rm -rf ${GARBAGE}

cleanDoc:
	@echo "(CLEAN doc)"
	@rm -rf ${DOC_GARBAGE}

cleanBuild:
	@echo "(CLEAN build)"
	@rm -rf ${BUILD_GARBAGE}

run: ${TARGET}
	@echo "(RUN  ) $(notdir ${TARGET})"
	@./$<

debug_server: ${TARGET}
	@echo "(DBGSRV) $(notdir ${TARGET}) on :1234"
	${GDBSRV} :1234 $< 

debug_client: ${TARGET}
	@echo "(DBGCLI) $(notdir ${TARGET}) on :1234"
	${GDB} $< -x misc/gdb.script

doc: ${DOC}/html/index.html
	@$(shell if [ -d ./doc/pics ] ; then cp -f ./doc/pics/* ./doc/html ; fi )
	@$(shell if [ -d ./doc/files ] ; then cp -f ./doc/files/* ./doc/html ; fi )
	
${DOC}/html/index.html: ${DOC}/Doxyfile ${DOXS} ${SOURCES} ${HEADERS}
	@echo "(DOC  )"
	@${DOCGEN} $< > ${DOC}/log
	

-include ${DEPS}
