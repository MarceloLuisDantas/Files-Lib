#include <stdlib.h>
#include <stdio.h>

#define TRUE 1
#define FALSE 0

typedef struct String {
    char *array;
    size_t len;
} String;

/*  Returns the pointer to a empty String with size of len
    Will returns a NULL Array if len = 0
*/
String *newString(size_t len) {
    String *s = (String *)malloc(sizeof(String));
    if (len != 0)
        s->array = (char *)malloc(sizeof(char) * len);
    else 
        s->array = NULL;
    s->len = len;
    return s;
}

typedef struct ArrayString {
    String **array;
    size_t len;
    size_t capacity;
} ArrayString;

/*  Create a new Array of Strings.
    if Capacity = 0, a NULL pointer is returned
*/
ArrayString *newArrayString(size_t capacity) {
    if (capacity == 0)
        return NULL;

    ArrayString *as = (ArrayString *)malloc(sizeof(ArrayString));
    as->array = (String **)malloc(sizeof(String *) * capacity);
    as->capacity = capacity;
    as->len = 0;

    return as;
}

size_t count(String *s, char item) {
    size_t total = 0;
    for (int i = 0; i < s->len; i++)
        if (s->array[i] == item)
            total += 1;
    return total;
}

// strlen from <strings.h> equivalent 
size_t cstrlen(char *s) {
    int i = 0;
    while (s[i] != '\0')
        i += 1;
    return i; 
}

// Checks if a range [form, to] is inside of a String's len 
int isInRange(String *s, int from, int to) {
    if (from > to) 
        return FALSE;

    if (from >= s->len || to >= s->len) 
        return FALSE;

    return TRUE;
}

/*  Receives a default C String ended with "\0", and convert to 
    a struct String. 
 */
String *CStringToString(char *src) {
    size_t len = cstrlen(src);
    String *ns = newString(len);
    for (int i = 0; i < len; i++)
        ns->array[i] = src[i];
    return ns; 
}

// Compare 2 diferent Strings
int StringCmp(String *s1, String *s2) {
    if (s1->len != s2->len)
        return FALSE;

    for (int i = 0; i < s1->len; i++)
        if (s1->array[i] != s2->array[i])
            return FALSE;
    
    return TRUE;
}

/*  Returns a new String, with the specific slice from the passed String 
    ['M', 'a', 'r', 'i', 's', 'a'], from 2 to 4 returns ['r', 'i', 's']
    From/To are bouth from 0 to Len.
    If the range is out of bounds, a NULL string will be returned.
*/
String *getSlice(String *s, size_t from, size_t to) {
    if (isInRange(s, from, to) == FALSE)
        return NULL;
  
    size_t len_n_string = to - from + 1;
    String *ns = newString(len_n_string);
    for (int i = 0; i < len_n_string; i++)
        ns->array[i] = s->array[i + from];
    
    return ns;
}

void trim_left(String **s) {
    if ((*s)->len == 0) 
        return;

    if ((*s)->array[0] != ' ')
        return;

    int remove = 0;
    for (int i = 0; i < (*s)->len; i++) {
        if ((*s)->array[i] != ' ')
            break;
        remove += 1;
    }

    if (remove == (*s)->len) {
        free((*s)->array);
        (*s)->array = NULL;
        (*s)->len = 0;
        return;
    }

    size_t newLen = (*s)->len - remove;
    String *ns = newString(newLen);
    for (int i = 0; i < ns->len; i++)
        ns->array[i] = (*s)->array[i + remove];
    
    free((*s)->array);
    free((*s));
    (*s) = ns;
}

void trim_right(String **s) {
    if ((*s)->len == 0) 
        return;

    if ((*s)->array[(*s)->len - 1] != ' ')
        return;

    int remove = 0;
    for (int i = (*s)->len - 1; i >= 0; i--) {
        if ((*s)->array[i] != ' ')
            break;
        remove += 1;
    }

    if (remove == (*s)->len) {
        free((*s)->array);
        (*s)->array = NULL;
        (*s)->len = 0;
        return;
    }

    size_t newLen = (*s)->len - remove;
    String *ns = newString(newLen);
    for (int i = 0; i < ns->len; i++)
        ns->array[i] = (*s)->array[i];
    
    free((*s)->array);
    free((*s));
    (*s) = ns;
}

/*  Remove all extra spaces in the start/end of a String 
    if the string is only spaces ["     "], a null pointer
    will be alloced to String.array;
*/
void trim(String **s) {
    trim_left(s);
    trim_right(s);
}

// Pushs the value in the Array, returns -1 if full
int ASPush(ArrayString *as, String *string) {
    if (as->len == as->capacity)
        return -1;

    as->array[as->len] = string;
    as->len += 1;

    return 1;
}

// Converts all Strings in a Array of Strings into a single String 
String *arrayToString(ArrayString *as) {
    if (as->len == 0)
        return NULL;

    size_t total_len = 0;
    for (int i = 0; i < as->len; i++) 
        total_len += as->array[i]->len + 1; // +1 for the space
    total_len -= 1; 


    String *s = newString(total_len);
    int i = 0;
    for (int j = 0; j < as->len; j++) {
        for (int k = 0; k < as->array[j]->len; k++) {
            s->array[i] = as->array[j]->array[k];
            i += 1;
        }
        s->array[i] = ' ';
        i += 1;
    }

    return s;
}

int count_words(String *s) {
    if (s->len == 0) 
        return 0;

    int words = 0;
    int spaces = 0;
    for (int i = 0; i < s->len; i++) {
        if (s->array[i] == ' ' && spaces == 0) {
            words += 1;
            spaces = 1;
        } else if (s->array[i] != ' ')
            spaces = 0;
    }
    words += 1;

    return words;
}

/*  Remove all extra spaces of a String 
    if the string is only spaces ["     "], a null pointer
    will be alloced to String.array;
*/
void remove_white_space(String **s) {
    trim(s);
    if ((*s)->len == 0)
        return;

    int words = count_words(*s);
    ArrayString *as = newArrayString(words);
    
    int from = 0;
    int spaces = 0;
    for (int i = 0; i < (*s)->len; i++) {
        if ((*s)->array[i] == ' ' && spaces == 0) {
            spaces = 1;
            ASPush(as, getSlice((*s), from, i - 1));
        } else if ((*s)->array[i] != ' ' && spaces == 1) {
            from = i;
            spaces = 0;
        }
    }
    ASPush(as, getSlice((*s), from, (*s)->len - 1));

    free((*s)->array);
    free((*s));
    (*s) = arrayToString(as);
}

/*  Splits a String in a Array of Strings, all the extra
    spaces in the string will be removed before split.
    Empty strings will return NULL.
*/ 
ArrayString *split(String *s, const char spliter) {
    remove_white_space(&s);
    if (s->len == 0) 
        return NULL;

    int words = count_words(s);
    ArrayString *as = newArrayString(words);
    
    int from = 0;
    int spaces = 0;
    for (int i = 0; i < s->len; i++) {
        if (s->array[i] == spliter && spaces == 0) {
            spaces = 1;
            ASPush(as, getSlice(s, from, i - 1));
        } else if (s->array[i] != spliter && spaces == 1) {
            from = i;
            spaces = 0;
        }
    }
    ASPush(as, getSlice(s, from, s->len - 1));

    return as;
}




