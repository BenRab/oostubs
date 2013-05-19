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

INTERNAL_OBJECTS := $(addprefix ${BUILD}/, boot.o cppInit.o pow.o compat.o)
SOURCES          := $(wildcard ${SRC}/*/*.cc ${SRC}/*.cc ${SRC}/asm/*.S )
HEADERS          := $(filter %.h, $(wildcard ${INCLUDE}/*/*.h))
DOXS             := $(wildcard ${DOC}/*.dox)
SYSTEM_OBJECTS   :=$(addprefix ${BUILD}/,$(filter-out ${OBJECT_IGNORE}, $(addsuffix .o,$(basename $(notdir ${SOURCES})))))
DEPS             := $(addsuffix .d,${SYSTEM_OBJECTS})
OBJECTS          := ${INTERNAL_OBJECTS} ${SYSTEM_OBJECTS}
TARGET           := ${BIN}/${TARGET}
EMTARGET         := ${BIN}/${EMUTARGET}
INCPATHS         := $(addprefix -I,${INCLUDE} ${INCPATHS})
LIBPATHS         := $(addprefix -L,${LIBPATHS})
LIBS             := $(addprefix -l,${LIBS})
ASMFLAGS         := $(foreach VAR, ${ASMFLAGS}, -Wa,${VAR})
BUILD_GARBAGE    := $(wildcard *~ *.sw?) ${BIN} ${BUILD} $(wildcard *.dump)
DOC_GARBAGE      := ${DOC}/html ${DOC}/log
GARBAGE          := $(BUILD_GARBAGE) $(DOC_GARBAGE)

.PHONY: all clean run debug doc dump cleanDoc cleanBuild

vpath %.cc ${SRC} ${SRC}/machine ${SRC}/user ${SRC}/object ${SRC}/syscall ${SRC}/thread ${SRC}/meetings ${SRC}/guard ${SRC}/device
vpath %.c  ${INTERNAL} ${SRC}/machine 
vpath %.S  ${INTERNAL} ${SRC}/asm

all: ${TARGET}

${TARGET}: ${OBJECTS} | ${BIN}
	@echo "(LD   ) $@ <- [$(notdir ${SYSTEM_OBJECTS})]"
	${LD} ${LDFLAGS} ${OBJECTS} -o $@

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

run: ${EMUTARGET}
	@echo "(EMU  )"
	${EMU} ${EMUFLAGS} $< 

debug: ${TARGET}
	@echo "(DEBUG)"
	${EMU} ${EMUFLAGS} $< ${EMUDEBUG} -S -s -daemonize && ${RAWGDB} ${TARGET} ${GDBFLAGS}

doc: ${DOC}/html/index.html
	@$(shell if [ -d ./doc/pics ] ; then cp -f ./doc/pics/* ./doc/html ; fi )
	@$(shell if [ -d ./doc/files ] ; then cp -f ./doc/files/* ./doc/html ; fi )
	
${DOC}/html/index.html: ${DOC}/Doxyfile ${DOXS} ${SOURCES} ${HEADERS}
	@echo "(DOC  )"
	@${DOCGEN} $< > ${DOC}/log
	

-include ${DEPS}
