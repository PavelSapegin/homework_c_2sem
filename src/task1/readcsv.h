#include <stdio.h>
#include <string.h>

typedef enum {
    Header,
    Body,
    Footer,
} Len;

// readcsv
int is_num(char s[]);
void print_line(FILE* fpwr, int widths[], int cols_count, Len type);
void max_width(FILE* fp, int widths[], int* cols_count);
void print_row(FILE* fpwr, char line[], int cols_count, int widths[], int is_header);
int read_csv(char fileread[], char filewrite[]);

// tests
int create_test_csv(char filename[], char content[]);
int check_file_content(char filename[], char expected[]);
void test_is_num();
void test_base_read_csv();
void test_empty_val_read_csv();
void run_tests();
