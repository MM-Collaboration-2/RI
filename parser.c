#include <stdlib.h>
#include <stdio.h>
#include "nodes.h"
#include "chars.h"
#include "associations.h"
#include "parser.h"


struct nodes *parser(struct nodes *infix_list)
{
    struct nodes *postfix_list;
    struct nodes *op_stack;
    static struct associations *precisions;
    static int setted = 0;

    if(!setted){
        precisions = associations_new(60);

        associations_set(precisions, "!", );
        associations_set(precisions, "=", );

        associations_set(precisions, "(", );
        associations_set(precisions, ")", );

        associations_set(precisions, "+", );
        associations_set(precisions, "-", );
        associations_set(precisions, "/", );
        associations_set(precisions, "%", );
        associations_set(precisions, "/", );
        associations_set(precisions, "<", );
        associations_set(precisions, ">", );
        associations_set(precisions, ".", );

        associations_set(precisions, "!=", );
        associations_set(precisions, "==", );

        associations_set(precisions, "+=", );
        associations_set(precisions, "-=", );
        associations_set(precisions, "/=", );
        associations_set(precisions, "%=", );
        associations_set(precisions, "/=", );
        associations_set(precisions, "<=", );
        associations_set(precisions, ">=", );
        associations_set(precisions, "..", );

        associations_set(precisions, "and", );
        associations_set(precisions, "or", );
        associations_set(precisions, "not", );
        associations_set(precisions, "return", );


        setted = 1;
    }


}
