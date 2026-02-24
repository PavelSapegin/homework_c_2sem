#include "readcsv.h"

int main(int argc, char* argv[])
{
    if ((argc > 1) && (strcmp(argv[1], "--test") == 0)) {
        run_tests();
        return 0;
    }
    read_csv("../input.csv", "../output.txt");
    return 0;
}
