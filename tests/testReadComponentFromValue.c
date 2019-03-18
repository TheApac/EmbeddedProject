//
// Created by acuevas on 11/02/19.
//
#include <check.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <xlsxio_read.h>
#include <mimick.h>

#include "../sources/hex2dec.h"
#include "../sources/readComponentFromValue.h"
#include "../sources/readFailureFromValue.h"
#include "../sources/readTypePlaneFromValue.h"
#include "../sources/getFormattedDate.h"
#include "../sources/readCountryFromPlaneCode.h"
#include "../sources/getFormattedDate.h"
#include "../sources/failure.h"
#include "../sources/strSplit.h"
#include "../sources/getPlaneFromJson.h"
#include "../sources/getFailureFromJson.h"

mmk_mock_define (xlsx_mock, xlsxioreader,
char *);
mmk_mock_define (fopen_mock, xlsxioreader,
char *,char *);

//----------------------------hex2dec----------------------
START_TEST (test_hexa_letter) {
	int r;

	r = hex2dec("0xF");
	ck_assert_int_eq(r, 15);
}

END_TEST

START_TEST(test_hexa_number) {
	int r;

	r = hex2dec("0x5");
	ck_assert_int_eq(r, 5);
}

END_TEST

START_TEST(test_hexa_number_0) {
	int r;

	r = hex2dec("0x0");
	ck_assert_int_eq(r, 0);
}

END_TEST

START_TEST(test_not_hexa_return_0) {
	int r;

	r = hex2dec("bonjour");
	ck_assert_int_eq(r, 0);
}

END_TEST

	Suite
*

test_hex2dec(void) {
	Suite * s;
	TCase *tc_core;

	s = suite_create("test hex2dec");
	tc_core = tcase_create("Core");

	tcase_add_test(tc_core, test_hexa_letter);
	tcase_add_test(tc_core, test_hexa_number);
	tcase_add_test(tc_core, test_not_hexa_return_0);
	tcase_add_test(tc_core, test_hexa_number_0);
	suite_add_tcase(s, tc_core);
	return s;
}

//----------------------------readComponentFromValue----------------------
START_TEST (test_RCFV_exist) {
	char *r;

	r = readComponentFromValue(0x2009);
	ck_assert_str_eq(r, "Elevator");
}

END_TEST

START_TEST(test_RCFV_not_exist) {
	char *r;

	r = readComponentFromValue(0x2022);
	ck_assert_str_eq(r, "");
}

END_TEST

START_TEST(test_RCFV_file_not_found) {
	xlsx_mock mock = mmk_mock("xlsxioread_open@self", xlsx_mock);
	void *result = NULL;
	mmk_when(xlsxioread_open(mmk_any(
	char *)),
	.then_return = &result,
	.then_errno = ENOMEM);
	assert(xlsxioread_open("Embedded_World-Request_for_proposal-Annex1.xlsx") == result && errno == ENOMEM);

	char *r;
	r = readComponentFromValue(0x2022);
	ck_assert_str_eq(r, "noFile");

	mmk_reset(mock);
}

END_TEST

	Suite
*

test_readComponentFromValue(void) {
	Suite * s;
	TCase *tc_core;

	s = suite_create("test readComponentFromValue");
	tc_core = tcase_create("Core");

	tcase_add_test(tc_core, test_RCFV_exist);
	tcase_add_test(tc_core, test_RCFV_not_exist);
	tcase_add_test(tc_core, test_RCFV_file_not_found);
	suite_add_tcase(s, tc_core);
	return s;
}

//----------------------------readFailureFromValue----------------------
START_TEST (test_RFFV_exist) {
	char *r;

	r = readFailureFromValue(0x1007);
	ck_assert_str_eq(r, "Too_Cold temperature error");
}

END_TEST

START_TEST(test_RFFV_not_exist) {
	char *r;

	r = readFailureFromValue(0x101D);
	ck_assert_str_eq(r, "");
}

END_TEST

START_TEST(test_RFFV_file_not_found) {
	xlsx_mock mock = mmk_mock("xlsxioread_open@self", xlsx_mock);
	void *result = NULL;
	mmk_when(xlsxioread_open(mmk_any(
	char *)),
	.then_return = &result,
	.then_errno = ENOMEM);
	assert(xlsxioread_open("Embedded_World-Request_for_proposal-Annex1.xlsx") == result && errno == ENOMEM);

	char *r;
	r = readFailureFromValue(0x1007);
	ck_assert_str_eq(r, "noFile");

	mmk_reset(mock);
}

