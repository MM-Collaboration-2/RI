#include <stdlib.h>
#include "object.h"
#include "list.h"


struct object *object_new(enum obj_type type, void *obj_)
{
    struct object *obj;
    obj = malloc(sizeof(struct object));
    obj->type = type;
    obj->obj = obj_;
    return obj;
}

struct variable *variable_new(char *name, struct object *obj)
{
    struct variable *var;
    var = malloc(sizeof(struct variable));
    var->name = name;
    var->obj = obj;
    return var;
}

struct int_obj *int_obj_new(long long data)
{
    struct int_obj *new_o;
    new_o = malloc(sizeof(*new_o));
    new_o->data = data;
    return new_o;
}

struct bol_obj *bol_obj_new(unsigned char data)
{
    struct bol_obj *new_o;
    new_o = malloc(sizeof(*new_o));
    new_o->data = data;
    return new_o;
}

struct flt_obj *flt_obj_new(long double data)
{
    struct flt_obj *new_o;
    new_o = malloc(sizeof(*new_o));
    new_o->data = data;
    return new_o;
}

struct str_obj *str_obj_new(char *data)
{
    struct str_obj *new_o;
    new_o = malloc(sizeof(*new_o));
    new_o->data = data;
    return new_o;
}

struct lst_obj *lst_obj_new(struct list *data)
{
    struct lst_obj *new_o;
    new_o = malloc(sizeof(*new_o));
    new_o->data = data;
    return new_o;
}

/*struct hmp_obj *hmp_obj_new(struct hashmap *data)
{
    struct hmp_obj *new_o;
    new_o = malloc(sizeof(*new_o));
    new_o->data = data;
    return new_o;
}*/

struct nil_obj *nil_obj_new()
{
    struct nil_obj *new_o;
    new_o = malloc(sizeof(*new_o));
    new_o->data = NULL;
    return new_o;
}

struct exc_obj *exc_obj_new(char *data)
{
    struct exc_obj *new_o;
    new_o = malloc(sizeof(*new_o));
    new_o->data = data;
    return new_o;
}

/*struct fun_obj *fun_obj_new(int argc, char *name, struct block* block)
{
    struct fun_obj *new_o;
    new_o = malloc(sizeof(*new_o));
    new_o->argc = argc;
    new_o->name = name;
    new_o->block = block;
    return new_o;
}*/

struct cls_obj *cls_obj_new(char *name, struct list *members)
{
    struct cls_obj *new_o;
    new_o = malloc(sizeof(*new_o));
    new_o->name = name;
    new_o->members = members;
    return new_o;
}




static void int_obj_free(struct int_obj *obj)
{
    free(obj);
}

static void bol_obj_free(struct bol_obj *obj)
{
    free(obj);
}

static void flt_obj_free(struct flt_obj *obj)
{
    free(obj);
}

static void str_obj_free(struct str_obj *obj)
{
    free(obj->data);
    free(obj);
}

static void lst_obj_free(struct lst_obj *obj)
{
    list_delete(obj->data);
    free(obj);
}

/*static void hmp_obj_free(struct hmp_obj *obj)
{
    hashmap_delete(obj->data);
    free(obj);
}*/

static void nil_obj_free(struct nil_obj *obj)
{
    free(obj->data);
    free(obj);
}

static void exc_obj_free(struct exc_obj *obj)
{
    free(obj->data);
    free(obj);
}

/*static void fun_obj_free(struct fun_obj *obj)
{
    free(obj->name);
    block_delete(obj->block);
    free(obj);
}*/

static void cls_obj_free(struct cls_obj *obj)
{
    free(obj->name);
    list_delete(obj->members);
    free(obj);
}


void object_free(struct object *obj_)
{
    enum obj_type type;
    type = obj_->type;
    switch(type){
        case int_type:
            int_obj_free((struct int_obj *)obj_->obj);
            break;
        case bol_type:
            bol_obj_free((struct bol_obj *)obj_->obj);
            break;
        case flt_type:
            flt_obj_free((struct flt_obj *)obj_->obj);
            break;
        case str_type:
            str_obj_free((struct str_obj *)obj_->obj);
            break;
        case lst_type:
            lst_obj_free((struct lst_obj *)obj_->obj);
            break;
        /*case hmp_type:
            hmp_obj_free((struct hmp_obj *)obj_->obj);
            break;*/
        case nil_type:
            nil_obj_free((struct nil_obj *)obj_->obj);
            break;
        case exc_type:
            exc_obj_free((struct exc_obj *)obj_->obj);
            break;
        /*case fun_type:
            fun_obj_free((struct fun_obj *)obj_->obj);
            break;*/
        case cls_type:
            cls_obj_free((struct cls_obj *)obj_->obj);
            break;
        default:
            break;
    }
}



