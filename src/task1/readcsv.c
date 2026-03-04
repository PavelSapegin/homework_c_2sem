#include "readcsv.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_COLS 20
#define MAX_BUFF 4096
#define BIAS 2

int isNum(char s[])
{
    if ((s == NULL) || (*s == '\0'))
        return 0;

    char* p;
    strtod(s, &p);
    return *p == '\0';
}

void printLine(FILE* fpwr, const size_t widths[], int colsCount, Len type)
{
    char* chars[3][4] = {
        { "╔", "═", "╦", "╗" }, // Header
        { "╠", "═", "╬", "╣" }, // Body
        { "╚", "═", "╩", "╝" } // Footer
    };

    fputs(chars[type][0], fpwr);
    for (int colIdx = 0; colIdx < colsCount; ++colIdx) {
        for (size_t i = 0; i < widths[colIdx]; ++i) {
            fputs(chars[type][1], fpwr);
        }

        if (colIdx < colsCount - 1) {
            fputs(chars[type][2], fpwr);
        }
    }
    fprintf(fpwr, "%s\n", chars[type][3]);
}

void maxWidth(FILE* fp, size_t widths[], int* colsCount)
{
    char buff[MAX_BUFF];
    long stPos = ftell(fp);

    while (fgets(buff, sizeof(buff), fp)) {
        int colIdx = 0;
        buff[strcspn(buff, "\r\n")] = 0;
        size_t newLen;

        char* start = buff;
        char* end = strchr(start, ',');

        while ((end != NULL) && (colIdx < MAX_COLS)) {
            *end = '\0';

            newLen = strlen(start);

            if (newLen > widths[colIdx])
                widths[colIdx] = newLen + BIAS;

            colIdx++;
            start = end + 1;
            end = strchr(start, ',');
        }

        // Последний столбец обрабатываем отдельно
        if (colIdx < MAX_COLS) {
            newLen = strlen(start);
            if (newLen > widths[colIdx])
                widths[colIdx] = newLen + BIAS;
            colIdx++;
        }

        if (colIdx > *colsCount) {
            *colsCount = colIdx;
        }
    }

    fseek(fp, stPos, SEEK_SET);
}

void printRow(FILE* fpwr, char line[], int colsCount, size_t widths[], int isHeader)
{
    line[strcspn(line, "\r\n")] = 0;

    char* start = line;
    char* end = strchr(start, ',');

    fprintf(fpwr, "║");
    for (int colIdx = 0; colIdx < colsCount; ++colIdx) {
        if (end != NULL) {
            *end = '\0';
        }

        if ((isNum(start)) && !(isHeader)) {
            fprintf(fpwr, "%*s", (int)widths[colIdx], start);
        } else {
            fprintf(fpwr, "%-*s", (int)widths[colIdx], start);
        }
        fprintf(fpwr, "║");

        if (end != NULL) {
            start = end + 1;
            end = strchr(start, ',');
        } else
            start = NULL;
    }
    fprintf(fpwr, "\n");
}

int readCsv(char fileread[], char filewrite[])
{
    FILE* fp = fopen(fileread, "r");
    FILE* fpwr = fopen(filewrite, "w");

    if ((fp == NULL) || (fpwr == NULL)) {
        printf("Error of opening reading or writing file\n");
        if (fp)
            fclose(fp);
        if (fpwr)
            fclose(fpwr);
        return -1;
    }

    int isHeader = 1;
    int isFirstRow = 1;
    int colsCount = 0;
    size_t widths[MAX_COLS] = { 0 };
    char buff[MAX_BUFF];

    maxWidth(fp, widths, &colsCount);

    printLine(fpwr, widths, colsCount, Header);

    while (fgets(buff, sizeof(buff), fp)) {
        if (!isFirstRow)
            printLine(fpwr, widths, colsCount, Body);
        printRow(fpwr, buff, colsCount, widths, isHeader);
        isFirstRow = 0;
        isHeader = 0;
    }
    printLine(fpwr, widths, colsCount, Footer);

    fclose(fp);
    fclose(fpwr);

    return 0;
}
