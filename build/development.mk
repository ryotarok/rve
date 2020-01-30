TARGET=drve

all: ${TARGET}

include ${TOPDIR}/build/common.mk

SRCDIR=${TOPDIR}/src

ENTRY=
SRCS=

include ${TOPDIR}/build/files.mk
OBJS=
OBJS+=${SRCS:.c=.o}
OBJS+=${ENTRY:.c=.o}

${TARGET}: ${OBJS}
	${CC} ${CFLAGS} -o $@ ${OBJS}

clean:
	rm -f ${TARGET} ${OBJS}

.c.o:
	${CC} ${CFLAGS} -c -o $@ $<
