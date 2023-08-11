#include <stdlib.h>
#include "hashmap.h"

static int key_length(char *key)
{
    char *t;
    for(t = key; *t; t++){}
    return t - key;
}

static int pearson_hash(const char *key, int len) 
{
    int i, j, sum;
    unsigned char h;

    static const unsigned char T[256] = {
    98,  6, 85,150, 36, 23,112,164,135,207,169,  5, 26, 64,165,219,  /* 1*/
    61, 20, 68, 89,130, 63, 52,102, 24,229,132,245, 80,216,195,115,  /* 2*/
    90,168,156,203,177,120,  2,190,188,  7,100,185,174,243,162, 10,  /* 3*/
    123,251, 67,250,161,  0,107, 97,241,111,181, 82,249, 33, 69, 55, /* 4*/
    237, 18,253,225,  8,208,172,244,255,126,101, 79,145,235,228,121, /* 5*/
    59,153, 29,  9,213,167, 84, 93, 30, 46, 94, 75,151,114, 73,222,  /* 6*/
    197, 96,210, 45, 16,227,248,202, 51,152,252,125, 81,206,215,186, /* 7*/
    39,158,178,187,131,136,  1, 49, 50, 17,141, 91, 47,129, 60, 99,  /* 8*/
    154, 35, 86,171,105, 34, 38,200,147, 58, 77,118,173,246, 76,254, /* 9*/
    133,232,196,144,198,124, 53,  4,108, 74,223,234,134,230,157,139, /*10*/
    189,205,199,128,176, 19,211,236,127,192,231, 70,233, 88,146, 44, /*11*/
    183,201, 22, 83, 13,214,116,109,159, 32, 95,226,140,220, 57, 12, /*12*/
    221, 31,209,182,143, 92,149,184,148, 62,113, 65, 37, 27,106,166, /*13*/
    3, 14,204, 72, 21, 41, 56, 66, 28,193, 40,217, 25, 54,179,117,   /*14*/
    238, 87,240,155,180,170,242,212,191,163, 78,218,137,194,175,110, /*15*/
    43,119,224, 71,122,142, 42,160,104, 48,247,103, 15, 11,138,239,  /*16*/
    };

    for (sum = 0, j = 0; j < 8; ++j) {
        h = T[(key[0] + j) % 256];
        for (i = 1; i < len; ++i) {
            h = T[h ^ key[i]];
        }
        sum += h << (7 - j);
    }
    return sum;
}

static int get_index(struct hashmap *hm, const char *key, int len)
{
    return pearson_hash(key, len) % (hm->factor * HASHMAP_SIZE);
}

static struct pair *pair_new(char *key, void *val)
{
    struct pair *p;
    p = malloc(sizeof(struct pair));
    p->key = key;
    p->val = val;
    return p;
}

static struct hashmap_list *hashmap_list_new(struct pair *p)
{
    struct hashmap_list *hl;
    hl = malloc(sizeof(struct hashmap_list));
    hl->data = p;
    hl->next = NULL;
    return hl;
}


static int hashmap_list_add(struct hashmap_list* l, char *key, void *val)
{
    struct hashmap_list **lp;

    if(!l){
        l = hashmap_list_new(pair_new(key, val));;
        return 1;
    }

    lp = &l;
    while(*lp){
        if((*lp)->data->key == key){
            (*lp)->data->val = val;
            return 0;
        }
        if(!(*lp)->next){
            break;
        }
        lp = &(*lp)->next;
    }

    (*lp)->next = hashmap_list_new(pair_new(key, val));
    return 1;
}

struct hashmap *hashmap_new()
{
    struct hashmap *hm;
    struct hashmap_list **table;
    int i;

    hm = malloc(sizeof(struct hashmap));
    table = malloc(sizeof(struct hashmap_list **));
    *table = malloc(sizeof(struct hashmap_list *) * HASHMAP_SIZE);
    hm->table = table;
    hm->factor = 1;
    hm->elements = 0;

    for(i = 0; i < HASHMAP_SIZE; i++){
        *(table + i) = NULL;
    }

    return hm;
}

void hashmap_set(struct hashmap *hm, char *key, void *val)
{
    struct hashmap_list *lst;
    lst = (*hm->table) + get_index(hm, key, key_length(key));
    hm->elements += hashmap_list_add(lst, key, val);
}

void* hashmap_get(struct hashmap *hm, char *key)
{
    struct hashmap_list *lst;
    lst = (*hm->table) + get_index(hm, key, key_length(key));
    while(lst){
        if(lst->data->key == key)
            return lst->data->val;
        lst = lst->next;
    }
    return NULL;
}

static void hashmap_resize(struct hashmap *hm)
{
    double coefficient;
    struct hashmap_list **old_table, **new_table;
    coefficient = (double)hm->elements / (double)(hm->factor * HASHMAP_SIZE);
    if(coefficient > HASHMAP_RESIZE_COEF){

        hm->factor++;

        new_table = malloc(sizeof(struct hashmap_list **));
        *new_table = malloc(sizeof(struct hashmap_list *) * hm->factor * HASHMAP_SIZE);

        old_table = hm->table;

        for(i = 0; i < hm->factor * HASHMAP_SIZE; i++){
            *(new_table + i) = NULL;
        }
        /* copy elements from old table to new */


    }
}











