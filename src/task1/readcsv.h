#include <stdio.h>
#include <string.h>

typedef enum {
    Header,
    Body,
    Footer,
} Len;

// readcsv
int isNum(char s[]);
void printLine(FILE* fpwr, const size_t widths[], int colsCount, Len type);
void maxWidth(FILE* fp, size_t widths[], int* colsCount);
void printRow(FILE* fpwr, char line[], int colsCount, size_t widths[], int isHeader);
int readCsv(char fileread[], char filewrite[]);

// tests
int createTestCsv(char filename[], char content[]);
int checkFileContent(char filename[], char expected[]);
void testIsNum(void);
void testBaseReadCsv(void);
void testEmptyValReadCsv(void);
void runTests(void);
