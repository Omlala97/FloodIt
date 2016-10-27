CXX = g++-4.9									# compiler
CXXFLAGS = -g -Wall -Werror -std=c++11 -MMD				# compiler flags
MAKEFILE_NAME = ${firstword ${MAKEFILE_LIST}}			# makefile name

OBJECTS1 = rpn.o binary.o expr.o num.o unary.o			# object files forming executable
EXEC1 = rpn									# executable name

OBJECTS2 = floodit.o cell.o game.o textdisplay.o		# object files forming executable
EXEC2 = floodit									# executable name

OBJECTS3 = hotpotato.o printer.o player.o potato.o umpire.o
EXEC3 = hotpotato								# executable name

OBJECTS = ${OBJECTS1} ${OBJECTS2} ${OBJECTS3}
EXECS = ${EXEC1} ${EXEC2} ${EXEC3}
DEPENDS = ${OBJECTS:.o=.d}							# substitute ".o" with ".d"

.PHONY : all clean

all : ${EXECS}

${EXEC1} : ${OBJECTS1}								# link step
	${CXX} $^ -o $@

${EXEC2} : ${OBJECTS2}								# link step
	${CXX} $^ -o $@

${EXEC3} : ${OBJECTS3}								# link step
	${CXX} $^ -o $@

${OBJECTS} : ${MAKEFILE_NAME}							# OPTIONAL : changes to this file => recompile

-include ${DEPENDS}								# include *.d files containing program dependences

clean :										# remove files that can be regenerated
	rm -f ${DEPENDS} ${OBJECTS} ${EXECS}
