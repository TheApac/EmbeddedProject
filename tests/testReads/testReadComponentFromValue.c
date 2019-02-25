//
// Created by acuevas on 11/02/19.
//
#include <np.h>


static void test_simple(void)
{
	int r;

	r = atoi("42");
	NP_ASSERT_EQUAL(r, 42);
}