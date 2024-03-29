#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define MAX_SZ 256

// typedef struct List {

// }

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
    int str_count = 0;
    while(fgets(buffer, bufferLength, fp)) {
        str_count += 1;

        char * token = strtok(buffer, ";");

        char* name[3];
        int name_len = 0;
        char* street;
        int c = 0;
        while( token != NULL ) {
            if(c <= 2){
                name_len+=strlen(token);
                name[c] = token;
            }else {
                printf("HERE");
                street = token;
            }
            c+=1;
            token = strtok(NULL, ";");
        }
        printf("%s\n", street);
        char *full_name = (char *)malloc(name_len);
        snprintf( full_name, name_len, "%s%s%s", name[0], name[1], name[2]);
        printf("%s;%s",full_name, street);
    }

    fclose(fp);

    return 0;
}