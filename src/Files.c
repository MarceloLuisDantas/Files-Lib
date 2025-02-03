#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "Strings.h"
#include "LinkedList.h"

typedef struct {
    LinkedList *lines;
    char *file_path;
    size_t len;
} File;

File *loadFile(const char *file_path) { 
    FILE *fp = fopen(file_path, "r");
    if (fp == NULL) {
        printf("Couldn't open or find file %s\n", file_path);
        exit(1);
    }

    File *file = malloc(sizeof(File));
    file->file_path = malloc(sizeof(char) * strlen(file_path) + 1);
    strcpy(file->file_path, file_path);
    
    LinkedList *lines = newLinkedList();
    char *line = NULL;
    size_t _n = 0;
    ssize_t line_len;
    while ((line_len = getline(&line, &_n, fp)) != -1) {
        if (line == NULL) {
            printf("Erro during read line\n");
            exit(1);
        }

        if (line[line_len - 1] == '\n')
            line[line_len - 1] = '\0';
        add(lines, line);
    }
    fclose(fp);
    free(line);
    
    file->lines = lines;
    file->len = lines->len;
    return file;
}

/*  Adds a new string to the end of the file.
    Empty Strings will be ignored, and 1 will be returned
*/
int addLine(File *file, char *new_string) {
    printf("%s\n", new_string);
    int x = add(file->lines, new_string);
    if (x == 0) 
        file->len += 1;
    return x;
}

/*  Retuns the String in th Specfic line of the File.
    Returns null if len out of range or empty file
*/
String *getLine(File *file, uint32_t line) { 
    if (file->len <= 0)
        return NULL;

    return getValue(file->lines, line);
}

/*  Sets a new value to a specific line in a file.
    Retuns 1 if line out of bounds. 
*/
int setLine(File *file, uint32_t line, char *new_string) {
    if (file->len <= 0)
        return 1;
    return set(file->lines, new_string, line);
}

/*  Inserts a new elemento in the specific line.
    Returns 1 if the line out of bounds.
*/
int insertLine(File *file, uint32_t line, char *new_string) { 
    int x = insert(file->lines, new_string, line);
    if (x == 0)
        file->len += 1;
    return x;
}

/*  Removes a line in the specific line.
    Returns 1 if the line out of bounds or empry file.
*/
int removeLine(File *file, uint32_t line) { 
    if (file->len <= 0)
        return 1;

    return delete(file->lines, line);
}

void saveIntoFile(File *file, char *file_path) { 
    FILE *fp = fopen(file_path, "w");
    if (fp == NULL) {
        printf("Couldn't create or find file %s\n", file_path);
        exit(1);
    }

    Node *sup = file->lines->start;
    while (sup != NULL) {
        fprintf(fp, "%s\n", sup->value->array);
        sup = sup->next;
    }

    fclose(fp);
}

// void saveFile(File *file) { }
