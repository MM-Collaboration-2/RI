#ifndef LEXER_H_SENTRY
#define LEXER_H_SENTRY

#define MAX_TOKEN_COUNT 20

#define STRING '"'
#define END_EXPRESSION ';'
#define TYPE_ANNOTATION ':'
#define OPEN_PARENTHESIS '('
#define CLOSE_PARENTHESIS ')'
#define OPEN_CONTAINER '{'
#define CLOSE_CONTAINER '}'

#define OPERATOR_EQL '='
#define OPERATOR_ADD '+'
#define OPERATOR_SUB '-'
#define OPERATOR_MUL '*'
#define OPERATOR_DIV '/'
#define OPERATOR_MOD '%'
#define OPERATOR_MEM '.'
#define OPERATOR_NOT '!'


enum token_types {
    /* types */
    token_integer,          /* 123         0*/
    token_float,            /* 0.43        1*/
    token_string,           /* "aa"        2*/
    token_list,             /* {1, 3}      3*/
    token_hashmap,          /* {"a": 4}    4*/
    token_nil,              /* nil         5*/

    /* brackets */
    token_open_bracket,     /* (           6*/
    token_close_bracket,    /* )           7*/

    /* operators */
    token_eql,              /* =           8*/
    token_add,              /* +           9*/
    token_sub,              /* -          10*/
    token_mul,              /* *          11*/
    token_div,              /* /          12*/
    token_mod,              /* %          13*/
    token_l,                /* <          14*/
    token_g,                /* >          15*/


    token_noteql,           /* !=         16*/
    token_eqleql,           /* ==         17*/
    token_addeql,           /* +=         18*/
    token_subeql,           /* -=         19*/
    token_muleql,           /* *=         20*/
    token_diveql,           /* /=         21*/
    token_modeql,           /* %=         22*/
    token_le,               /* <=         23*/
    token_ge,               /* >=         24*/


    token_mem,              /* .          25*/
    token_range,            /* ..         26*/
    token_call,             /* (a, 14)    27*/

    /* identifier */
    token_identifier,       /* aboba      28*/

    /* reserved words */
    token_or,               /* or         29*/
    token_and,              /* and        30*/
    token_not,              /* not        31*/
    token_return,           /* return     32*/
    token_break,            /* break      33*/
    token_continue,         /* continue   34*/
    token_raise,            /* raise      35*/
    token_true,             /* true       36*/
    token_false,            /* false      37*/

    /* other */
    token_other,            /* ?          38*/
};


struct token
{
    enum token_types type;
    char *str;
};


struct nodes *lexer(char *expression);


#endif
