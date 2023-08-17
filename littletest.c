#include <stdio.h>
#include <time.h>
#include "littletest.h"





/* local functions */
static int compare_strings(const char *s1, const char *s2)
{
    while(*s1 == *s2){
        if(*s1 == '\0')
            return 1;
        s1++;
        s2++;
    }
    return 0;
}

static void int_to_string(char *buf, int n)
{
    sprintf(buf, "%-50d", n);
}

static void double_to_string(char *buf, double d)
{
    sprintf(buf, "%-50lf", d);
}

static void char_to_string(char *buf, char c)
{
    sprintf(buf, "%-1c", c);
}


static void pointer_to_string(char *buf, void *p)
{
    sprintf(buf, "%-20p", p);
}






enum littletest_action {increment, get, set};


static int littletest_counter(enum littletest_action action, int n)
{
    static int counter = 0;
    switch(action){
        case set:
            counter = n;
            break;
        case increment:
            counter++;
            break;
        case get:
            break;
    }
    return counter;
}

static int littletest_passed(enum littletest_action action, int n)
{
    static int passed = 0;
    switch(action){
        case set:
            passed = n;
            break;
        case increment:
            passed++;
            break;
        case get:
            break;
    }
    return passed;
}


static void passed()
{
    littletest_counter(increment, 0);
    littletest_passed(increment, 0);
    fprintf(stderr, "Test %d passed.\n", littletest_counter(get, 0));
}


static void failed(const char *a, const char *b)
{
    littletest_counter(increment, 0);
    fprintf(stderr, "\n==============\n");
    fprintf(stderr, "Test %d FAILED:\n", littletest_counter(get, 0));
    fprintf(stderr, "Expected %s\nGot %s\n", a, b);
    fprintf(stderr, "==============\n\n");
}



/* Interface functions */

int littletest_time(void (*func)())
{
    clock_t start, diff;
    int msec;
    start = clock();
    func();
    diff = clock() - start;
    msec = diff * 1000 / CLOCKS_PER_SEC;
    return msec;
}

int littletest_get_passed()
{
    return littletest_passed(get, 0);
}

int littletest_get_count()
{
    return littletest_counter(get, 0);
}

void littletest_set_up(int passed, int counter)
{
    littletest_counter(set, counter);
    littletest_passed(set, passed); 
}


void littletest_sum_up()
{
    fprintf(stderr,
            "%d/%d tests passed.\n",
            littletest_passed(get, 0),
            littletest_counter(get, 0));
}

void assert_equal_int(int a, int b)
{
    if(a == b)
        passed();
    else{
        char bufa[51];
        char bufb[51];
        int_to_string(bufa, a);
        int_to_string(bufb, b);
        failed(bufa, bufb);
    }
}

void assert_equal_double(double a, double b)
{
    if(a == b)
        passed();
    else{
        char bufa[51];
        char bufb[51];
        double_to_string(bufa, a);
        double_to_string(bufb, b);
        failed(bufa, bufb);
    }
}

void assert_equal_char(char a, char b)
{
    if(a == b)
        passed();
    else{
        char bufa[2];
        char bufb[2];
        char_to_string(bufa, a);
        char_to_string(bufb, b);
        failed(bufa, bufb);
    }
}

void assert_equal_string(char *a, char *b)
{
    if(compare_strings(a, b))
        passed();
    else
        failed(a, b);
}


void assert_equal_pointer(void *a, void *b)
{
    if(a == b)
        passed();
    else{
        char bufa[21];
        char bufb[21];
        pointer_to_string(bufa, a);
        pointer_to_string(bufb, b);
        failed(bufa, bufb);
    }
}





