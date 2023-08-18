#include <stdlib.h>
#include <stdio.h>
#include "nodes.h"
#include "chars.h"
#include "associations.h"
#include "lexer.h"


static int is_digit(char ch)
{
    if((ch >= '0' && ch <= '9'))
        return 1;
    return 0;
}


static int is_identifier(char ch)
{
    if( (ch >= 'a' && ch <= 'z') ||
        (ch >= 'A' && ch <= 'Z') ||
        (ch == '_') )
        return 1;
    return 0;
}


static int is_operator(char ch)
{
    char *operators, *tmp;
    int f;
    
    f = 0;
    operators = chars_from("=+-*/%<>!.");
    tmp = operators;
    while(*tmp){
        if(*tmp == ch)
            f = 1;
        tmp++;
    }
    free(operators);
    return f;
}

struct token *token_new()
{
    struct token *t;
    t = malloc(sizeof(struct token));
    return t;
}


struct nodes *lexer(char *expression)
{

    struct nodes *nds;
    struct token *tok;

    char *tmp, *start;

    int string_f, hashmap_f, brackets_f, float_f;

    enum token_types *type;

    static struct associations *as;
    static int setted = 0;

    static enum token_types types_vec[] = {
        token_not,              /* !\not      0 */
        token_eql,              /* =          1 */
        token_add,              /* +          2 */
        token_sub,              /* -          3 */
        token_mul,              /* *          4 */
        token_div,              /* /          5 */
        token_mod,              /* %          6 */
        token_mem,              /* .          7 */
        token_l,                /* <          8 */
        token_g,                /* >          9 */

        token_noteql,           /* !=         10*/
        token_eqleql,           /* ==         11*/
        token_addeql,           /* +=         12*/
        token_subeql,           /* -=         13*/
        token_muleql,           /* *=         14*/
        token_diveql,           /* /=         15*/
        token_modeql,           /* %=         16*/
        token_range,            /* ..         17*/
        token_le,               /* <=         18*/
        token_ge,               /* >=         19*/

        token_or,               /* or         20*/
        token_and,              /* and        21*/
        token_return,           /* return     22*/
        token_break,            /* break      23*/
        token_continue,         /* continue   24*/
        token_raise,            /* raise      25*/
        token_true,             /* true       26*/
        token_false,            /* false      27*/
    };


    if(!setted){

        as = associations_new(60);

        associations_set(as, "!",        types_vec);
        associations_set(as, "not",      types_vec);
        associations_set(as, "=",        types_vec + 1);
        associations_set(as, "+",        types_vec + 2);
        associations_set(as, "-",        types_vec + 3);
        associations_set(as, "*",        types_vec + 4);
        associations_set(as, "/",        types_vec + 5);
        associations_set(as, "%",        types_vec + 6);
        associations_set(as, ".",        types_vec + 7);
        associations_set(as, "<",        types_vec + 8);
        associations_set(as, ">",        types_vec + 9);

        associations_set(as, "!=",       types_vec + 10);
        associations_set(as, "==",       types_vec + 11);
        associations_set(as, "+=",       types_vec + 12);
        associations_set(as, "-=",       types_vec + 13);
        associations_set(as, "*=",       types_vec + 14);
        associations_set(as, "/=",       types_vec + 15);
        associations_set(as, "%=",       types_vec + 16);
        associations_set(as, "..",       types_vec + 17);
        associations_set(as, "<=",       types_vec + 18);
        associations_set(as, ">=",       types_vec + 19);

        associations_set(as, "or",       types_vec + 20);
        associations_set(as, "and",      types_vec + 21);
        associations_set(as, "return",   types_vec + 22);
        associations_set(as, "break",    types_vec + 23);
        associations_set(as, "continue", types_vec + 24);
        associations_set(as, "raise",    types_vec + 25);
        associations_set(as, "true",     types_vec + 26);
        associations_set(as, "false",    types_vec + 27);

        setted = 1;
    }


    nds = nodes_new();
    string_f = 0;
    hashmap_f = 0;
    float_f = 0;

