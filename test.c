#include <stdio.h>
#include <stdlib.h>
#include "nodes.h"
#include "chars.h"
#include "associations.h"
#include "lexer.h"
#include "littletest.h"



void *print_int_data(void *data)
{
    if(data)
        fprintf(stderr, "%d ", *(int *)data);
    else
        fprintf(stderr, "%p\n", data);
    return data;
}

void *print_chars_data(void *data)
{
    fprintf(stderr, "%s\n", (char *)data);
    return data;
}

void *plus_five(void *data)
{
    int *tmp;
    if(data){
        tmp = (int *)data;
        *tmp = *tmp + 5;
        return tmp;
    }
    return NULL;
}

void *printchars(void *data)
{
    fprintf(stderr, "%s\n", (char *)data);
    return data;
}

void nodes_test()
{
    struct nodes *nds, *nds2;
    int arr[] = {17, 19, 13, 11, -4, -10, 0};
    int sum, i;
    char *s1, *s2;

    /* Set up */
    littletest_set_up(0, 0);
    nds = nodes_new();
    s1 = "aboba";
    s2 = "hello";
    fprintf(stderr, "\n\nNODES TEST\n");

    
    /* Test 1 */
    assert_equal_int(nodes_length(nds), 0);


    /* Test 2 */
    nodes_push_front(nds, arr);
    nodes_push_front(nds, arr + 1);
    nodes_push_back(nds, arr + 2);
    assert_equal_int(nodes_length(nds), 3);


    /* Test 3 */
    nodes_set(nds, 0, arr + 3);
    assert_equal_int(*(int *)nodes_get(nds, 0), arr[3]);


    /* Test 4 */
    nodes_insert(nds, 1, s1);
    nodes_remove(nds, 0, nodes_pass);
    assert_equal_string((char *)nodes_get_front(nds), "aboba");
    
    /* Test 5 */
    nodes_set_front(nds, s2);
    assert_equal_string((char *)nodes_get(nds, 0), "hello");


    /* Test 6 */
    assert_equal_int(nodes_length(nds), 3);


    /* Test 7 */
    nodes_remove_front(nds, nodes_pass);
    nodes_push_back(nds, arr + 1);
    nodes_push_back(nds, arr + 3);

    assert_equal_int(*(int *)nodes_get_back(nds) +
            *(int *)nodes_get(nds, 1), 24);


    /* Test 8 */
    nodes_iter(nds, plus_five);
    assert_equal_int(*(int *)nodes_get(nds, 1), 18);


    /* Test 9 */
    nodes_push_back(nds, arr + 5);
    nodes_push_back(nds, arr + 6);
    nodes_insert(nds, 3, arr + 4);
    nodes_remove(nds, 3, nodes_pass);
    nodes_remove_front(nds, nodes_pass);
    nodes_remove_back(nds, nodes_pass);
    assert_equal_int(*(int *)nodes_get(nds, 3), -10);


    /* Test 10 */
    sum = 0;
    for(i = 0; i < nodes_length(nds); i++){
        sum += *(int *)nodes_get(nds, i);
    }
    assert_equal_int(sum, 48);

    /* Test 11 */
    nodes_pop(nds);
    nodes_pop(nds);
    assert_equal_int(*(int *)nodes_pop(nds), 24); 



    /* Test 12 */
    nodes_push_back(nds, arr);
    nodes_push_back(nds, arr + 1);
    nodes_push_back(nds, arr + 2);
    nodes_push_back(nds, arr + 3);

    fprintf(stderr, "\n");
    nodes_iter(nds, print_int_data);
    fprintf(stderr, "\n");
    nds2 = nodes_slice(nds, 1, 3);
    fprintf(stderr, "\n");
    nodes_iter(nds2, print_int_data);
    fprintf(stderr, "\n");


    littletest_sum_up();
    nodes_free(nds, nodes_pass);
}


