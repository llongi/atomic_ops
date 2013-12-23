/**
 * This file is part of the atomic_ops project.
 *
 * For the full copyright and license information, please view the COPYING
 * file that was distributed with this source code.
 *
 * @copyright  (c) the atomic_ops project
 * @author     Luca Longinotti <chtekk@longitekk.com>
 * @license    BSD 2-clause
 * @version    $Id: atomic_ops_test.c 1109 2012-08-30 01:27:43Z llongi $
 */

#include "atomic_ops.h"
#include <check.h>

#define TCASE_ADD(testname) \
	TCase *tc_##testname = tcase_create(#testname); \
	tcase_add_test(tc_##testname, test_##testname); \
	suite_add_tcase(s, tc_##testname)

#define TCASE_ADD_EXIT(testname, exit) \
	TCase *tc_##testname = tcase_create(#testname); \
	tcase_add_exit_test(tc_##testname, test_##testname, exit); \
	suite_add_tcase(s, tc_##testname)

#define TCASE_ADD_FIXTURE(testname, setup, teardown) \
	TCase *tc_##testname = tcase_create(#testname); \
	tcase_add_checked_fixture(tc_##testname, setup, teardown); \
	tcase_add_test(tc_##testname, test_##testname); \
	suite_add_tcase(s, tc_##testname)

#define TCASE_ADD_FIXTURE_EXIT(testname, setup, teardown, exit) \
	TCase *tc_##testname = tcase_create(#testname); \
	tcase_add_checked_fixture(tc_##testname, setup, teardown); \
	tcase_add_exit_test(tc_##testname, test_##testname, exit); \
	suite_add_tcase(s, tc_##testname)

Suite *test_atomic_ops_load(void);
Suite *test_atomic_ops_store(void);
Suite *test_atomic_ops_not(void);
Suite *test_atomic_ops_and(void);
Suite *test_atomic_ops_or(void);
Suite *test_atomic_ops_xor(void);
Suite *test_atomic_ops_add(void);
Suite *test_atomic_ops_inc(void);
Suite *test_atomic_ops_dec(void);
Suite *test_atomic_ops_fetch_and_add(void);
Suite *test_atomic_ops_fetch_and_inc(void);
Suite *test_atomic_ops_fetch_and_dec(void);
Suite *test_atomic_ops_casr(void);
Suite *test_atomic_ops_cas(void);
Suite *test_atomic_ops_swap(void);

int main(void) {
	SRunner *sr = srunner_create(test_atomic_ops_load());
	srunner_add_suite(sr, test_atomic_ops_store());
	srunner_add_suite(sr, test_atomic_ops_not());
	srunner_add_suite(sr, test_atomic_ops_and());
	srunner_add_suite(sr, test_atomic_ops_or());
	srunner_add_suite(sr, test_atomic_ops_xor());
	srunner_add_suite(sr, test_atomic_ops_add());
	srunner_add_suite(sr, test_atomic_ops_inc());
	srunner_add_suite(sr, test_atomic_ops_dec());
	srunner_add_suite(sr, test_atomic_ops_fetch_and_add());
	srunner_add_suite(sr, test_atomic_ops_fetch_and_inc());
	srunner_add_suite(sr, test_atomic_ops_fetch_and_dec());
	srunner_add_suite(sr, test_atomic_ops_casr());
	srunner_add_suite(sr, test_atomic_ops_cas());
	srunner_add_suite(sr, test_atomic_ops_swap());

	srunner_run_all(sr, CK_VERBOSE);
	int failed = srunner_ntests_failed(sr);
	srunner_free(sr);

	return ((failed == 0) ? (EXIT_SUCCESS) : (EXIT_FAILURE));
}

/******************************************************************************/

START_TEST(test_atomic_ops_load_int) {
	atomic_ops_int src = ATOMIC_OPS_INT_INIT(-10);
	intptr_t dest = 0;

	dest = atomic_ops_int_load(&src, ATOMIC_OPS_FENCE_NONE);

	ck_assert(dest == -10);

	dest = 0;

	dest = atomic_ops_int_load(&src, ATOMIC_OPS_FENCE_FULL);

	ck_assert(dest == -10);
} END_TEST

START_TEST(test_atomic_ops_load_uint) {
	atomic_ops_uint src = ATOMIC_OPS_UINT_INIT(10);
	uintptr_t dest = 0;

	dest = atomic_ops_uint_load(&src, ATOMIC_OPS_FENCE_NONE);

	ck_assert(dest == 10);

	dest = 0;

	dest = atomic_ops_uint_load(&src, ATOMIC_OPS_FENCE_FULL);

	ck_assert(dest == 10);
} END_TEST

START_TEST(test_atomic_ops_load_ptr) {
	atomic_ops_ptr src = ATOMIC_OPS_PTR_INIT(0x10);
	void *dest = NULL;

	dest = atomic_ops_ptr_load(&src, ATOMIC_OPS_FENCE_NONE);

	ck_assert(dest == (void *)0x10);

	dest = NULL;

	dest = atomic_ops_ptr_load(&src, ATOMIC_OPS_FENCE_FULL);

	ck_assert(dest == (void *)0x10);
} END_TEST

Suite *test_atomic_ops_load(void) {
	Suite *s = suite_create("test_atomic_ops_load");

	TCASE_ADD(atomic_ops_load_int);
	TCASE_ADD(atomic_ops_load_uint);
	TCASE_ADD(atomic_ops_load_ptr);

	return (s);
}

/******************************************************************************/

START_TEST(test_atomic_ops_store_int) {
	atomic_ops_int dest = ATOMIC_OPS_INT_INIT(0);

	atomic_ops_int_store(&dest, -10, ATOMIC_OPS_FENCE_NONE);

	ck_assert(atomic_ops_int_load(&dest, ATOMIC_OPS_FENCE_FULL) == -10);

	atomic_ops_int_store(&dest, -20, ATOMIC_OPS_FENCE_FULL);

	ck_assert(atomic_ops_int_load(&dest, ATOMIC_OPS_FENCE_FULL) == -20);
} END_TEST

START_TEST(test_atomic_ops_store_uint) {
	atomic_ops_uint dest = ATOMIC_OPS_UINT_INIT(0);

	atomic_ops_uint_store(&dest, 10, ATOMIC_OPS_FENCE_NONE);

	ck_assert(atomic_ops_uint_load(&dest, ATOMIC_OPS_FENCE_FULL) == 10);

	atomic_ops_uint_store(&dest, 20, ATOMIC_OPS_FENCE_FULL);

	ck_assert(atomic_ops_uint_load(&dest, ATOMIC_OPS_FENCE_FULL) == 20);
} END_TEST

START_TEST(test_atomic_ops_store_ptr) {
	atomic_ops_ptr dest = ATOMIC_OPS_PTR_INIT(NULL);

	atomic_ops_ptr_store(&dest, (void *)0x10, ATOMIC_OPS_FENCE_NONE);

	ck_assert(atomic_ops_ptr_load(&dest, ATOMIC_OPS_FENCE_FULL) == (void *)0x10);

	atomic_ops_ptr_store(&dest, (void *)0x20, ATOMIC_OPS_FENCE_FULL);

	ck_assert(atomic_ops_ptr_load(&dest, ATOMIC_OPS_FENCE_FULL) == (void *)0x20);
} END_TEST

Suite *test_atomic_ops_store(void) {
	Suite *s = suite_create("test_atomic_ops_store");

	TCASE_ADD(atomic_ops_store_int);
	TCASE_ADD(atomic_ops_store_uint);
	TCASE_ADD(atomic_ops_store_ptr);

	return (s);
}

/******************************************************************************/

START_TEST(test_atomic_ops_not_int) {
	atomic_ops_int val = ATOMIC_OPS_INT_INIT(0);

	atomic_ops_int_not(&val, ATOMIC_OPS_FENCE_NONE);

	ck_assert(atomic_ops_int_load(&val, ATOMIC_OPS_FENCE_FULL) == -1);

	atomic_ops_int_not(&val, ATOMIC_OPS_FENCE_FULL);

	ck_assert(atomic_ops_int_load(&val, ATOMIC_OPS_FENCE_FULL) == 0);
} END_TEST

START_TEST(test_atomic_ops_not_uint) {
	atomic_ops_uint val = ATOMIC_OPS_UINT_INIT(0);

	atomic_ops_uint_not(&val, ATOMIC_OPS_FENCE_NONE);

	ck_assert(atomic_ops_uint_load(&val, ATOMIC_OPS_FENCE_FULL) == UINTPTR_MAX);

	atomic_ops_uint_not(&val, ATOMIC_OPS_FENCE_FULL);

	ck_assert(atomic_ops_uint_load(&val, ATOMIC_OPS_FENCE_FULL) == 0);
} END_TEST

Suite *test_atomic_ops_not(void) {
	Suite *s = suite_create("test_atomic_ops_not");

	TCASE_ADD(atomic_ops_not_int);
	TCASE_ADD(atomic_ops_not_uint);

	return (s);
}

/******************************************************************************/

START_TEST(test_atomic_ops_and_int) {
	atomic_ops_int val = ATOMIC_OPS_INT_INIT(0xF0F0);

	atomic_ops_int_and(&val, 0xFFFF, ATOMIC_OPS_FENCE_NONE);

	ck_assert(atomic_ops_int_load(&val, ATOMIC_OPS_FENCE_FULL) == 0xF0F0);

	atomic_ops_int_and(&val, 0x0110, ATOMIC_OPS_FENCE_FULL);

	ck_assert(atomic_ops_int_load(&val, ATOMIC_OPS_FENCE_FULL) == 0x0010);
} END_TEST

START_TEST(test_atomic_ops_and_uint) {
	atomic_ops_uint val = ATOMIC_OPS_UINT_INIT(0xF0F0);

	atomic_ops_uint_and(&val, 0xFFFF, ATOMIC_OPS_FENCE_NONE);

	ck_assert(atomic_ops_uint_load(&val, ATOMIC_OPS_FENCE_FULL) == 0xF0F0);

	atomic_ops_uint_and(&val, 0x0110, ATOMIC_OPS_FENCE_FULL);

	ck_assert(atomic_ops_uint_load(&val, ATOMIC_OPS_FENCE_FULL) == 0x0010);
} END_TEST

Suite *test_atomic_ops_and(void) {
	Suite *s = suite_create("test_atomic_ops_and");

	TCASE_ADD(atomic_ops_and_int);
	TCASE_ADD(atomic_ops_and_uint);

	return (s);
}

/******************************************************************************/

START_TEST(test_atomic_ops_or_int) {
	atomic_ops_int val = ATOMIC_OPS_INT_INIT(0xF0F0);

	atomic_ops_int_or(&val, 0x0F0F, ATOMIC_OPS_FENCE_NONE);

	ck_assert(atomic_ops_int_load(&val, ATOMIC_OPS_FENCE_FULL) == 0xFFFF);

	atomic_ops_int_or(&val, 0x0000, ATOMIC_OPS_FENCE_FULL);

	ck_assert(atomic_ops_int_load(&val, ATOMIC_OPS_FENCE_FULL) == 0xFFFF);
} END_TEST

START_TEST(test_atomic_ops_or_uint) {
	atomic_ops_uint val = ATOMIC_OPS_UINT_INIT(0xF0F0);

	atomic_ops_uint_or(&val, 0x0F0F, ATOMIC_OPS_FENCE_NONE);

	ck_assert(atomic_ops_uint_load(&val, ATOMIC_OPS_FENCE_FULL) == 0xFFFF);

	atomic_ops_uint_or(&val, 0x0000, ATOMIC_OPS_FENCE_FULL);

	ck_assert(atomic_ops_uint_load(&val, ATOMIC_OPS_FENCE_FULL) == 0xFFFF);
} END_TEST

Suite *test_atomic_ops_or(void) {
	Suite *s = suite_create("test_atomic_ops_or");

	TCASE_ADD(atomic_ops_or_int);
	TCASE_ADD(atomic_ops_or_uint);

	return (s);
}

/******************************************************************************/

START_TEST(test_atomic_ops_xor_int) {
	atomic_ops_int val = ATOMIC_OPS_INT_INIT(0xF0F0);

	atomic_ops_int_xor(&val, 0x0F0F, ATOMIC_OPS_FENCE_NONE);

	ck_assert(atomic_ops_int_load(&val, ATOMIC_OPS_FENCE_FULL) == 0xFFFF);

	atomic_ops_int_xor(&val, 0x0FFF, ATOMIC_OPS_FENCE_FULL);

	ck_assert(atomic_ops_int_load(&val, ATOMIC_OPS_FENCE_FULL) == 0xF000);
} END_TEST

START_TEST(test_atomic_ops_xor_uint) {
	atomic_ops_uint val = ATOMIC_OPS_UINT_INIT(0xF0F0);

	atomic_ops_uint_xor(&val, 0x0F0F, ATOMIC_OPS_FENCE_NONE);

	ck_assert(atomic_ops_uint_load(&val, ATOMIC_OPS_FENCE_FULL) == 0xFFFF);

	atomic_ops_uint_xor(&val, 0x0FFF, ATOMIC_OPS_FENCE_FULL);

	ck_assert(atomic_ops_uint_load(&val, ATOMIC_OPS_FENCE_FULL) == 0xF000);
} END_TEST

Suite *test_atomic_ops_xor(void) {
	Suite *s = suite_create("test_atomic_ops_xor");

	TCASE_ADD(atomic_ops_xor_int);
	TCASE_ADD(atomic_ops_xor_uint);

	return (s);
}

/******************************************************************************/

START_TEST(test_atomic_ops_add_int) {
} END_TEST

START_TEST(test_atomic_ops_add_uint) {
} END_TEST

Suite *test_atomic_ops_add(void) {
	Suite *s = suite_create("test_atomic_add_add");

	TCASE_ADD(atomic_ops_add_int);
	TCASE_ADD(atomic_ops_add_uint);

	return (s);
}

/******************************************************************************/

START_TEST(test_atomic_ops_inc_int) {
} END_TEST

START_TEST(test_atomic_ops_inc_uint) {
} END_TEST

Suite *test_atomic_ops_inc(void) {
	Suite *s = suite_create("test_atomic_ops_inc");

	TCASE_ADD(atomic_ops_inc_int);
	TCASE_ADD(atomic_ops_inc_uint);

	return (s);
}

/******************************************************************************/

START_TEST(test_atomic_ops_dec_int) {
} END_TEST

START_TEST(test_atomic_ops_dec_uint) {
} END_TEST

Suite *test_atomic_ops_dec(void) {
	Suite *s = suite_create("test_atomic_ops_dec");

	TCASE_ADD(atomic_ops_dec_int);
	TCASE_ADD(atomic_ops_dec_uint);

	return (s);
}

/******************************************************************************/

START_TEST(test_atomic_ops_fetch_and_add_int) {
} END_TEST

START_TEST(test_atomic_ops_fetch_and_add_uint) {
} END_TEST

Suite *test_atomic_ops_fetch_and_add(void) {
	Suite *s = suite_create("test_atomic_ops_fetch_and_add");

	TCASE_ADD(atomic_ops_fetch_and_add_int);
	TCASE_ADD(atomic_ops_fetch_and_add_uint);

	return (s);
}

/******************************************************************************/

START_TEST(test_atomic_ops_fetch_and_inc_int) {
} END_TEST

START_TEST(test_atomic_ops_fetch_and_inc_uint) {
} END_TEST

Suite *test_atomic_ops_fetch_and_inc(void) {
	Suite *s = suite_create("test_atomic_ops_fetch_and_inc");

	TCASE_ADD(atomic_ops_fetch_and_inc_int);
	TCASE_ADD(atomic_ops_fetch_and_inc_uint);

	return (s);
}

/******************************************************************************/

START_TEST(test_atomic_ops_fetch_and_dec_int) {
} END_TEST

START_TEST(test_atomic_ops_fetch_and_dec_uint) {
} END_TEST

Suite *test_atomic_ops_fetch_and_dec(void) {
	Suite *s = suite_create("test_atomic_ops_fetch_and_dec");

	TCASE_ADD(atomic_ops_fetch_and_dec_int);
	TCASE_ADD(atomic_ops_fetch_and_dec_uint);

	return (s);
}

/******************************************************************************/

START_TEST(test_atomic_ops_casr_int) {
} END_TEST

START_TEST(test_atomic_ops_casr_uint) {
} END_TEST

START_TEST(test_atomic_ops_casr_ptr) {
} END_TEST

Suite *test_atomic_ops_casr(void) {
	Suite *s = suite_create("test_atomic_ops_casr");

	TCASE_ADD(atomic_ops_casr_int);
	TCASE_ADD(atomic_ops_casr_uint);
	TCASE_ADD(atomic_ops_casr_ptr);

	return (s);
}

/******************************************************************************/

START_TEST(test_atomic_ops_cas_int) {
} END_TEST

START_TEST(test_atomic_ops_cas_uint) {
} END_TEST

START_TEST(test_atomic_ops_cas_ptr) {
} END_TEST

Suite *test_atomic_ops_cas(void) {
	Suite *s = suite_create("test_atomic_ops_cas");

	TCASE_ADD(atomic_ops_cas_int);
	TCASE_ADD(atomic_ops_cas_uint);
	TCASE_ADD(atomic_ops_cas_ptr);

	return (s);
}

/******************************************************************************/

START_TEST(test_atomic_ops_swap_int) {
} END_TEST

START_TEST(test_atomic_ops_swap_uint) {
} END_TEST

START_TEST(test_atomic_ops_swap_ptr) {
} END_TEST

Suite *test_atomic_ops_swap(void) {
	Suite *s = suite_create("test_atomic_ops_swap");

	TCASE_ADD(atomic_ops_swap_int);
	TCASE_ADD(atomic_ops_swap_uint);
	TCASE_ADD(atomic_ops_swap_ptr);

	return (s);
}

/******************************************************************************/
