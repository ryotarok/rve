
ENTRY=${SRCDIR}/main.c

SRCS+=${SRCDIR}/common/util.c
SRCS+=${SRCDIR}/common/listnode.c
SRCS+=${SRCDIR}/common/bintreenode.c
SRCS+=${SRCDIR}/common/memoryconfig.c

TEST_SRCS+=${TESTDIR}/common/listnode_test.cpp
TEST_SRCS+=${TESTDIR}/common/bintreenode_test.cpp
TEST_SRCS+=${TESTDIR}/common/memoryconfig_test.cpp
