#ifndef LITTLETEST_H_SENTRY
#define LITTLETEST_H_SENTRY

int littletest_time(void (*func)());

int littletest_get_passed();

int littletest_get_count();

void littletest_set_up(int passed, int counter);

void littletest_sum_up();

void assert_equal_int(int a, int b);

void assert_equal_double(double a, double b);

void assert_equal_char(char a, char b);

void assert_equal_string(char *a, char *b);

void assert_equal_pointer(void *a, void *b);

#endif
