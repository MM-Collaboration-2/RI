#ifndef OBJECT_H_SETRY
#define OBJECT_H_SETRY


enum obj_type
{
    int_type,
    bol_type,
    flt_type,
    str_type,
    lst_type,
    hmp_type,
    nil_type,
    exc_type,
    fun_type,
    cls_type,
    var_type,
};

struct object
{
    enum obj_type;
    void *obj;
};

/*struct var_obj
{
    char *name;
    struct *object object;
};

struct int_obj
{
    long long data;
}

struct bol_obj
{
    unsigned char data;
}

struct flt_obj
{
    long double data;
}

struct str_obj
{
    struct string data;
}

struct lst_obj
{
    struct list data;
}

struct hmp_obj
{
    struct hash_map data;
}

struct nil_obj
{
    void *data
}

struct exc_obj
{
    char data;
}

struct fun_obj
{
    int arg_count;
    char *name;
    char *executable_text;
};

struct cls_obj
{
    char *name;
    struct list *members;
};


struct vm_frame
{
    char *text;
    struct list *local_variables;
    struct list *locals_for_next;
};

struct vm
{
    int length;
    struct list *frames;
    struct list *user_functions;
}*/

#endif
