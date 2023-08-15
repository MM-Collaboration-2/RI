#ifndef ASSOCIATIONS_H_SENTRY
#define ASSOCIATIONS_H_SENTRY

#define ASSOCIATIONS_MINIMAL_SIZE 20
#define ASSOCIATIONS_RESIZE_COEF 0.6


struct association
{
    char *key;
    void *val;
};

struct associations
{
    struct nodes *table;
    int elements;
};

int associations_length(struct associations *as);

struct associations *associations_new(int size);

void associations_set(struct associations *as, char *key, void *val);

void *associations_get(struct associations *as, char *key);
;

void associations_remove(
        struct associations *as, 
        char *key);
 
void associations_iter(
        struct associations *as, 
        void *(*valfunc)(void *));

struct nodes *associations_keys(struct associations *as);

#endif