END_TEST

	Suite
*

test_readFailureFromValue(void) {
	Suite * s;
	TCase *tc_core;

	s = suite_create("test readFailureFromValue");
	tc_core = tcase_create("Core");

	tcase_add_test(tc_core, test_RFFV_exist);
	tcase_add_test(tc_core, test_RFFV_not_exist);
	tcase_add_test(tc_core, test_RFFV_file_not_found);
	suite_add_tcase(s, tc_core);
	return s;
}

//----------------------------readTypePlaneFromValue----------------------
START_TEST (test_RTPFV_exist) {
	char *r;

	r = readTypePlaneFromValue(0x015E);
	ck_assert_str_eq(r, "Airbus A350");
}

END_TEST

START_TEST(test_RTPFV_not_exist) {
	char *r;

	r = readTypePlaneFromValue(0x016D);
	ck_assert_str_eq(r, "");
}

END_TEST

START_TEST(test_RTPFV_file_not_found) {
	xlsx_mock mock = mmk_mock("xlsxioread_open@self", xlsx_mock);
	void *result = NULL;
	mmk_when(xlsxioread_open(mmk_any(
	char *)),
	.then_return = &result,
	.then_errno = ENOMEM);
	assert(xlsxioread_open("Embedded_World-Request_for_proposal-Annex1.xlsx") == result && errno == ENOMEM);

	char *r;
	r = readTypePlaneFromValue(0x016D);
	ck_assert_str_eq(r, "noFile");

	mmk_reset(mock);
}

END_TEST

	Suite
*

test_readTypePlaneFromValue(void) {
	Suite * s;
	TCase *tc_core;

	s = suite_create("test readTypePlaneFromValue");
	tc_core = tcase_create("Core");

	tcase_add_test(tc_core, test_RTPFV_exist);
	tcase_add_test(tc_core, test_RTPFV_not_exist);
	tcase_add_test(tc_core, test_RTPFV_file_not_found);
	suite_add_tcase(s, tc_core);
	return s;
}

//----------------------------readCountryFromPlaneCode----------------------
START_TEST (test_RCFPC_exist_start) {
	char *r;

	r = readCountryFromPlaneCode((unsigned char *) "T9-AAA");
	ck_assert_str_eq(r, "Bosnia and Herzegovina");
}

END_TEST

START_TEST(test_RCFPC_exist_middle) {
	char *r;

	r = readCountryFromPlaneCode((unsigned char *) "T9-SJW");
	ck_assert_str_eq(r, "Bosnia and Herzegovina");
}

END_TEST

START_TEST(test_RCFPC_exist_end) {
	char *r;

	r = readCountryFromPlaneCode((unsigned char *) "T9-ZZZ");
	ck_assert_str_eq(r, "Bosnia and Herzegovina");
}

END_TEST

START_TEST(test_RCFPC_not_exist) {
	char *r;

	r = readCountryFromPlaneCode((unsigned char *) "ma3'é9-AET");
	ck_assert_str_eq(r, "");
}

END_TEST

START_TEST(test_RCFPC_one_elem) {
	char *r;

	r = readCountryFromPlaneCode((unsigned char *) "SX-H");
	ck_assert_str_eq(r, "Greece");
}

END_TEST

START_TEST(test_RCFPC_file_not_found) {
	xlsx_mock mock = mmk_mock((char *) "xlsxioread_open@self", xlsx_mock);
	void *result = NULL;
	mmk_when(xlsxioread_open(mmk_any(
	char *)),
	.then_return = &result,
	.then_errno = ENOMEM);
	assert(xlsxioread_open("Embedded_World-Request_for_proposal-Annex1.xlsx") == result && errno == ENOMEM);

	char *r;
	r = readCountryFromPlaneCode((unsigned char *) "T9-ZZZ");
	ck_assert_str_eq(r, "noFile");

	mmk_reset(mock);
}

END_TEST

	Suite
*

