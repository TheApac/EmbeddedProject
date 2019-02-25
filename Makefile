CC	= gcc

-std=c11

all: libmycode.a

LIBRARYPATH = /usr/lib/

SOURCES= sources/src/failure.c		\
		sources/src/getFormattedDate.c		\
		sources/src/plane.c		\
		sources/src/printInLogFile.c	\
		sources/src/raiseError.c \
		sources/src/readComponentFromValue.c  \
		sources/src/readCountryFromPlaneCode.c  \
		sources/src/readFailureFromValue.c \
		sources/src/hex2dec.c \
		sources/src/readTypePlaneFromValue.c

SOURCES_OBJS= $(SOURCES:.c=.o)

libmycode.a: $(SOURCES_OBJS)
	ar ruv $@ $(SOURCES_OBJS)
	ranlib $@

NOVAPROVA_CFLAGS= $(shell pkg-config --cflags novaprova)

NOVAPROVA_LIBS= $(shell pkg-config --libs novaprova)

CFLAGS= -g $(NOVAPROVA_CFLAGS) -Wall -W -Wextra -I./sources/include/ -fprofile-arcs -ftest-coverage

LDFLAGS	+= -fprofile-arcs -ftest-coverage

test: testrunner
	./coverage_test
	gcov $(TEST_SOURCE)
	gcovr -r . --html -o coverage.html --html-details

TEST_SOURCE= tests/testReads/testReadComponentFromValue.c

TEST_OBJS= $(TEST_SOURCE:.c=.o)

COV_SOURCES	= $(SOURCES:.c=.gcno) $(SOURCES:.c=.gcda)
COV_TEST	= $(TEST_SOURCE:.c=.gcno) $(TEST_SOURCE:.c=.gcda)

testrunner: $(TEST_OBJS) libmycode.a
	$(LINK.c) -o $@ $(TEST_OBJS) libmycode.a $(NOVAPROVA_LIBS)
	$(CC) $(LDFLAGS) $(TEST_OBJS) -L$(LIBRARYPATH) -o coverage_test -lgcov libmycode.a $(NOVAPROVA_LIBS)

clean:
	$(RM) testrunner coverage_test libmycode.a $(TEST_OBJS) $(SOURCES_OBJS) $(COV_SOURCES) $(COV_TEST) *.html *.gcov

re:	clean all test

.PHONY: all

