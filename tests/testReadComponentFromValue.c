//
// Created by acuevas on 11/02/19.
//
#include <check.h>
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

mmk_mock_define (xlsx_mock, xlsxioreader,char *);


//----------------------------hex2dec----------------------
START_TEST (test_hexa_letter) {
	int r;

	r = hex2dec("0xF");
	ck_assert_int_eq(r, 15);
}END_TEST

START_TEST(test_hexa_number) {
	int r;

	r = hex2dec("0x5");
	ck_assert_int_eq(r, 5);
}END_TEST

START_TEST(test_hexa_number_0) {
	int r;

	r = hex2dec("0x0");
	ck_assert_int_eq(r, 0);
}END_TEST

START_TEST(test_not_hexa_return_0) {
	int r;

	r = hex2dec("bonjour");
	ck_assert_int_eq(r, 0);
}END_TEST

Suite *test_hex2dec(void) {
	Suite *s;
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
}END_TEST

START_TEST(test_RCFV_not_exist) {
	char *r;

	r = readComponentFromValue(0x2022);
	ck_assert_str_eq(r, "");
}END_TEST

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
}END_TEST

Suite *test_readComponentFromValue(void) {
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
}END_TEST

START_TEST(test_RFFV_not_exist) {
	char *r;

	r = readFailureFromValue(0x101D);
	ck_assert_str_eq(r, "");
}END_TEST

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
}END_TEST

Suite *test_readFailureFromValue(void) {
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
}END_TEST

START_TEST(test_RTPFV_not_exist) {
	char *r;

	r = readTypePlaneFromValue(0x016D);
	ck_assert_str_eq(r, "");
}END_TEST

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
}END_TEST

Suite *test_readTypePlaneFromValue(void) {
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
}END_TEST

START_TEST(test_RCFPC_exist_middle) {
	char *r;

	r = readCountryFromPlaneCode((unsigned char *) "T9-SJW");
	ck_assert_str_eq(r, "Bosnia and Herzegovina");
}END_TEST

START_TEST(test_RCFPC_exist_end) {
	char *r;

	r = readCountryFromPlaneCode((unsigned char *) "T9-ZZZ");
	ck_assert_str_eq(r, "Bosnia and Herzegovina");
}END_TEST

START_TEST(test_RCFPC_not_exist) {
	char *r;

	r = readCountryFromPlaneCode((unsigned char *) "ma3'é9-AET");
	ck_assert_str_eq(r, "");
}END_TEST

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
}END_TEST

Suite *test_readCountryFromPlaneCode(void) {
	Suite * s;
	TCase *tc_core;

	s = suite_create("test readCountryFromPlaneCode");
	tc_core = tcase_create("Core");

	tcase_add_test(tc_core, test_RCFPC_exist_start);
	tcase_add_test(tc_core, test_RCFPC_exist_middle);
	tcase_add_test(tc_core, test_RCFPC_exist_end);
	tcase_add_test(tc_core, test_RCFPC_not_exist);
	tcase_add_test(tc_core, test_RCFPC_file_not_found);
	suite_add_tcase(s, tc_core);
	return s;
}

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

	return (no_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
