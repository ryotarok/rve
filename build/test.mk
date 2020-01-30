TARGET=trve

all: ${TARGET}

include ${TOPDIR}/build/common.mk

SRCDIR=${TOPDIR}/src
TESTDIR=${TOPDIR}/test

ENTRY=
SRCS=
TEST_SRCS=

include ${TOPDIR}/build/files.mk
OBJS=
OBJS+=${SRCS:.c=.o}
OBJS+=${TEST_SRCS:.cpp=.o}

${TARGET}: ${OBJS}
	${CXX} ${CXXFLAGS} -o $@ ${OBJS} ${TESTFRAMEWORKLIB}

clean:
	rm -f ${TARGET} ${OBJS}

.c.o:
	${CC} ${CFLAGS} -c -o $@ $<

.cpp.o:
	${CXX} ${CXXFLAGS} -c -o $@ $<
