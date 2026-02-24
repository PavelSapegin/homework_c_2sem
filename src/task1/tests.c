#include "readcsv.h"
#include <assert.h>
#define MAX_BUFF 4096

int createTestCsv(char filename[], char content[])
{
    FILE* fp = fopen(filename, "w");
    if (fp == NULL) {
        printf("[ERROR] Can't create a test csv file");
        assert(fp != NULL);
        return -1;
    }

    fputs(content, fp);
    fclose(fp);
    return 0;
}

int checkFileContent(char filename[], char expected[])
{
    FILE* fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("[ERROR] Can't open a test csv file");
        assert(fp != NULL);
        return -1;
    }

    char buff[MAX_BUFF];
    size_t len = fread(buff, 1, sizeof(buff) - 1, fp);
    buff[len] = '\0';

    fclose(fp);
    int result = (strcmp(buff, expected) != 0);
    if (result != 0) {
        printf("[FAIL] File content mismatch.\n");
        printf("[EXPECTED]\n%s\n", expected);
        printf("[GET]\n%s\n", buff);
        assert(result == 0);
    }

    return 0;
}

void testIsNum(void)
{
    printf("[RUNNING] Test isNum:\n");

    assert(isNum("123") == 1);
    assert(isNum("42.1") == 1);
    assert(isNum("-12") == 1);
    assert(isNum("0.0") == 1);

    assert(isNum("") == 0);
    assert(isNum("testing thus") == 0);
    assert(isNum("4343adsds121") == 0);
    assert(isNum("aaaaa323232") == 0);
    assert(isNum(NULL) == 0);

    printf("[SUCCESS] Test isNum passed!\n");
}

void testBaseReadCsv(void)
{
    printf("[RUNNING] Test base readCsv:\n");

    // TEST WITH BIAS = 2!!!!!

    char input[] = "Test field 1,Test field 2\n"
                   "test,123\n"
                   "long string test!,28.7\n"
                   "other text,3\n";

    char expected[] = "╔═══════════════════╦══════════════╗\n"
                      "║Test field 1       ║Test field 2  ║\n"
                      "╠═══════════════════╬══════════════╣\n"
                      "║test               ║           123║\n"
                      "╠═══════════════════╬══════════════╣\n"
                      "║long string test!  ║          28.7║\n"
                      "╠═══════════════════╬══════════════╣\n"
                      "║other text         ║             3║\n"
                      "╚═══════════════════╩══════════════╝\n";

    createTestCsv("test_input.csv", input);

    int result = readCsv("test_input.csv", "test_output.txt");

    assert(result == 0);

    checkFileContent("test_output.txt", expected);

    printf("[SUCCESS] Test base read csv passed!\n");
}

void testEmptyValReadCsv(void)
{
    printf("[RUNNING] Test empty values read csv:\n");

    char input[] = "ID,Name,Score\n"
                   "1,,99.32\n"
                   ",Bob,\n";

    char expected[] = "╔════╦══════╦═══════╗\n"
                      "║ID  ║Name  ║Score  ║\n"
                      "╠════╬══════╬═══════╣\n"
                      "║   1║      ║  99.32║\n"
                      "╠════╬══════╬═══════╣\n"
                      "║    ║Bob   ║       ║\n"
                      "╚════╩══════╩═══════╝\n";

    createTestCsv("test_input.csv", input);

    int result = readCsv("test_input.csv", "test_output.csv");
    assert(result == 0);

    checkFileContent("test_output.csv", expected);

    printf("[SUCCESS] Test empty values read csv passed!\n");
}

void runTests(void)
{
    printf("[RUNNING] Starting Tests!\n");

    testIsNum();
    testBaseReadCsv();
    testEmptyValReadCsv();

    printf("[SUCCESS] ALL Tests passed!\n");
}
