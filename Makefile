CC = gcc
CFLAGS = -c -Wall -lxlsxio_read
PROFILE_FLAGS = -fprofile-arcs -ftest-coverage
TST_LIBS = -lcheck -lm -lpthread -lrt -lxlsxio_read -lmimick
COV_LIBS = -lgcov -coverage
SRC_DIR= sources
TST_DIR= tests
SRC_FILES = $(addprefix $(SRC_DIR)/, *.c)
H_FILES = $(addprefix $(SRC_DIR)/, *.h)
TST_FILES = $(addprefix $(TST_DIR)/, *.c)
O_FILES = $(addsuffix .o, $(FUNC_FILES))
FILE_TEST = testReadComponentFromValue.o
GCOV = gcovr
GCONV_FLAGS = -r . --html --html-details
FUNC_FILES = hex2dec readComponentFromValue readFailureFromValue readTypePlaneFromValue getFormattedDate readCountryFromPlaneCode failure strSplit

all: clean coverage_report.html cleanAll

$(O_FILES):  $(SRC_FILES) $(H_FILES)
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

cleanAll:
	-rm *.o *.gcda *.gcno testReadComponentFromValue libmycode.a tests/*.o tests/*.gcno 2>/dev/null || true

clean:
	-rm *.o *.html *.gcda *.gcno testReadComponentFromValue libmycode.a tests/*.o tests/*.gcno 2>/dev/null || true