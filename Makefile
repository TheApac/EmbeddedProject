CC = gcc
CFLAGS = -c -Wall
PROFILE_FLAGS = -fprofile-arcs -ftest-coverage
TST_LIBS = -lcheck -lm -lpthread -lrt 
COV_LIBS = -lgcov -coverage
SRC_DIR= sources
TST_DIR= tests
SRC_FILES = $(addprefix $(SRC_DIR)/, *.c) 
TST_FILES = $(addprefix $(TST_DIR)/, *.c)
GCOV = gcovr 
GCONV_FLAGS = -r . --html --html-details

all: coverage_report.html

hex2dec.o:  $(SRC_FILES) $(addprefix $(SRC_DIR)/, hex2dec.h)
	$(CC) $(CFLAGS) $(PROFILE_FLAGS) $(SRC_FILES)

testReadComponentFromValue: tests/testReads/testReadComponentFromValue.o
	$(CC) tests/testReads/testReadComponentFromValue.o $(TST_LIBS) $(COV_LIBS) -o testReadComponentFromValue

test: testReadComponentFromValue
	./testReadComponentFromValue

coverage_report.html: test
	$(GCOV) $(GCONV_FLAGS) -o coverage_report.html

.PHONY: clean all

clean:
	-rm *.o *.html *.gcda *.gcno testReadComponentFromValue
