CC=clang
CFLAGS=-I${SRCDIR} -O3 -Wall -Wextra -std=c11

CXX=clang++
CXXFLAGS=-I${SRCDIR} -I${TESTDIR} -I${TESTFRAMEWORKDIR}/googletest/googletest/include -O3 -Wall -Wextra -std=c++11
TESTFRAMEWORKDIR=${TESTDIR}/framework/
TESTFRAMEWORKLIB=-L${TESTFRAMEWORKDIR}/googletest/googletest/build -lgtest -lgtest_main
