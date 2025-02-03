#include <stdlib.h>
#include <stdint.h>
#include "Strings.h"

typedef struct Node {
    struct Node *next;
    String *value;
} Node;

Node *newNode(String *s) {
    Node *n = malloc(sizeof(Node));
    n->next = NULL;
    n->value = s;
    return n;
}

typedef struct LinkedList {
    Node *start;
    uint32_t len;
} LinkedList;


/*  Allocs and return a new Linked List with len = 0 and
    the start node = NULL
*/
LinkedList *newLinkedList() { 
    LinkedList *ll = malloc(sizeof(LinkedList));
    ll->start = NULL;
    ll->len = 0;
    return ll;
}

/*  Creates a new node and put in the end of the list.
    Empty Strings will be ignored, and 1 will be returned;
*/
int add(LinkedList *list, char *value) { 
    String *s = CStringToString(value);
    trim(&s);
    if (s->array == NULL) 
        return 1;
    
    Node *n = newNode(s);
    if (list->len == 0) {
        list->start = n;
        list->len = 1;
        return 0;
    }

    Node *sup = list->start;
    while (sup->next != NULL)
        sup = sup->next;
    sup->next = n;
    list->len += 1;
    return 0;    
}

/*  Returns the pointer String saved in the index.
    Returns NULL if out of bounds;
*/
String *getValue(LinkedList *l, uint32_t index) {
    if (index < 0 || index >= l->len)
        return NULL;

    Node *sup = l->start;
    while (index != 0) {
        sup = sup->next;;
        index -= 1;
    }

    return sup->value;
}

/*  Returns the pointer to a copy of the String saved in the index.
    Returns NULL if out of bounds;
*/
String *getValueCopy(LinkedList *l, uint32_t index) {
    if (index < 0 || index >= l->len)
        return NULL;

    Node *sup = l->start;
    while (index != 0) {
        sup = sup->next;;
        index -= 1;
    }

    String *copy = malloc(sizeof(String));
    *copy = *sup->value;
    return copy;
}


/*  Frees the String in the index, and saves the new String
    Returns 1 if the index is out of bounds
*/
int set(LinkedList *l, char *value, uint32_t index) { 
    if (index < 0 || index >= l->len)
        return 1;

    Node *sup = l->start;
    while (index != 0) {
        sup = sup->next;
        index -= 1;
    }

    String *ns = CStringToString(value);
    free(sup->value->array);
    free(sup->value);
    sup->value = ns;

    return 0;
}

/*  Removes the index element 
    if the index is out of bounds, will returns 1
*/
int delete(LinkedList *l, uint32_t index) { 
    if (index < 0 || index >= l->len)
        return 1;

    Node *sup = l->start;
    if (index == 0) {
        l->start = sup->next;
        free(sup->value);
        free(sup);
    } else {
        while (index > 1) {
            sup = sup->next;
            index -= 1;
        }

        Node *sup2 = sup->next;
        sup->next = sup2->next;
        free(sup2->value);
        free(sup2);
    }

    l->len -= 1;
    return 0;
}


/*  Inserts a new node.
    If the index is is out of bounds (> len) 1 will be returned
*/
int insert(LinkedList *l, char *value, uint32_t index) { 
    if (index < 0 || index > l->len)
        return 1;

    Node *nn = newNode(CStringToString(value));
    if (index == 0) {
        nn->next = l->start;
        l->start = nn;
    } else {
        Node *sup = l->start;
        while (index > 1) {
            sup = sup->next;
            index -= 1;
        }

        nn->next = sup->next;    
        sup->next = nn;
    }

    l->len += 1;
    return 0;
}

/*  Creates a ArrayString from all the values in the list
    All the values are copys of the originals, not references
    If the list is empty a NULL pointer will be returned
*/
ArrayString *toArray(LinkedList *l) { 
    if (l->len == 0)
        return NULL;

    ArrayString *as = newArrayString(l->len);
    for (int i = 0; i < l->len; i++)
        ASPush(as, getValueCopy(l, i));

    return as;
}