test_readCountryFromPlaneCode(void) {
	Suite * s;
	TCase *tc_core;

	s = suite_create("test readCountryFromPlaneCode");
	tc_core = tcase_create("Core");

	tcase_add_test(tc_core, test_RCFPC_exist_start);
	tcase_add_test(tc_core, test_RCFPC_exist_middle);
	tcase_add_test(tc_core, test_RCFPC_exist_end);
	tcase_add_test(tc_core, test_RCFPC_not_exist);
	tcase_add_test(tc_core, test_RCFPC_file_not_found);
	tcase_add_test(tc_core, test_RCFPC_one_elem);
	suite_add_tcase(s, tc_core);
	return s;
}

//----------------------------getFormattedDate----------------------
START_TEST (test_GFD_title) {
	char *r;
	unsigned int date = 1551877430;

	r = getFormattedDate(date, 0);
	ck_assert_str_eq(r, "2019_03_06_14_03_50");
}

END_TEST

START_TEST(test_GFD_file) {
	char *r;
	unsigned int date = 1551877430;

	r = getFormattedDate(date, 1);
	ck_assert_str_eq(r, "2019/03/06-14:03:50");
}

END_TEST

	Suite
*

test_getFormattedDate(void) {
	Suite * s;
	TCase *tc_core;

	s = suite_create("test getFormattedDate");
	tc_core = tcase_create("Core");

	tcase_add_test(tc_core, test_GFD_title);
	tcase_add_test(tc_core, test_GFD_file);
	suite_add_tcase(s, tc_core);
	return s;
}

//----------------------------failure----------------------
START_TEST (test_failure_work) {
	char *filename[50];

	struct failure fail;
	fail = (struct failure) {.datetime_failure_x = 1551877430, .id_failure_x = 0x1009, .id_component_failure_x = 0x2005, .comment_failure_x_size = 255, .level_criticity_failure_x = 1, .comment_failure_x = "Failure pas cool"};
	struct plane planeA = (struct plane) {"D2-ZZZ", 1, 380};

	printFailureToFile(fail, planeA);
	printFailureToFile(fail, planeA);
	printFailureToFile(fail, planeA);
	printFailureToFile(fail, planeA);


	strcpy(filename, "Extraction_report_");
	strcat(filename, (char *) planeA.id_plane);
	strcat(filename, "_");
	strcat(filename, getFormattedDate(fail.datetime_failure_x, 0));
	strcat(filename, ".txt");


	FILE *fp = fopen(filename, "r");
	ck_assert_ptr_nonnull(fp);
	int nbLine = 0;
	int ch = 0;
	while (!feof(fp)) {
		ch = fgetc(fp);
		if (ch == '\n') {
			nbLine++;
		}
	}

	fclose(fp);
	//remove(filename);
	int nbLineWait = 4 * 6 + 5;
	ck_assert_int_eq(nbLine, nbLineWait);
}

END_TEST

START_TEST(test_failure_already_exist) {
	char *filename[50];

	struct failure fail;
	fail = (struct failure) {.datetime_failure_x = 1551877430, .id_failure_x = 0x1009, .id_component_failure_x = 0x2005, .comment_failure_x_size = 255, .level_criticity_failure_x = 1, .comment_failure_x = "Failure pas cool"};
	struct plane planeA = (struct plane) {"D2-ZZZ", 1, 380};

	strcpy(filename, "Extraction_report_");
	strcat(filename, (char *) planeA.id_plane);
	strcat(filename, "_");
	strcat(filename, getFormattedDate(fail.datetime_failure_x, 0));
	strcat(filename, ".txt");


	FILE *fp = fopen(filename, "r");
	ck_assert_ptr_nonnull(fp);
	int nbLinePrevious = 0;
	int ch = 0;
	while (!feof(fp)) {
		ch = fgetc(fp);
		if (ch == '\n') {
			nbLinePrevious++;
		}
	}

	fclose(fp);

	printFailureToFile(fail, planeA);
	printFailureToFile(fail, planeA);
	printFailureToFile(fail, planeA);
	printFailureToFile(fail, planeA);

	fp = fopen(filename, "r");
	ck_assert_ptr_nonnull(fp);
	int nbLine = 0;
	ch = 0;
	while (!feof(fp)) {
		ch = fgetc(fp);
		if (ch == '\n') {
			nbLine++;
		}
	}

	remove(filename);
	int nbLineWait = 4 * 6 + nbLinePrevious;
	ck_assert_int_eq(nbLine, nbLineWait);
}

END_TEST

