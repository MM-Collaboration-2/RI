#include <stdlib.h>
#include "chars.h"


static char *chars_new(int length)
{
    char *chars;
    chars = malloc(sizeof(char) * (length + 1));
    *(chars + length) = '\0';
    return chars;
}

static char *chars_cat(char *dest, const char *src)
{
    char *tmp;
    tmp = dest;
    while(*tmp)
        tmp++;
    while(*src)
        *tmp++ = *src++;
    *tmp = '\0';
    return dest;
}

static char *chars_ncat(char *dest, const char *src, int n)
{
    char *tmp;
    tmp = dest;
    while(*tmp)
        tmp++;
    while(n--)
        *tmp++ = *src++;
    return dest;
}





int chars_length(const char *chars)
{
    const char *t;
    for(t = chars; *t; t++){}
    return t - chars;
}

void chars_set(char *chars, char ch, int length)
{
    int i;
    for(i = 0; i < length; i++){
        *(chars + i) = ch;
    }
}

char *chars_from(const char *chars)
{
    char *new_chars, *tmp;
    new_chars = chars_new(chars_length(chars));
    tmp = new_chars;
    while(*chars)
        *tmp++ = *chars++;
    
    return new_chars;
}

char *chars_lfind(char *chars1, const char *chars2)
{
    const char *tmp;

    if(chars_length(chars2) > chars_length(chars1))
        return NULL;

    tmp = chars2;

    while(*chars1){
        if(*chars1 == *tmp){
            while(*chars1 == *tmp){
                if(!*(tmp + 1)){
                    return chars1 - (tmp - chars2);
                }
                chars1++;
                tmp++;
            }
            tmp = chars2;
        }
        chars1++;
    }
    return NULL;
}

char *chars_rfind(char *chars1, const char *chars2)
{
    const char *tmp;

    if(chars_length(chars2) > chars_length(chars1))
        return NULL;

    chars1 = chars1 + chars_length(chars1) - 1;
    tmp = chars2 + chars_length(chars2) - 1;

    while(*chars1){
        if(*chars1 == *tmp){
            while(*chars1 == *tmp){
                if(!*(tmp - 1)){
                    return chars1;
                }
                chars1--;
                tmp--;
            }
            tmp = chars2;
        }
        chars1--;
    }
    return NULL;
}

char *chars_find(char *chars1, const char *chars2)
{
    return chars_lfind(chars1, chars2);
}

int chars_count(const char *chars1, const char *chars2)
{
    int count;
    const char *tmp;

    count = 0;
    tmp = chars2;

    while(*chars1){
        if(*chars1 == *tmp){
            while(*chars1 == *tmp){
                if(!*(tmp + 1)){
                    count++;
                    break;
                }
                chars1++;
                tmp++;
            }
            tmp = chars2;
        }
        chars1++;
    }
    return count;
}

int chars_startswith(const char *chars1, const char *chars2)
{
    while(*chars2){
        if(*chars1 != *chars2){
            return 0;
        }
        chars1++;
        chars2++;
    }
    return 1;
}

int chars_endswith(const char *chars1, const char *chars2)
{
    chars1 = chars1 + chars_length(chars1) - 1;
    chars2 = chars2 + chars_length(chars2) - 1;

    while(*chars2){
        if(*chars1 != *chars2){
            return 0;
        }
        chars1--;
        chars2--;
    }
    return 1;
}


int chars_is_integer(const char *chars)
{
    char c;
    while((c = *chars)){
        if(c < '0' || c > '9')
            return 0;
        chars++;
    }
    return 1;
}

int chars_is_float(const char *chars)
{
    char c;
    int point_flag = 0;
    while((c = *chars)){
        if((c < '0' || c > '9') && c != '.'){
            return 0;
        }
        if(c == '.'){
            if(point_flag || !*(chars + 1)){
                return 0;
            }
            point_flag = 1;
        }
        chars++;
    }
    return 1;
}


char* chars_replace(char* chars, const char* oldc, const char* newc)
{

    int old_len, gap, total_len;
    char *tmp, *buf, *next;

    old_len = chars_length(oldc);
    gap = chars_length(newc) - old_len;

    total_len = chars_length(chars) + chars_count(chars, oldc) * gap;

    buf = chars_new(total_len);

    tmp = chars;
    while ((next = chars_find(tmp, oldc))) {
        chars_ncat(buf, tmp, next - tmp);
        chars_cat(buf, newc);
        tmp = next + old_len;
    }
    chars_cat(buf, tmp);

    return buf;
}

char *chars_reverse(const char *chars)
{
    char *buf;
    int length;

    length = chars_length(chars);
    buf = chars_new(length);
    buf = buf + length;

    while(*chars)
        *--buf = *chars++;

    return buf;
}

char *chars_add(const char *chars1, const char *chars2)
{
    char *buf;
    buf = chars_new(chars_length(chars1) + chars_length(chars2));
    buf = chars_cat(buf, chars1);
    buf = chars_cat(buf, chars2);
    return buf;
}

char *chars_slice(const char *chars, int start, int end)
{
    char *tmp, *buf;
    buf = chars_new(end - start);
    tmp = buf;
    chars = chars + start;
    while(end - start++){
        *tmp++ = *chars++;
    }
    return buf;
}
