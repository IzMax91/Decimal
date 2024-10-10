#include <stdlib.h>

#include "test.h"

int main() {
  int no_failed = 0;
  Suite *s;
  SRunner *runner;
  Suite *list_cases[] = {s21_from_int_to_decimal_test(),
                         s21_from_decimal_to_int_test(),
                         s21_from_float_to_decimal_test(),
                         s21_from_decimal_to_float_test(),
                         s21_floor_test(),
                         s21_round_test(),
                         s21_truncate_test(),
                         s21_negate_test(),
                         add_suite1(),
                         sub_suite1(),
                         mul_suite1(),
                         div_suite1(),
                         s21_is_less_test(),
                         s21_is_less_or_equal_test(),
                         s21_is_greater_test(),
                         s21_is_greater_or_equal_test(),
                         s21_is_equal_test(),
                         s21_is_not_equal_test(),
                         NULL};

  for (int i = 0; list_cases[i] != NULL; i++) {
    s = list_cases[i];
    runner = srunner_create(s);

    srunner_run_all(runner, CK_NORMAL);
    no_failed += srunner_ntests_failed(runner);
    srunner_free(runner);
  }
  return (no_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
