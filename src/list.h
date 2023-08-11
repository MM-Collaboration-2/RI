#ifndef LIST_H_SENTRY
#define LIST_H_SENTRY



struct list_node
{
    struct object *obj;
    struct list_node *next;
    struct list_node *prev;
};

struct list
{
    int length;
    struct list_node *head;
    struct list_node *tail;
};

int list_length(struct list *lst);

void list_push_back(struct list *lst, struct object *obj);

void list_push_front(struct list *lst, struct object *obj);

void list_insert(struct list *lst, int index, struct object *obj);

void list_remove_back(struct list *lst);

void list_remove_front(struct list *lst);

void list_remove(struct list *lst, int index);

struct object *list_get_back(struct list *lst);

struct object *list_get_front(struct list *lst);

struct object *list_get(struct list *lst, int index);

struct object *list_pop(struct list *lst);

void list_set_back(struct list *lst, struct object *obj);

void list_set_front(struct list *lst, struct object *obj);

void list_set(struct list *lst, int index, struct object *obj);

void list_iter(struct list *lst, struct object *(*func)(struct object *));

void list_delete(struct list *lst);

struct list *list_new();

#endif
