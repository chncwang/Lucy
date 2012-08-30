#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Environment
MKDIR=mkdir
CP=cp
GREP=grep
NM=nm
CCADMIN=CCadmin
RANLIB=ranlib
CC=clang
CCC=c++
CXX=c++
FC=gfortran
AS=as

# Macros
CND_PLATFORM=GNU-MacOSX
CND_DLIB_EXT=dylib
CND_CONF=Debug
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/src/lua_table.o \
	${OBJECTDIR}/src/state_util.o \
	${OBJECTDIR}/src/oo_support.o \
	${OBJECTDIR}/src/lua_data_array.o \
	${OBJECTDIR}/src/lua_func_TEST.o \
	${OBJECTDIR}/src/lua_value.o \
	${OBJECTDIR}/src/lua_data.o \
	${OBJECTDIR}/src/lucy.o \
	${OBJECTDIR}/src/lua_file.o \
	${OBJECTDIR}/src/lua_func.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=
CXXFLAGS=

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=/Library/lua-5.2.1/src/liblua.a

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/lucy

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/lucy: /Library/lua-5.2.1/src/liblua.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/lucy: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.c} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/lucy ${OBJECTFILES} ${LDLIBSOPTIONS} 

${OBJECTDIR}/src/lua_table.o: src/lua_table.c 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.c) -g -I/Library/lua-5.2.1/src -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/lua_table.o src/lua_table.c

${OBJECTDIR}/src/state_util.o: src/state_util.c 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.c) -g -I/Library/lua-5.2.1/src -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/state_util.o src/state_util.c

${OBJECTDIR}/src/oo_support.o: src/oo_support.c 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.c) -g -I/Library/lua-5.2.1/src -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/oo_support.o src/oo_support.c

${OBJECTDIR}/src/lua_data_array.o: src/lua_data_array.c 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.c) -g -I/Library/lua-5.2.1/src -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/lua_data_array.o src/lua_data_array.c

${OBJECTDIR}/src/lua_func_TEST.o: src/lua_func_TEST.c 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.c) -g -I/Library/lua-5.2.1/src -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/lua_func_TEST.o src/lua_func_TEST.c

${OBJECTDIR}/src/lua_value.o: src/lua_value.c 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.c) -g -I/Library/lua-5.2.1/src -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/lua_value.o src/lua_value.c

${OBJECTDIR}/src/lua_data.o: src/lua_data.c 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.c) -g -I/Library/lua-5.2.1/src -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/lua_data.o src/lua_data.c

${OBJECTDIR}/src/lucy.o: src/lucy.c 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.c) -g -I/Library/lua-5.2.1/src -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/lucy.o src/lucy.c

${OBJECTDIR}/src/lua_file.o: src/lua_file.c 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.c) -g -I/Library/lua-5.2.1/src -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/lua_file.o src/lua_file.c

${OBJECTDIR}/src/lua_func.o: src/lua_func.c 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.c) -g -I/Library/lua-5.2.1/src -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/lua_func.o src/lua_func.c

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/lucy

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
