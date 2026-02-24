#include "readcsv.h"
#include <assert.h>
#define MAX_BUFF 4096

int create_test_csv(char filename[], char content[])
{
    FILE *fp = fopen(filename, "w");
    if (fp == NULL)
    {
        printf("[ERROR] Can't create a test csv file");
        assert(fp != NULL);
        return -1;
    }

    fputs(content, fp);
    fclose(fp);
    return 0;
}

int check_file_content(char filename[], char expected[])
{
    FILE *fp = fopen(filename, "r");
    if (fp == NULL)
    {
        printf("[ERROR] Can't open a test csv file");
        assert(fp != NULL);
        return -1;
    }

    char buff[MAX_BUFF];
    int len = fread(buff, 1, sizeof(buff) - 1, fp);
    buff[len] = '\0';

    fclose(fp);
    int result = (strcmp(buff, expected) != 0);
    if (result != 0)
    {
        printf("[FAIL] File content mismatch.\n");
        printf("[EXPECTED]\n%s\n", expected);
        printf("[GET]\n%s\n", buff);
        assert(result == 0);
    }

    return 0;
}

void test_is_num()
{
    printf("[RUNNING] Test is_num:\n");

    assert(is_num("123") == 1);
    assert(is_num("42.1") == 1);
    assert(is_num("-12") == 1);
    assert(is_num("0.0") == 1);

    assert(is_num("") == 0);
    assert(is_num("testing thus") == 0);
    assert(is_num("4343adsds121") == 0);
    assert(is_num("aaaaa323232") == 0);
    assert(is_num(NULL) == 0);

    printf("[SUCCESS] Test is_num passed!\n");
}

void test_base_read_csv()
{
    printf("[RUNNING] Test base read_csv:\n");

    // TEST WITH BIAS = 2!!!!!

    char input[] =
        "Test field 1,Test field 2\n"
        "test,123\n"
        "long string test!,28.7\n"
        "other text,3\n";

    char expected[] =
        "╔═══════════════════╦══════════════╗\n"
        "║Test field 1       ║Test field 2  ║\n"
        "╠═══════════════════╬══════════════╣\n"
        "║test               ║           123║\n"
        "╠═══════════════════╬══════════════╣\n"
        "║long string test!  ║          28.7║\n"
        "╠═══════════════════╬══════════════╣\n"
        "║other text         ║             3║\n"
        "╚═══════════════════╩══════════════╝\n";

    create_test_csv("test_input.csv", input);

    int result = read_csv("test_input.csv", "test_output.txt");

    assert(result == 0);

    check_file_content("test_output.txt", expected);

    printf("[SUCCESS] Test base read csv passed!\n");
}

void test_empty_val_read_csv()
{
    printf("[RUNNING] Test empty values read csv:\n");

    char input[] =
        "ID,Name,Score\n"
        "1,,99.32\n"
        ",Bob,\n";

    char expected[] =
        "╔════╦══════╦═══════╗\n"
        "║ID  ║Name  ║Score  ║\n"
        "╠════╬══════╬═══════╣\n"
        "║   1║      ║  99.32║\n"
        "╠════╬══════╬═══════╣\n"
        "║    ║Bob   ║       ║\n"
        "╚════╩══════╩═══════╝\n";

    create_test_csv("test_input.csv",input);

    int result = read_csv("test_input.csv","test_output.csv");
    assert(result == 0);

    check_file_content("test_output.csv",expected);

    printf("[SUCCESS] Test empty values read csv passed!\n");
}

void run_tests()
{
    printf("[RUNNING] Starting Tests!\n");

    test_is_num();
    test_base_read_csv();
    test_empty_val_read_csv();

    printf("[SUCCESS] ALL Tests passed!\n");
}
