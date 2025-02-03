#ifndef FILES_H
#define FILES_H

#include <stdint.h>
#include "Strings.h"
#include "LinkedList.h"

typedef struct {
    LinkedList *lines;
    char *file_path;
    size_t len;
} File;

File *loadFile(char *file_path);

void saveIntoFile(File *file, char *file_path);

void saveFile(File *file);

int addLine(File *file, char *new_string);

String *getLine(File *file, uint32_t line);

int setLine(File *file, uint32_t line, char *new_string);

int insertLine(File *file, uint32_t line, char *new_string);

int removeLine(File *file, uint32_t line);

#endif