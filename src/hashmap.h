#ifndef HASHMAP_H_SENTRY
#define HASHMAP_H_SENTRY

#define HASHMAP_SIZE 40
#define HASHMAP_RESIZE_COEF 0.6

struct pair
{
    char *key;
    void *val;
};

struct hashmap_list
{
    struct pair *data;
    struct hashmap_list *next;
};

struct hashmap
{
    struct hashmap_list **table;
    int factor;
    int elements;
};

void hashmap_set();

void* hashmap_get();

void hashmap_iter(struct hashmap *hm,
        char *(*keyfunc)(char *),
        void *(*valfunc)(void *));

#endif
