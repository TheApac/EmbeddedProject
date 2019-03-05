CC = gcc
CFLAGS = -c -Wall
PROFILE_FLAGS = -fprofile-arcs -ftest-coverage
TST_LIBS = -lcheck -lm -lpthread -lrt 
COV_LIBS = -lgcov -coverage
SRC_DIR= sources
TST_DIR= tests
SRC_FILES = $(addprefix $(SRC_DIR)/, *.c) 
TST_FILES = $(addprefix $(TST_DIR)/, *.c)
O_FILES = hex2dec.o
H_FILES = hex2dec.h
FILE_TEST = testReadComponentFromValue.o
GCOV = gcovr
GCONV_FLAGS = -r . --html --html-details

all: coverage_report.html clean

$(O_FILES):  $(SRC_FILES) $(addprefix $(SRC_DIR)/, $(H_FILES))
	$(CC) $(CFLAGS) $(PROFILE_FLAGS) $(SRC_FILES)

$(FILE_TEST): $(TST_FILES)
	$(CC) $(CFLAGS) $(PROFILE_FLAGS)  $(TST_FILES)

testReadComponentFromValue: $(O_FILES) $(FILE_TEST)
	$(CC) $(O_FILES) $(FILE_TEST) $(TST_LIBS) $(COV_LIBS) -o testReadComponentFromValue

test: testReadComponentFromValue
	./testReadComponentFromValue

coverage_report.html: test
	$(GCOV) $(GCONV_FLAGS) -o coverage_report.html

.PHONY: clean all

clean:
	-rm *.o *.html *.gcda *.gcno testReadComponentFromValue libmycode.a tests/*/*.o tests/*/*.gcno 2>/dev/null || true
