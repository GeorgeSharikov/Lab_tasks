#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define MAX_SZ 256
int main()
{   
    // char *street = malloc(MAX_SZ);
    // fgets(street, MAX_SZ, stdin);
    // if ((strlen(street) > 0) && (street[strlen(street) - 1] == '\n'))
    //     street[strlen (street) - 1] = '\0';

    // char *building = malloc(MAX_SZ);
    // fgets(building, MAX_SZ, stdin);
    // if ((strlen(building) > 0) && (building[strlen(building) - 1] == '\n'))
    //     building[strlen (building) - 1] = '\0';
    // printf("%s\n", street);
    // printf("%d", building=="");

    int bufferLength = 255;
    char buffer[255];
    
    FILE* fp = fopen("mock.txt", "r");

    while(fgets(buffer, bufferLength, fp)) {
        printf("%s\n", buffer);
    }

    fclose(fp);

    return 0;
}