START_TEST(test_failure_file_not_exist) {
	char *filename[50];

	struct failure fail;
	fail = (struct failure) {.datetime_failure_x = 1551877430, .id_failure_x = 0x1009, .id_component_failure_x = 0x2005, .comment_failure_x_size = 255, .level_criticity_failure_x = 1, .comment_failure_x = "Failure pas cool"};
	struct plane planeA = (struct plane) {"D2-ZZZ", 1, 380};

	strcpy(filename, "Extraction_report_");
	strcat(filename, (char *) planeA.id_plane);
	strcat(filename, "_");
	strcat(filename, getFormattedDate(fail.datetime_failure_x, 0));
	strcat(filename, ".txt");

	fopen_mock mock = mmk_mock((char *) "fopen@self", fopen_mock);
	void *result = NULL;
	mmk_when(fopen(mmk_any(
	char *),mmk_any(
	char *)),
	.then_return = &result,
	.then_errno = ENOMEM);
	assert(fopen(filename, "w") == result && errno == ENOMEM);
	assert(fopen(filename, "r") == result && errno == ENOMEM);
	assert(fopen(filename, "a") == result && errno == ENOMEM);

	printFailureToFile(fail, planeA);

	mmk_reset(mock);


	FILE *fp = fopen(filename, "r");
	ck_assert_ptr_null(fp);

	//fclose(fp);
	//remove(filename);
}

END_TEST

	Suite
*

test_failure(void) {
	Suite * s;
	TCase *tc_core;

	s = suite_create("test failure");
	tc_core = tcase_create("Core");

	tcase_add_test(tc_core, test_failure_work);
	tcase_add_test(tc_core, test_failure_already_exist);
	tcase_add_test(tc_core, test_failure_file_not_exist);
	suite_add_tcase(s, tc_core);
	return s;
}

//----------------------------str_split----------------------
START_TEST (test_strSplit_valid_split) {
	char **r;
	char text[] = "bonjour";

	r = str_split(text, 'j');
	ck_assert_str_eq(r[0], "bon");
	ck_assert_str_eq(r[1], "our");
}

END_TEST

START_TEST(test_strSplit_not_plit) {
	char **r;
	char text[] = "bonjour";
	r = str_split(text, 'v');
	ck_assert_str_eq(r[0], "bonjour");
	ck_assert_ptr_null(r[1]);
}

END_TEST

	Suite
*

test_str_split(void) {
	Suite * s;
	TCase *tc_core;

	s = suite_create("test str_split");
	tc_core = tcase_create("Core");

	tcase_add_test(tc_core, test_strSplit_valid_split);
	tcase_add_test(tc_core, test_strSplit_not_plit);
	suite_add_tcase(s, tc_core);
	return s;
}


//----------------------------getPlaneFromJson----------------------


START_TEST (test_json_plane_valid) {
	struct plane r;
	char text[] = "{\n"
		"Id_plane:VH-AAA, Type_plane:777, Nb_failures:2, failures:[\n"
		"{\n"
		"Id_failure:4105, Date:1793007013, Id_component:8201, Level_criticity:0, Comment_failure_size:12, Comment_failure:Test Failure }, {\n"
		"Id_failure:4103, Date:25736911, Id_component:8199, Level_criticity:5, Comment_failure_size:12, Comment_failure:Test Failure } ] }";
	r = getPlaneFromJson(text);
	ck_assert_str_eq(r.id_plane, "VH-AAA");
	ck_assert_int_eq(r.nb_failures, 2);
	ck_assert_int_eq(r.type_plane, 777);
}

END_TEST

START_TEST(test_json_plane_invalid) {
	struct plane r;
	char text[] = "a";
	r = getPlaneFromJson(text);
	ck_assert_str_eq(r.id_plane, "error");
	ck_assert_int_eq(r.nb_failures, 0);
	ck_assert_int_eq(r.type_plane, 0);
}

END_TEST


test_getPlaneFromJson(void) {
	Suite * s;
	TCase *tc_core;

	s = suite_create("test getPlaneFromJson");
	tc_core = tcase_create("Core");

	tcase_add_test(tc_core, test_json_plane_valid);
	tcase_add_test(tc_core, test_json_plane_invalid);
	suite_add_tcase(s, tc_core);
	return s;
}

//----------------------------getFailureFromJson----------------------