void chars_test()
{
    char *ch1, *ch2, *ch3, *ch4;
    struct nodes *n;

    /* Set up */
    littletest_set_up(0, 0);
    fprintf(stderr, "\n\nCHARS TEST\n");

    /* Test 1 */
    assert_equal_string(chars_from("aboba"), "aboba");

    /* Test 2 */
    assert_equal_string(chars_from(""), "");

    /* Test 3 */
    assert_equal_string(chars_from("\0"), "\0");

    /* Test 4 */
    ch1 = chars_from("hello world");
    assert_equal_int(chars_length(ch1), 11);

    /* Test 5 */
    ch1 = chars_from("");
    assert_equal_int(chars_length(ch1), 0);

    /* Test 6 */
    ch1 = chars_from("11111");
    chars_set(ch1, '2', 3);
    assert_equal_string(ch1, "22211");

    /* Test 7 */
    ch1 = chars_from("aboba");
    ch2 = chars_lfind(ch1, "b");
    assert_equal_string(ch2, "boba");

    /* Test 8 */
    ch1 = chars_from("aboba");
    ch2 = chars_rfind(ch1, "b");
    assert_equal_string(ch2, "ba");

    /* Test 9 */
    ch1 = chars_from("aboba");
    ch2 = chars_lfind(ch1, "x");
    assert_equal_pointer(ch2, NULL);

    /* Test 10 */
    ch1 = chars_from(",one,two,three,four,");
    ch2 = chars_from(",");
    assert_equal_int(chars_count(ch1, ch2), 5);

    /* Test 11 */
    ch1 = chars_from("aboba");
    ch2 = chars_from("x");
    assert_equal_int(chars_count(ch1, ch2), 0);

    /* Test 12 */
    ch1 = chars_from("roses are red");
    ch2 = chars_from("r");
    assert_equal_int(chars_count(ch1, ch2), 3);

    /* Test 13 */
    ch1 = chars_from("roses are red");
    ch2 = chars_from("roses");
    assert_equal_int(chars_startswith(ch1, ch2), 1);

    /* Test 14 */
    ch1 = chars_from("roses are red");
    ch2 = chars_from("are");
    assert_equal_int(chars_startswith(ch1, ch2), 0);

    /* Test 15 */
    ch1 = chars_from(" hello");
    ch2 = chars_from(" ");
    assert_equal_int(chars_startswith(ch1, ch2), 1);

    /* Test 16 */
    ch1 = chars_from("roses are red");
    ch2 = chars_from("are red");
    assert_equal_int(chars_endswith(ch1, ch2), 1);

    /* Test 17 */
    ch1 = chars_from("roses are red");
    ch2 = chars_from("are");
    assert_equal_int(chars_endswith(ch1, ch2), 0);

    /* Test 18 */
    ch1 = chars_from("hello ");
    ch2 = chars_from(" ");
    assert_equal_int(chars_endswith(ch1, ch2), 1);

    /* Test 19 */
    ch1 = chars_from("aboba");
    ch2 = chars_from("aboba");
    assert_equal_int(chars_endswith(ch1, ch2), 1);

    /* Test 20 */
    ch1 = chars_from("aboba");
    assert_equal_int(chars_is_integer(ch1), 0);

    /* Test 21 */
    ch1 = chars_from("439010");
    assert_equal_int(chars_is_integer(ch1), 1);

    /* Test 22 */
    ch1 = chars_from("00043");
    assert_equal_int(chars_is_integer(ch1), 1);

    /* Test 23 */
    ch1 = chars_from("238.08");
    assert_equal_int(chars_is_integer(ch1), 0);

    /* Test 24 */
    ch1 = chars_from("941o75");
    assert_equal_int(chars_is_integer(ch1), 0);

    /* Test 25 */
    ch1 = chars_from(".048349");
    assert_equal_int(chars_is_float(ch1), 1);

    /* Test 26 */
    ch1 = chars_from("4389");
    assert_equal_int(chars_is_float(ch1), 1);

    /* Test 27 */
    ch1 = chars_from("09.a8");
    assert_equal_int(chars_is_float(ch1), 0);

    /* Test 28 */
    ch1 = chars_from("13.0.038");
    assert_equal_int(chars_is_float(ch1), 0);

    /* Test 29 */
    ch1 = chars_from("893.");
    assert_equal_int(chars_is_float(ch1), 0);

    /* Test 30 */
    ch1 = chars_from("0.12");
    assert_equal_int(chars_is_float(ch1), 1);

    /* Test 31 */
    ch1 = chars_from("aboba");
    ch2 = chars_from("b");
    ch3 = chars_from("");
    ch4 = chars_replace(ch1, ch2, ch3);
    assert_equal_string(ch4, "aoa");

    /* Test 32 */
    ch1 = chars_from("aboba");
    ch2 = chars_from("aboba");
    ch3 = chars_from("");
    ch4 = chars_replace(ch1, ch2, ch3);
    assert_equal_string(ch4, "");

    /* Test 33 */
    ch1 = chars_from("the \"before\" string");
    ch2 = chars_from("before");
    ch3 = chars_from("after");
    ch4 = chars_replace(ch1, ch2, ch3);
    assert_equal_string(ch4, "the \"after\" string");

    /* Test 34 */
    ch1 = chars_from("011000110");
    ch2 = chars_from("11");
    ch3 = chars_from("VVVV");
    ch4 = chars_replace(ch1, ch2, ch3);
    assert_equal_string(ch4, "0VVVV000VVVV0");

    /* Test 35 */
    ch1 = chars_from("flowers are red");
    ch2 = chars_from("red");
    ch3 = chars_from("blue");
    ch4 = chars_replace(ch1, ch2, ch3);
    assert_equal_string(ch4, "flowers are blue");

    /* Test 36 */
    ch1 = chars_from("flowers");
    ch2 = chars_reverse(ch1);
    assert_equal_string(ch2, "srewolf");

    /* Test 37 */
    ch1 = chars_from("");
    ch2 = chars_reverse(ch1);
    assert_equal_string(ch2, "");

    /* Test 38 */
    ch1 = chars_from("hello world");
    ch2 = chars_reverse(ch1);
    assert_equal_string(ch2, "dlrow olleh");

    /* Test 39 */
    ch1 = chars_from("1234");
    ch2 = chars_reverse(ch1);
    assert_equal_string(ch2, "4321");

    /* Test 40 */
    ch1 = chars_from("hello ");
    ch2 = chars_from("world");
    ch3 = chars_add(ch1, ch2);
    assert_equal_string(ch3, "hello world");

    /* Test 41 */
    ch1 = chars_from("");
    ch2 = chars_from("");
    ch3 = chars_add(ch1, ch2);
    assert_equal_string(ch3, "");

    /* Test 42 */
    ch1 = chars_from("");
    ch2 = chars_from("60");
    ch3 = chars_add(ch1, ch2);
    assert_equal_string(ch3, "60");

    /* Test 43 */
    ch1 = chars_from("1234");
    ch2 = chars_from("");
    ch3 = chars_add(ch1, ch2);
    assert_equal_string(ch3, "1234");

    /* Test 44 */
    ch1 = chars_from("hello ");
    ch2 = chars_from("world");
    ch3 = chars_add(ch1, ch2);
    assert_equal_int(chars_length(ch3), 11);
    
    /* Test 45 */
    ch1 = chars_from("hello world");
    ch2 = chars_slice(ch1, 3, 7);
    assert_equal_int(chars_length(ch2), 4);
    
    /* Test 46 */
    ch1 = chars_from("roses are red");
    ch2 = chars_slice(ch1, 0, 8);
    assert_equal_int(chars_length(ch2), 8);
    
    /* Test 47 */
    ch1 = chars_from("hello world");
    ch2 = chars_slice(ch1, 0, 4);
    assert_equal_string(ch2, "hell");
    
    /* Test 48 */
    ch1 = chars_from("roses are red");
    ch2 = chars_slice(ch1, 7, 8);
    assert_equal_string(ch2, "r");
    
    /* Test 49 */
    ch1 = chars_from("hello");
    ch2 = chars_slice(ch1, 1, 1);
    assert_equal_string(ch2, "");
    
    /* Test 50 */
    ch1 = chars_from("aboba");
    ch2 = chars_slice(ch1, 0, 5);
    assert_equal_string(ch2, "aboba");
    
    /* Test 51 */
    ch1 = chars_from(",133,ac,,da,");
    ch2 = chars_from(",");
    n = chars_split(ch1, ch2);
    assert_equal_string((char *)nodes_get(n, 0), "133");

    /* Test 52 */
    assert_equal_string((char *)nodes_get(n, 1), "ac");

    /* Test 53 */
    assert_equal_string((char *)nodes_get(n, 2), "da");

    /* Test 54 */
    ch1 = chars_from("hihellofromhellothere");
    ch2 = chars_from("hello");
    n = chars_split(ch1, ch2);
    assert_equal_int(nodes_length(n), 3);

    /* Test 55 */
    ch1 = chars_from("hello");
    ch2 = chars_from("world");
    assert_equal_int(chars_similar(ch1, ch2), 0);

    /* Test 56 */
    ch2 = chars_from("hello");
    assert_equal_int(chars_similar(ch1, ch2), 1);


    littletest_sum_up();
    nodes_free(n, free);
}


