#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <stdint.h>
#include "Strings.h"

typedef struct Node {
    struct Node *next;
    String *value;
} Node;

typedef struct LinkedList {
    Node *start;
    uint32_t len;
} LinkedList;

/*  Allocs and return a new Linked List with len = 0 and
    the start node = NULL
*/
LinkedList *newLinkedList();

/*  Creates a new node and put in the end of the list.
    Empty Strings will be ignored, and 1 will be returned;
*/
int add(LinkedList *l, char *value);

/*  Returns the pointer String saved in the index.
    Returns NULL if out of bounds;
*/
String *getValue(LinkedList *l, uint32_t index);

/*  Returns the pointer to a copy of the String saved in the index.
    Returns NULL if out of bounds;
*/
String *getValueCopy(LinkedList *l, uint32_t idnex);

/*  Frees the String in the index, and saves the new String
    Returns 1 if the index is out of bounds
*/
int set(LinkedList *l, char *value, uint32_t index);

/*  Removes the index element 
    if the index is out of bounds, will returns 1
*/
int delete(LinkedList *l, uint32_t index);

/*  Inserts a new node.
    If the index is is out of bounds (> len) 1 will be returned
*/
int insert(LinkedList *l, char *value, uint32_t index);

/*  Creates a ArrayString from all the values in the list
    All the values are copys of the originals, not references
    If the list is empty a NULL pointer will be returned
*/
ArrayString *toArray(LinkedList *l);

#endif