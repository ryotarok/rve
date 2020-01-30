.PHONY: clean development test release
all: development test

TOPDIR=${shell pwd}

development:
	TOPDIR=${TOPDIR} make -f ${TOPDIR}/build/development.mk clean
	TOPDIR=${TOPDIR} make -f ${TOPDIR}/build/development.mk

test:
	TOPDIR=${TOPDIR} make -f ${TOPDIR}/build/test.mk clean
	TOPDIR=${TOPDIR} make -f ${TOPDIR}/build/test.mk

# release:
# 	TOPDIR=${TOPDIR} make -f ${TOPDIR}/build/release.mk clean
# 	TOPDIR=${TOPDIR} make -f ${TOPDIR}/build/release.mk

clean:
	TOPDIR=${TOPDIR} make -f ${TOPDIR}/build/development.mk clean
	TOPDIR=${TOPDIR} make -f ${TOPDIR}/build/test.mk clean
	# TOPDIR=${TOPDIR} make -f ${TOPDIR}/build/release.mk clean