void *valfunc(void *data)
{
    int *i;
    i = (int *)data;
    *i += 10;
    return data;
}

char *keyfunc(char *key)
{
    return chars_reverse(key);
}

void associations_test()
{
    struct associations *as;
    char *ch1, *ch2, *ch3, *ch4;
    int arr[] = {1, 2, 3, 4, 5};
    /* Set up */
    littletest_set_up(0, 0);
    fprintf(stderr, "\n\nASSOCIATIONS TEST\n");

    /* Test 1 */
    as = associations_new(1);
    ch1 = chars_from("hello");
    ch2 = chars_from("world");
    associations_set(as, ch1, ch2);
    ch3 = (char *)associations_get(as, ch1);
    assert_equal_string(ch3, "world");

    /* Test 2 */
    assert_equal_string((char *)associations_get(as, "hello"), "world");

    /* Test 3 */
    ch1 = chars_from("one");
    ch2 = chars_from("two");
    ch3 = chars_from("three");
    ch4 = chars_from("four");
    associations_set(as, ch1, arr);
    associations_set(as, ch2, arr + 1);
    associations_set(as, ch3, arr + 2);
    associations_set(as, ch4, arr + 3);
    assert_equal_int(*(int *)associations_get(as, ch1), 1);

    /* Test 4 */
    assert_equal_int(*(int *)associations_get(as, ch2), 2);

    /* Test 5 */
    assert_equal_int(*(int *)associations_get(as, ch3), 3);

    /* Test 6 */
    assert_equal_int(*(int *)associations_get(as, ch4), 4);

    /* Test 7 */
    associations_remove(as, "hello");
    assert_equal_int(associations_length(as), 4);

    /* Test 8 */
    associations_iter(as, valfunc);
    assert_equal_int(*(int *)associations_get(as, "three"), 13);

    /* Test 9 */
    assert_equal_pointer(associations_get(as, "six"), NULL);


    littletest_sum_up();
}

