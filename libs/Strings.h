#ifndef STRINGS_H
#define STRINGS_H

#include <stdlib.h>

typedef struct String {
    char *array;
    size_t len;
} String;

typedef struct ArrayString {
    String **array;
    size_t len;
    size_t capacity;
} ArrayString;

/*  Returns the pointer to a empty String with size of len
    Will returns a NULL Array if len = 0
*/
String *newString(size_t len);

/*  Receives a default C String ended with "\0", and convert to 
    a struct String. 
 */
String *CStringToString(char *src);

/*  Returns a new String, with the specific slice from the passed String 
    ['M', 'a', 'r', 'i', 's', 'a'], from 2 to 4 returns ['r', 'i', 's']
    From/To are bouth from 0 to Len.
    If the range is out of bounds, a NULL string will be returned.
*/
String *getSlice(String *s, size_t from, size_t to);

// Compare 2 diferent Strings
int StringCmp(String *s1, String *s2);

/*  Removes all extra spaces in the start of a String
    Will set the String->Array to Null and len to 0
    if the String is only white spaces
*/
void trim_left(String **s);

/*  Removes all extra spaces in the end of a String
    Will set the String->Array to Null and len to 0 
    if the String is only white spaces
*/
void trim_right(String **s);

/*  Remove all extra spaces in the start/end of a String 
    if the string is only spaces ["     "], a null pointer
    will be alloced to String.array;
*/
void trim(String **s);

/*  Remove all extra spaces of a String 
    if the string is only spaces ["     "], a null pointer
    will be alloced to String.array;
*/
void remove_white_space(String **s);

/*  Splits a String in a Array of Strings, all the extra
    spaces in the string will be removed before split.
    Empty strings will return NULL.
*/
ArrayString *split(String *s, const char spliter);

/*  Create a new Array of Strings.
    if Capacity = 0, a NULL pointer is returned
*/
ArrayString *newArrayString(size_t capacity);

// Converts all Strings in a Array of Strings into a single String 
String *arrayToString(ArrayString *as);

// Pushs the value in the Array, returns -1 if full
int ASPush(ArrayString *as, String *string);

#endif