START_TEST (test_json_failure_valid) {
	struct failure *r;
	char text[] = "{\n"
		"Id_plane:VH-AAA, Type_plane:777, Nb_failures:2, failures:[\n"
		"{\n"
		"Id_failure:4105, Date:1793007013, Id_component:8201, Level_criticity:0, Comment_failure_size:13, Comment_failure:Test Failure}, {\n"
		"Id_failure:4103, Date:25736911, Id_component:8199, Level_criticity:5, Comment_failure_size:13, Comment_failure:Test Failure} ] }";
	r = getFailureFromJson(text, 2);
	ck_assert_ptr_nonnull(r);

	ck_assert_int_eq(r[0].id_failure_x, 4105);
	ck_assert_str_eq(r[0].comment_failure_x, "Test Failure");
	ck_assert_str_eq(r[0].comment_failure_x_size, "13");
	ck_assert_int_eq(r[0].datetime_failure_x, 1793007013);
	ck_assert_int_eq(r[0].id_component_failure_x, 8201);
	ck_assert_int_eq(r[0].level_criticity_failure_x, 0);

	ck_assert_int_eq(r[1].id_failure_x, 4103);
	ck_assert_str_eq(r[1].comment_failure_x, "Test Failure");
	ck_assert_str_eq(r[1].comment_failure_x_size, "13");
	ck_assert_int_eq(r[1].datetime_failure_x, 25736911);
	ck_assert_int_eq(r[1].id_component_failure_x, 8199);
	ck_assert_int_eq(r[1].level_criticity_failure_x, 5);
}

END_TEST

START_TEST(test_json_failure_invalid) {
	struct failure *r;
	char text[] = "A{{{,,{12:;[)[}";
	r = getFailureFromJson(text, 1);
	ck_assert_ptr_null(r);
}

END_TEST


test_getFailureFromJson(void) {
	Suite * s;
	TCase *tc_core;

	s = suite_create("test getFailureFromJson");
	tc_core = tcase_create("Core");

	tcase_add_test(tc_core, test_json_failure_valid);
	tcase_add_test(tc_core, test_json_failure_invalid);
	suite_add_tcase(s, tc_core);
	return s;
}

//----------------------------------------------------------------

int main(void) {
	int no_failed = 0;
	Suite * s;
	SRunner *runner;

	s = test_hex2dec();
	runner = srunner_create(s);
	srunner_run_all(runner, CK_NORMAL);
	no_failed = srunner_ntests_failed(runner);
	srunner_free(runner);

	s = test_readComponentFromValue();
	runner = srunner_create(s);
	srunner_run_all(runner, CK_NORMAL);
	no_failed = srunner_ntests_failed(runner);
	srunner_free(runner);

	s = test_readFailureFromValue();
	runner = srunner_create(s);
	srunner_run_all(runner, CK_NORMAL);
	no_failed = srunner_ntests_failed(runner);
	srunner_free(runner);

	s = test_readTypePlaneFromValue();
	runner = srunner_create(s);
	srunner_run_all(runner, CK_NORMAL);
	no_failed = srunner_ntests_failed(runner);
	srunner_free(runner);

	s = test_readCountryFromPlaneCode();
	runner = srunner_create(s);
	srunner_run_all(runner, CK_NORMAL);
	no_failed = srunner_ntests_failed(runner);
	srunner_free(runner);

	s = test_getFormattedDate();
	runner = srunner_create(s);
	srunner_run_all(runner, CK_NORMAL);
	no_failed = srunner_ntests_failed(runner);
	srunner_free(runner);

	s = test_failure();
	runner = srunner_create(s);
	srunner_run_all(runner, CK_NORMAL);
	no_failed = srunner_ntests_failed(runner);
	srunner_free(runner);

	s = test_str_split();
	runner = srunner_create(s);
	srunner_run_all(runner, CK_NORMAL);
	no_failed = srunner_ntests_failed(runner);
	srunner_free(runner);

	s = test_getPlaneFromJson();
	runner = srunner_create(s);
	srunner_run_all(runner, CK_NORMAL);
	no_failed = srunner_ntests_failed(runner);
	srunner_free(runner);

	s = test_getFailureFromJson();
	runner = srunner_create(s);
	srunner_run_all(runner, CK_NORMAL);
	no_failed = srunner_ntests_failed(runner);
	srunner_free(runner);


	return (no_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
