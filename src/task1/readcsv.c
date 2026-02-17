#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "readcsv.h"
#define MAX_COLS 20
#define MAX_BUFF 1024
#define BIAS 10


int is_num(char s[])
{
    char *p;
    strtod(s, &p);
    return *p == 0;
}

void print_line(FILE *fpwr, int widths[], int cols_count, Len type)
{
    char *chars[3][4] = {
        {"╔", "═", "╦", "╗"}, // Header
        {"╠", "═", "╬", "╣"}, // Body
        {"╚", "═", "╩", "╝"}  // Footer
    };

    fputs(chars[type][0],fpwr);
    for (int col_idx = 0; col_idx < cols_count; ++col_idx)
    {
        for (int i = 0; i < widths[col_idx]; ++i)
        {
            fputs(chars[type][1],fpwr);
        }

        if (col_idx < cols_count - 1)
        {
            fputs(chars[type][2],fpwr);
        }
    }
    fprintf(fpwr,"%s\n",chars[type][3]);
}

void max_width(FILE *fp, int widths[], int *cols_count)
{
    char buff[MAX_BUFF];
    long st_pos = ftell(fp);

    while (fgets(buff, sizeof(buff), fp))
    {
        int col_idx = 0;
        buff[strcspn(buff, "\n")] = 0; //*
        int new_len;

        char *start = buff;
        char *end = strchr(start, ',');

        while ((end != NULL) && (col_idx < MAX_COLS))
        {
            *end = '\0';

            new_len = strlen(start);

            if (new_len > widths[col_idx])
                widths[col_idx] = new_len + BIAS;

            col_idx++;
            start = end + 1;
            end = strchr(start, ',');
        }

        // Последний столбец обрабатываем отдельно
        new_len = strlen(start);
        if (new_len > widths[col_idx])
            widths[col_idx] = new_len + BIAS;
        col_idx++;

        if (col_idx > *cols_count)
        {
            *cols_count = col_idx;
        }
    }

    fseek(fp, st_pos, SEEK_SET);
}

void print_row(FILE *fpwr, char line[], int cols_count, int widths[])
{
   line[strcspn(line,"\n")] = 0;

    char *start = line;
    char *end = strchr(start, ',');

    fprintf(fpwr, "⁠║");
    for (int col_idx = 0; col_idx < cols_count; ++col_idx)
    {
        if (end != NULL)
        {
            *end = '\0';
        }

        if (start == NULL)
        {
            fprintf(fpwr, "%-*s", widths[col_idx], " ");
        }
        else if (is_num(start))
        {
            fprintf(fpwr, "%*s", widths[col_idx], start);
        }
        else
        {
            fprintf(fpwr, "%-*s", widths[col_idx], start);
        }
        fprintf(fpwr, "⁠║");

        if (end != NULL)
        {
            start = end + 1;
            end = strchr(start, ',');
        }
    }
    fprintf(fpwr, "\n");
}

int read_csv(char fileread[], char filewrite[])
{
    FILE *fp = fopen(fileread, "r");
    FILE *fpwr = fopen(filewrite, "w");

    if ((fp == NULL) || (fpwr == NULL))
    {
        printf("Error of opening reading or writing file\n");
        return -1;
    }

    int cols_count = 0;
    long st_pos = ftell(fpwr);
    int widths[MAX_COLS] = {0};
    char buff[MAX_BUFF];

    max_width(fp, widths, &cols_count);

    print_line(fpwr, widths, cols_count, Header);

    while (fgets(buff, sizeof(buff), fp))
    {
        print_row(fpwr, buff, cols_count, widths);
        st_pos = ftell(fpwr);
        print_line(fpwr, widths, cols_count, Body);
    }
    fseek(fpwr, st_pos, SEEK_SET);
    print_line(fpwr, widths, cols_count, Footer);

    fclose(fp);
    fclose(fpwr);

    return 0;
}
