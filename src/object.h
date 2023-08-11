#ifndef OBJECT_H_SETRY
#define OBJECT_H_SETRY

struct hashmap;
struct block;


/*void hashmap_delete(struct hashmap *);
void block_delete(struct block *);*/

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
};

struct object
{
    enum obj_type type;
    void *obj;
};

struct variable
{
    char *name;
    struct object *obj;
};

struct int_obj
{
    long long data;
};

struct bol_obj
{
    unsigned char data;
};

struct flt_obj
{
    long double data;
};

struct str_obj
{
    char *data;
};

struct lst_obj
{
    struct list *data;
};

struct hmp_obj
{
    struct hashmap *data;
};

struct nil_obj
{
    void *data;
};

struct exc_obj
{
    char *data;
};

struct fun_obj
{
    int argc;
    char *name;
    struct block *block;
};

struct cls_obj
{
    char *name;
    struct list *members;
};

struct object *object_new(enum obj_type type, void *obj_);

struct variable *variable_new(char *name, struct object *obj);

struct int_obj *int_obj_new(long long data);

struct bol_obj *bol_obj_new(unsigned char data);

struct flt_obj *flt_obj_new(long double data);

struct str_obj *str_obj_new(char *data);

struct lst_obj *lst_obj_new(struct list *data);

struct hmp_obj *hmp_obj_new(struct hashmap *data);

struct nil_obj *nil_obj_new();

struct exc_obj *exc_obj_new(char *data);

struct fun_obj *fun_obj_new(int argc, char *name, struct block* block);

struct cls_obj *cls_obj_new(char *name, struct list *members);

void object_free(struct object *obj_);


#endif
