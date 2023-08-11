#include <stdio.h>
#include "object.h"
#include "list.h"

int main()
{
    struct int_obj *i;
    struct object *o;
    i = int_obj_new(5);
    o = object_new(int_type, i);
    fprintf(stderr, "%lld\n", i->data);
    object_free(o);
    return 0;
}