    tmp = expression;
    while(*tmp){
        while(*tmp && *tmp == ' '){
            tmp++;
            continue;
        }

        start = tmp;
        /* String */
        if(*tmp == '"'){
            string_f = 1;
            while(string_f != 0){
                tmp++;
                if(!tmp)
                    return NULL;
                if(*tmp == '"' && *(tmp - 1) != '\\'){
                    string_f = 0;
                }
            }
            tok = token_new();
            tok->str = chars_slice(start, 0, tmp - start + 1);
            tok->type = token_string;
            nodes_push_back(nds, tok);
            tmp++;
            continue;
        }
        /* Identifiers and reserved words */
        else if(is_identifier(*tmp)){
            while(*tmp && (is_identifier(*tmp) || is_digit(*tmp))){
                tmp++;
            }
            tok = token_new();
            tok->str = chars_slice(start, 0, tmp - start);
            type = (enum token_types *)associations_get(as,
                    tok->str);
            if(!type)
                tok->type = token_identifier;
            else
                tok->type = *type;
            nodes_push_back(nds, tok);
            continue;
        }
        /* Container */
        else if(*tmp == '{'){
            brackets_f = 1;
            hashmap_f = 0;
            string_f = 0;
            while(brackets_f != 0){
                tmp++;
                if(!tmp)
                    return NULL;
                if(*tmp == '"' && *(tmp - 1) != '\\'){
                    string_f++;
                    string_f /= 2;
                }
                else if(*tmp == '{' && !string_f){
                    brackets_f++;
                }
                else if(*tmp == '}' && !string_f){
                    brackets_f--;
                }
                if(*tmp == ':' && brackets_f == 1){
                    hashmap_f = 1;
                }
            }
            tok = token_new();
            tok->str = chars_slice(start, 0, tmp - start + 1);
            tok->type = hashmap_f ? token_hashmap : token_list;
            nodes_push_back(nds, tok);
            tmp++;
            continue;
        }
        /* Operator */
        else if(is_operator(*tmp)){
            while(is_operator(*tmp)){
                tmp++;
            }
            tok = token_new();
            tok->str = chars_slice(start, 0, tmp - start);
            type = associations_get(as, tok->str);


            if(type){
                tok->type = *type;
            }
            else
                tok->type = token_other;
            
            nodes_push_back(nds, tok);
            continue;
        }
        /* Open bracket and call */
        else if(*tmp == '('){
            tok = (struct token *)nodes_get_back(nds);
            if(tok){
                if(tok->type == token_call ||
                        tok->type == token_identifier ||
                        tok->type == token_close_bracket){
                    brackets_f = 1;
                    while(brackets_f != 0){
                        tmp++;
                        if(!tmp)
                            return NULL;
                        if(*tmp == '"' && *(tmp - 1) != '\\'){
                            string_f++;
                            string_f /= 2;
                        }
                        else if(*tmp == '(' && !string_f)
                            brackets_f++;
                        else if(*tmp == ')' && !string_f)
                            brackets_f--;
                    }
                    tok = token_new();
                    tok->type = token_call;
                    tok->str = chars_slice(start, 0,
                            tmp - start + 1);
                    nodes_push_back(nds, tok);
                }
                else{
                    tok = token_new();
                    tok->type = token_open_bracket;
                    tok->str = chars_slice(start, 0, 1);
                    nodes_push_back(nds, tok);
                }
            }
            else{
                tok = token_new();
                tok->type = token_open_bracket;
                tok->str = chars_slice(start, 0, 1);
                nodes_push_back(nds, tok);
            }
            tmp++;
            continue;
        }
        /* Close bracket */
        else if(*tmp == ')'){
            tok = token_new();
            tok->type = token_close_bracket;
            tok->str = chars_slice(start, 0, 1);
            nodes_push_back(nds, tok);
            tmp++;
            continue;
        }
        /* Integer and float */
        else if(is_digit(*tmp)){
            float_f = 0;
            while(is_digit(*tmp) || *tmp == '.'){
                tmp++;
                if(*tmp == '.')
                    float_f++;
            }
            tok = token_new();
            tok->str = chars_slice(start, 0, tmp - start);
            if(float_f > 1)
                tok->type = token_other;
            else
                tok->type = float_f ? token_float : token_integer;
            nodes_push_back(nds, tok);
            continue;
        }
        else{
            tmp++;
        }
    }
    return nds;
}
