#include "readcsv.h"

int main(int argc, char* argv[])
{
    if ((argc > 1) && (strcmp(argv[1], "--test") == 0)) {
        runTests();
        return 0;
    }
    readCsv("../input.csv", "../output.txt");
    return 0;
}
