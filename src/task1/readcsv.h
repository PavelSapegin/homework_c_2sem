#include <stdio.h>

typedef enum
{
    Header,
    Body,
    Footer,
} Len;

int is_num(char s[]);
void print_line(FILE *fpwr, int widths[], int cols_count, Len type);
void max_width(FILE *fp, int widths[], int *cols_count);
void print_row(FILE *fpwr, char line[], int cols_count, int widths[]);
int read_csv(char fileread[], char filewrite[]);
