#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "avl.h"

int load(char filepath[])
{
    FILE* fp = fopen(filepath,"r");
    char buff[1024];
    char iata[10];
    char name[1000];
    while (fgets(buff,sizeof(buff),fp))
    {
        sscanf(buff,"%[^:]:%[^\n]",iata,name);
        printf("%s:%s\n",iata,name);
    }
    fclose(fp);
}


int main(void)
{
    load("./airports.txt");
    return 0;
}
