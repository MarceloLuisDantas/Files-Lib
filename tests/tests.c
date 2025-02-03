#include <stdio.h>

#include "../src/Files.h"
#include "Strings.h"
#include "LinkedList.h"

#define TRUE 1
#define FALSE 0

int runTest(int (*test)(), int number, const char *test_name) {
    printf("Running test %d - %s\n", number, test_name);
    int result = test();
    if (result == FALSE) {
        printf("Teste %d - %s, DO NOT PASS\n\n", number, test_name);
        return FALSE;
    }
    printf("Teste %d - %s, PASS\n\n", number, test_name);
    return TRUE;
}

// ===============================================
// ==================== TESTS ==================== 
// ===============================================

int test_load_file() {
    File *empty_f = loadFile("tests/files/empty_file.txt");
    if (empty_f->len != 0) {
        printf("Len of empty file should be 0\n");
        return FALSE;
    } 
    
    File *f1 = loadFile("tests/files/file_1.txt");
    if (f1->len != 9) {
        printf("Should be 9 lines. Gets: %ld\n", f1->len);
        return FALSE;
    }

    char *foo[9] = {
        "teste 0", "teste 1", "teste 2", "teste 3", "teste 4", 
        "teste 5", "teste 6", "teste 7", "teste 8"
    };

    for (int i = 0; i < f1->len; i++) {
        String *st = getValue(f1->lines, i);
        if (StringCmp(st, CStringToString(foo[i])) == FALSE) {
            printf("Strings not equals\n");
            printf("Strings 1: \"%s\"\n", st->array);
            printf("Strings 2: \"%s\"\n", foo[i]);
            return FALSE;
        }
    }
        
    return TRUE;
}

int test_add_get_set() {
    File *f = loadFile("tests/files/empty_file.txt");
    int r0 = addLine(f, "");
    if (r0 != 1) {
        printf("r0 should be 1\n");
        return FALSE;
    }

    String *r1 = getLine(f, 0);
    if (r1 != NULL) {
        printf("r1 should be 1\n");
        return FALSE;
    }

    int r2 = setLine(f, 1, "teste");
    if (r2 != 1) {
        printf("r2 should be 1\n");
        return FALSE;
    }

    addLine(f, "linha -1");
    setLine(f, 0, "linha 0");
    String *l1 = getLine(f, 0);
    if (l1 == NULL) {
        printf("null");
        return FALSE;
    }

    if (StringCmp(l1, CStringToString("linha 0")) != TRUE) {
        printf("l1 should be \"linha 0\", gets: %s\n", l1->array);
        return FALSE;
    }

    return TRUE;
}

int test_remove_insert() {
    File *f = loadFile("tests/files/file_1.txt");
    removeLine(f, 0);
    String *l0 = getLine(f, 0);
    if (StringCmp(l0, CStringToString("teste 1")) == FALSE) {
        printf("l0 should be \"linha 1\", gets: %s\n", l0->array);
        return FALSE;
    }

    insertLine(f, 0, "teste 0");
    String *l02 = getLine(f, 0);
    if (StringCmp(l02, CStringToString("teste 0")) == FALSE) {
        printf("l0 should be \"teste 0\", gets: %s\n", l0->array);
        return FALSE;
    }
    
    return TRUE;
}

int test_save_file() {
    File *f = loadFile("tests/files/file_1.txt");
    addLine(f, "teste 9");
    addLine(f, "teste");
    addLine(f, "teste 10");
    addLine(f, "teste 9");
    addLine(f, "teste 112");
    addLine(f, "teste 12");
    removeLine(f, 2);
    insertLine(f, 4, "inserido linha 5");
    insertLine(f, 7, "inserido linha 8");

    saveIntoFile(f, "tests/files/saved_file.txt");

    return TRUE;
}



// ===============================================
// ============== RUNNING ALL TESTS ============== 
// ===============================================

int main() {
    printf("RUNNING Strings Tests ======================================\n");
    runTest(&test_load_file, 1, "Load file Test");
    runTest(&test_add_get_set, 2, "Set and Get Test");
    runTest(&test_remove_insert, 3, "Remove and Insert Test");
    runTest(&test_save_file, 4, "Save into new file Test");
    return 0;
}