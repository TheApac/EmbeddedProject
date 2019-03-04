//
// Created by acuevas on 11/02/19.
//
#include <check.h>
#include <stdlib.h>




START_TEST(test_simple)
{
	int r;

	r = atoi("42");
	ck_assert_int_eq(r, 42);
} END_TEST

Suite *test(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("test 1");
  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_simple);
  suite_add_tcase(s, tc_core);

  return s;
}

int main(void) {
  int no_failed = 0;
  Suite *s;
  SRunner *runner;

  s = test();
  runner = srunner_create(s);

  srunner_run_all(runner, CK_NORMAL);
  no_failed = srunner_ntests_failed(runner);
  srunner_free(runner);
  return (no_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