void *print_token_data(void *data)
{
    struct token *t;
    t = (struct token *)data;
    fprintf(stderr, "%s\t\t\t%d\n", t->str, t->type);
    return data;
}


void lexer_test()
{
    struct token *tok;
    char *input;
    struct nodes *tokens;

    /* Set up */
    littletest_set_up(0, 0);

    /* Simple tests */
    /* Test 1 */
    input = "123 + 45.6";
    tokens = lexer(input);
    assert_equal_int(nodes_length(tokens), 3);

    /* Test 2 */
    tok = nodes_get(tokens, 0);
    assert_equal_int(tok->type, token_integer);

    /* Test 3 */
    assert_equal_string(tok->str, "123");

    /* Test 4 */
    tok = nodes_get(tokens, 1);
    assert_equal_int(tok->type, token_add);

    /* Test 5 */
    assert_equal_string(tok->str, "+");

    /* Test 6 */
    tok = nodes_get(tokens, 2);
    assert_equal_int(tok->type, token_float);

    /* Test 7 */
    assert_equal_string(tok->str, "45.6");




    /* Identifiers */
    input = "my_variable some_function(function_call) anotherVar";
    tokens = lexer(input);

    /* Test 8 */
    assert_equal_int(nodes_length(tokens), 4);

    /* Test 9 */
    tok = nodes_get(tokens, 0);
    assert_equal_int(tok->type, token_identifier);

    /* Test 10 */
    assert_equal_string(tok->str, "my_variable");

    /* Test 11 */
    tok = nodes_get(tokens, 1);
    assert_equal_int(tok->type, token_identifier);

    /* Test 12 */
    assert_equal_string(tok->str, "some_function");

    /* Test 13*/
    tok = nodes_get(tokens, 2);
    assert_equal_int(tok->type, token_call);

    /* Test 14*/
    assert_equal_string(tok->str, "(function_call)");

    /* Test 15*/
    tok = nodes_get(tokens, 3);
    assert_equal_int(tok->type, token_identifier);

    /* Test 16*/
    assert_equal_string(tok->str, "anotherVar");




    /* Numbers */
    input = "123 -456 789.123";
    tokens = lexer(input);

    /* Test 17 */
    assert_equal_int(nodes_length(tokens), 4);

    /* Test 18 */
    tok = nodes_get(tokens, 0);
    assert_equal_int(tok->type, token_integer);

    /* Test 19 */
    assert_equal_string(tok->str, "123");

    /* Test 20 */
    tok = nodes_get(tokens, 1);
    assert_equal_int(tok->type, token_sub);

    /* Test 21 */
    assert_equal_string(tok->str, "-");

    /* Test 22 */
    tok = nodes_get(tokens, 2);
    assert_equal_int(tok->type, token_integer);

    /* Test 23 */
    assert_equal_string(tok->str, "456");

    /* Test 24 */
    tok = nodes_get(tokens, 3);
    assert_equal_int(tok->type, token_float);

    /* Test 25 */
    assert_equal_string(tok->str, "789.123");




    /* Operators */
    input = "! = + - * / % . < > != == += -= *= /= %= .. <= >= or and not return break continue raise true false";
    tokens = lexer(input);

    /* Test 26 */
    assert_equal_int(nodes_length(tokens), 29);

    /* Test 27 */
    tok = nodes_get(tokens, 0);
    assert_equal_int(tok->type, token_not);

    /* Test 28 */
    assert_equal_string(tok->str, "!");

    /* Test 29 */
    tok = nodes_get(tokens, 1);
    assert_equal_int(tok->type, token_eql);

    /* Test 30 */
    assert_equal_string(tok->str, "=");

    /* Test 31 */
    tok = nodes_get(tokens, 2);
    assert_equal_int(tok->type, token_add);

    /* Test 32 */
    assert_equal_string(tok->str, "+");

    /* Test 33 */
    tok = nodes_get(tokens, 3);
    assert_equal_int(tok->type, token_sub);

    /* Test 34 */
    assert_equal_string(tok->str, "-");

    /* Test 35 */
    tok = nodes_get(tokens, 4);
    assert_equal_int(tok->type, token_mul);

    /* Test 36 */
    assert_equal_string(tok->str, "*");

    /* Test 37 */
    tok = nodes_get(tokens, 5);
    assert_equal_int(tok->type, token_div);

    /* Test 38 */
    assert_equal_string(tok->str, "/");

    /* Test 39 */
    tok = nodes_get(tokens, 6);
    assert_equal_int(tok->type, token_mod);

    /* Test 40 */
    assert_equal_string(tok->str, "%");

    /* Test 41 */
    tok = nodes_get(tokens, 7);
    assert_equal_int(tok->type, token_mem);

    /* Test 42 */
    assert_equal_string(tok->str, ".");

    /* Test 43 */
    tok = nodes_get(tokens, 8);
    assert_equal_int(tok->type, token_l);

    /* Test 44 */
    assert_equal_string(tok->str, "<");

    /* Test 45 */
    tok = nodes_get(tokens, 9);
    assert_equal_int(tok->type, token_g);

    /* Test 46 */
    assert_equal_string(tok->str, ">");

    /* Test 47 */
    tok = nodes_get(tokens, 10);
    assert_equal_int(tok->type, token_noteql);

    /* Test 48 */
    assert_equal_string(tok->str, "!=");

    /* Test 49 */
    tok = nodes_get(tokens, 11);
    assert_equal_int(tok->type, token_eqleql);

    /* Test 50 */
    assert_equal_string(tok->str, "==");

    /* Test 51 */
    tok = nodes_get(tokens, 12);
    assert_equal_int(tok->type, token_addeql);

    /* Test 52 */
    assert_equal_string(tok->str, "+=");

    /* Test 53 */
    tok = nodes_get(tokens, 13);
    assert_equal_int(tok->type, token_subeql);

    /* Test 54 */
    assert_equal_string(tok->str, "-=");

    /* Test 55 */
    tok = nodes_get(tokens, 14);
    assert_equal_int(tok->type, token_muleql);

    /* Test 56 */
    assert_equal_string(tok->str, "*=");

    /* Test 57 */
    tok = nodes_get(tokens, 15);
    assert_equal_int(tok->type, token_diveql);

    /* Test 58 */
    assert_equal_string(tok->str, "/=");

    /* Test 59 */
    tok = nodes_get(tokens, 16);
    assert_equal_int(tok->type, token_modeql);

    /* Test 60 */
    assert_equal_string(tok->str, "%=");

    /* Test 61 */
    tok = nodes_get(tokens, 17);
    assert_equal_int(tok->type, token_range);

    /* Test 62 */
    assert_equal_string(tok->str, "..");

    /* Test 63 */
    tok = nodes_get(tokens, 18);
    assert_equal_int(tok->type, token_le);

    /* Test 64 */
    assert_equal_string(tok->str, "<=");

    /* Test 65 */
    tok = nodes_get(tokens, 19);
    assert_equal_int(tok->type, token_ge);

    /* Test 66 */
    assert_equal_string(tok->str, ">=");

    /* Test 67 */
    tok = nodes_get(tokens, 20);
    assert_equal_int(tok->type, token_or);

    /* Test 68 */
    assert_equal_string(tok->str, "or");

    /* Test 69 */
    tok = nodes_get(tokens, 21);
    assert_equal_int(tok->type, token_and);

    /* Test 70 */
    assert_equal_string(tok->str, "and");

    /* Test 71 */
    tok = nodes_get(tokens, 22);
    assert_equal_int(tok->type, token_not);

    /* Test 72 */
    assert_equal_string(tok->str, "not");

    /* Test 73 */
    tok = nodes_get(tokens, 23);
    assert_equal_int(tok->type, token_return);

    /* Test 74 */
    assert_equal_string(tok->str, "return");

    /* Test 75 */
    tok = nodes_get(tokens, 24);
    assert_equal_int(tok->type, token_break);

    /* Test 76 */
    assert_equal_string(tok->str, "break");

    /* Test 77 */
    tok = nodes_get(tokens, 25);
    assert_equal_int(tok->type, token_continue);

    /* Test 78 */
    assert_equal_string(tok->str, "continue");

    /* Test 79 */
    tok = nodes_get(tokens, 26);
    assert_equal_int(tok->type, token_raise);

    /* Test 80 */
    assert_equal_string(tok->str, "raise");

    /* Test 81 */
    tok = nodes_get(tokens, 27);
    assert_equal_int(tok->type, token_true);

    /* Test 82 */
    assert_equal_string(tok->str, "true");

    /* Test 83 */
    tok = nodes_get(tokens, 28);
    assert_equal_int(tok->type, token_false);

    /* Test 84 */
    assert_equal_string(tok->str, "false");




    /* Strings */
    input = "\"helloworld\" \"this is a string\"";
    tokens = lexer(input);

    /* Test 85 */
    assert_equal_int(nodes_length(tokens), 2);

    /* Test 86 */
    tok = nodes_get(tokens, 0);
    assert_equal_int(tok->type, token_string);

    /* Test 87 */
    assert_equal_string(tok->str, "\"helloworld\"");

    /* Test 88 */
    tok = nodes_get(tokens, 1);
    assert_equal_int(tok->type, token_string);

    /* Test 89 */
    assert_equal_string(tok->str, "\"this is a string\"");

    /* Test escaped characters */
    input = "\"hello\\\"world\" \"string\\nwith\\tescapes\"";
    tokens = lexer(input);

    /* Test 90 */
    assert_equal_int(nodes_length(tokens), 2);

    /* Test 91 */
    tok = nodes_get(tokens, 0);
    assert_equal_int(tok->type, token_string);

    /* Test 92 */
    assert_equal_string(tok->str, "\"hello\\\"world\"");

    /* Test 93 */
    tok = nodes_get(tokens, 1);
    assert_equal_int(tok->type, token_string);

    /* Test 94 */
    assert_equal_string(tok->str, "\"string\\nwith\\tescapes\"");

    /* Test russian letters */
    input = "\"привет\" \"Меня зовут чел\"";
    tokens = lexer(input);

    /* Test 95 */
    assert_equal_int(nodes_length(tokens), 2);

    /* Test 96 */
    tok = nodes_get(tokens, 0);
    assert_equal_int(tok->type, token_string);

    /* Test 97 */
    assert_equal_string(tok->str, "\"привет\"");

    /* Test 98 */
    tok = nodes_get(tokens, 1);
    assert_equal_int(tok->type, token_string);

    /* Test 99 */
    assert_equal_string(tok->str, "\"Меня зовут чел\"");




    /* Containers */
    
    /* list */
    input = "{1, 2, 3}";
    tokens = lexer(input);

    /* Test 100 */
    assert_equal_int(nodes_length(tokens), 1);

    /* Test 101 */
    tok = nodes_get(tokens, 0);
    assert_equal_int(tok->type, token_list);

    /* Test 102 */
    assert_equal_string(tok->str, "{1, 2, 3}");

    /* hashmap */
    input = "{\"key1\": value1, \"key2\": value2}";
    tokens = lexer(input);

    /* Test 103 */
    assert_equal_int(nodes_length(tokens), 1);

    /* Test 104 */
    tok = nodes_get(tokens, 0);
    assert_equal_int(tok->type, token_hashmap);

    /* Test 105 */
    assert_equal_string(tok->str, "{\"key1\": value1, \"key2\": value2}");

    /* empty list */
    input = "{}";
    tokens = lexer(input);

    /* Test 106 */
    assert_equal_int(nodes_length(tokens), 1);

    /* Test 107 */
    tok = nodes_get(tokens, 0);
    assert_equal_int(tok->type, token_list);

    /* Test 108 */
    assert_equal_string(tok->str, "{}");

    /* empty hashmap */
    input = "{:}";
    tokens = lexer(input);

    /* Test 109 */
    assert_equal_int(nodes_length(tokens), 1);

    /* Test 110 */
    tok = nodes_get(tokens, 0);
    assert_equal_int(tok->type, token_hashmap);

    /* Test 111 */
    assert_equal_string(tok->str, "{:}");

    /* nested list */
    input = "{1, {2, 3}}";
    tokens = lexer(input);

    /* Test 112 */
    assert_equal_int(nodes_length(tokens), 1);

    /* Test 113 */
    tok = nodes_get(tokens, 0);
    assert_equal_int(tok->type, token_list);

    /* Test 114 */
    assert_equal_string(tok->str, "{1, {2, 3}}");

    /* with an additional element */
    input = "{1, {2, 3}, 4}";
    tokens = lexer(input);

    /* Test 115 */
    assert_equal_int(nodes_length(tokens), 1);

    /* Test 116 */
    tok = nodes_get(tokens, 0);
    assert_equal_int(tok->type, token_list);

    /* Test 117 */
    assert_equal_string(tok->str, "{1, {2, 3}, 4}");

    /* only nested list */
    input = "{{2, 3}}";
    tokens = lexer(input);

    /* Test 118 */
    assert_equal_int(nodes_length(tokens), 1);

    /* Test 119 */
    tok = nodes_get(tokens, 0);
    assert_equal_int(tok->type, token_list);

    /* Test 120 */
    assert_equal_string(tok->str, "{{2, 3}}");

    /* hashmap in a list */
    input = "{1, {\"b\": 2}}";
    tokens = lexer(input);

    /* Test 121 */
    assert_equal_int(nodes_length(tokens), 1);

    /* Test 122 */
    tok = nodes_get(tokens, 0);
    assert_equal_int(tok->type, token_list);

    /* Test 123 */
    assert_equal_string(tok->str, "{1, {\"b\": 2}}");

    /* nested hashmap */
    input = "{\"key1\": {\"key3\": value3, \"key4\": value4}, \"key2\": value2}";
    tokens = lexer(input);

    /* Test 124 */
    assert_equal_int(nodes_length(tokens), 1);

    /* Test 125 */
    tok = nodes_get(tokens, 0);
    assert_equal_int(tok->type, token_hashmap);

    /* Test 126 */
    assert_equal_string(tok->str, "{\"key1\": {\"key3\": value3, \"key4\": value4}, \"key2\": value2}");

    /* only nested hashmap */
    input = "{\"key1\": {\"key3\": value3, \"key4\": value4}}";
    tokens = lexer(input);

    /* Test 127 */
    assert_equal_int(nodes_length(tokens), 1);

    /* Test 128 */
    tok = nodes_get(tokens, 0);
    assert_equal_int(tok->type, token_hashmap);

    /* Test 129 */
    assert_equal_string(tok->str, "{\"key1\": {\"key3\": value3, \"key4\": value4}}");

    /* with element before and after
    (this makes the most sense, I guess we
    could use less tests, but make them more complex) */
    /* only nested hashmap */
    input = "{\"key0\": value0, \"key1\": {\"key3\": value3, \"key4\": value4}, \"key2\": {value2, value5}} {\"b\": {2, 3}}";
    tokens = lexer(input);

    /* Test 130 */
    assert_equal_int(nodes_length(tokens), 2);

    /* Test 131 */
    tok = nodes_get(tokens, 0);
    assert_equal_int(tok->type, token_hashmap);

    /* Test 132 */
    assert_equal_string(tok->str, "{\"key0\": value0, \"key1\": {\"key3\": value3, \"key4\": value4}, \"key2\": {value2, value5}}");

    /* Test 133 */
    tok = nodes_get(tokens, 1);
    assert_equal_int(tok->type, token_hashmap);

    /* Test 134 */
    assert_equal_string(tok->str, "{\"b\": {2, 3}}");

    /* Nested nested list and hashmap*/
    input = "{\"key0\": value0, \"key1\": {\"key3\": {\"key5\": value5}, \"key4\": value4}, \"key2\": {value2, value5}} {1, {2, 2, {3, 3}}}";
    tokens = lexer(input);

    /* Test 135 */
    tok = nodes_get(tokens, 0);
    assert_equal_int(tok->type, token_hashmap);

    /* Test 136 */
    assert_equal_string(tok->str, "{\"key0\": value0, \"key1\": {\"key3\": {\"key5\": value5}, \"key4\": value4}, \"key2\": {value2, value5}}");

    /* Test 137 */
    tok = nodes_get(tokens, 1);
    assert_equal_int(tok->type, token_list);

    /* Test 138 */
    assert_equal_string(tok->str, "{1, {2, 2, {3, 3}}}");

    /* Function calls */
    input = "foo(1, 2)(5, 6)";
    tokens = lexer(input);

    /* Test 139 */
    assert_equal_int(nodes_length(tokens), 3);

    /* Test 140 */
    tok = nodes_get(tokens, 0);
    assert_equal_int(tok->type, token_identifier);

    /* Test 141 */
    assert_equal_string(tok->str, "foo");

    /* Test 142 */
    tok = nodes_get(tokens, 1);
    assert_equal_int(tok->type, token_call);

    /* Test 143 */
    assert_equal_string(tok->str, "(1, 2)");

    /* Test 144 */
    tok = nodes_get(tokens, 2);
    assert_equal_int(tok->type, token_call);

    /* Test 145 */
    assert_equal_string(tok->str, "(5, 6)");

    /* chuchu */
    input = "(1, 2)(5, 6)";
    tokens = lexer(input);

    /* Test 146 */
    assert_equal_int(nodes_length(tokens), 5);

    /* Test 147 */
    tok = nodes_get(tokens, 0);
    assert_equal_int(tok->type, token_open_bracket);

    /* Test 148 */
    assert_equal_string(tok->str, "(");

    /* Test 149 */
    tok = nodes_get(tokens, 1);
    assert_equal_int(tok->type, token_integer);

    /* Test 150 */
    assert_equal_string(tok->str, "1");

    /* Test 151 */
    tok = nodes_get(tokens, 2);
    assert_equal_int(tok->type, token_integer);

    /* Test 152 */
    assert_equal_string(tok->str, "2");

    /* Test 153 */
    tok = nodes_get(tokens, 3);
    assert_equal_int(tok->type, token_close_bracket);

    /* Test 154 */
    assert_equal_string(tok->str, ")");

    /* Test 155 */
    tok = nodes_get(tokens, 4);
    assert_equal_int(tok->type, token_call);

    /* Test 156 */
    assert_equal_string(tok->str, "(5, 6)");

    littletest_sum_up();
}



int main()
{
    lexer_test();
    /*nodes_test();
    chars_test();
    associations_test();*/
    return 0;
}
