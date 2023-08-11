#include <stdlib.h>
#include <stdio.h>
#include "list.h"
#include "object.h"


/* List cant be a NULL pointer */


static void list_node_free(struct list_node *ln)
{
    object_free(ln->obj);
    free(ln);
}

static struct list_node *list_node_new(struct object *obj)
{
    struct list_node *n;
    n = malloc(sizeof(struct list_node));
    n->obj = obj;
    n->next = NULL;
    n->prev = NULL;
    return n;
}


int list_length(struct list *lst)
{
    return lst->length;
}

void list_push_back(struct list *lst, struct object *obj)
{
    struct list_node *n;
    n = list_node_new(obj);

    if(lst->length == 0){
        lst->head = n;
        lst->tail = n;
    }
    else{
        lst->tail->next = n;
        n->prev = lst->tail;
        lst->tail = n;
    }
    lst->length++;
}

void list_push_front(struct list *lst, struct object *obj)
{
    struct list_node *n;
    n = list_node_new(obj);

    if(lst->length == 0){
        lst->head = n;
        lst->tail = n;
    }
    else{
        lst->head->prev = n;
        n->next = lst->head;
        lst->head = n;
    }
    lst->length++;
}

void list_insert(struct list *lst, int index, struct object *obj)
{
    struct list_node *n, *tmp;

    if(index < 0 || index > lst->length){
        fprintf(stderr, "List index out of range.\n");
        return;
    }

    if(index == 0){
        list_push_front(lst, obj);
        return;
    }
    else if(index == lst->length){
        list_push_back(lst, obj);
        return;
    }

    n = list_node_new(obj);
    tmp = lst->head;

    for(; index > 0; index--, tmp = tmp->next){}

    n->next = tmp;
    n->prev = tmp->prev;
    tmp->prev->next = n;
    tmp->prev = n;

    lst->length++;
}

void list_remove_back(struct list *lst)
{
    struct list_node *tmp;

    if(lst->length == 0){
        fprintf(stderr, "Remove from empty list.\n");
        return;
    }
    tmp = lst->tail;
    if(lst->length == 1){
        lst->tail = NULL;
        lst->head = NULL;
    }
    else{
        lst->tail = lst->tail->prev;
        lst->tail->next = NULL;
    }
    list_node_free(tmp);
    lst->length--;
}

void list_remove_front(struct list *lst)
{
    struct list_node *tmp;

    if(lst->length == 0){
        fprintf(stderr, "Remove from empty list.\n");
        return;
    }
    tmp = lst->head;
    if(lst->length == 1){
        lst->tail = NULL;
        lst->head = NULL;
    }
    else{
        lst->head = lst->head->next;
        lst->head->prev = NULL;
    }
    list_node_free(tmp);
    lst->length--;
}

void list_remove(struct list *lst, int index)
{
    struct list_node *tmp;

    if(index < 0 || index > lst->length - 1){
        fprintf(stderr, "List index out of range.\n");
        return;
    }

    if(index == 0){
        list_remove_front(lst);
        return;
    }
    else if(index == lst->length - 1){
        list_remove_back(lst);
        return;
    }

    tmp = lst->head;

    for(; index > 0; index--, tmp = tmp->next){}

    tmp->prev->next = tmp->next;
    tmp->next->prev = tmp->prev;

    list_node_free(tmp);
    lst->length--;
}

struct object *list_get_back(struct list *lst)
{
    if(!lst->tail){
        fprintf(stderr, "Get from empty list.\n");
        return NULL;
    }
    return lst->tail->obj;
}

struct object *list_get_front(struct list *lst)
{
    if(!lst->head){
        fprintf(stderr, "Get from empty list.\n");
        return NULL;
    }
    return lst->head->obj;
}

struct object *list_get(struct list *lst, int index)
{
    struct list_node *tmp;

    if(index < 0 || index > lst->length - 1){
        fprintf(stderr, "List index out of range.\n");
        return NULL;
    }

    if(index == 0){
        return list_get_front(lst);
    }
    else if(index == lst->length - 1){
        return list_get_back(lst);
    }

    tmp = lst->head;
    for(; index > 0; index--, tmp = tmp->next){}

    return tmp->obj;
}

struct object *list_pop(struct list *lst)
{
    struct object *obj;
    if(lst->length == 0){
        fprintf(stderr, "Pop from empty list.\n");
        return NULL;
    }
    obj = list_get_back(lst);
    list_remove_back(lst);
    return obj;
}

void list_set_back(struct list *lst, struct object *obj)
{
    if(!lst->tail){
        fprintf(stderr, "Set to empty list.\n");
        return;
    }
    lst->tail->obj = obj;
}

void list_set_front(struct list *lst, struct object *obj)
{
    if(!lst->head){
        fprintf(stderr, "Set to empty list.\n");
        return;
    }
    lst->head->obj = obj;
}

void list_set(struct list *lst, int index, struct object *obj)
{
    struct list_node *tmp;

    if(index < 0 || index > lst->length - 1){
        fprintf(stderr, "List index out of range.\n");
        return;
    }

    if(index == 0){
        return list_set_front(lst, obj);
    }
    else if(index == lst->length - 1){
        return list_set_back(lst, obj);
    }

    tmp = lst->head;
    for(; index > 0; index--, tmp = tmp->next){}

    tmp->obj = obj;
}

/* Remember to check if *(struct object *) is NULL */
void list_iter(struct list *lst, struct object *(*func)(struct object *))
{
    struct list_node *tmp;
    struct object *obj;
    tmp = lst->head;
    while(tmp){
        obj = func(tmp->obj);
        tmp->obj = obj;
        tmp = tmp->next;
    }
}

void list_delete(struct list *lst)
{
    struct list_node *tmp;
    while(lst->head){
        tmp = lst->head;
        lst->head = lst->head->next;
        list_node_free(tmp);
    }
    lst->tail = NULL;
    lst->length = 0;
}


struct list *list_new()
{
    struct list* new_list;
    new_list = malloc(sizeof(struct list));
    new_list->head = NULL;
    new_list->tail = NULL;
    new_list->length = 0;
    return new_list;
}


