#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define MAX_SZ 256

typedef struct node {
    char* name;
    char* street;
    int building;
    struct node *next;
} node;


void list_push(node** head, char* street, int building, char* name) {
    //printf("PUSH\n");
    node* tmp = (node*)malloc(sizeof(node));
    //printf("%s", street);
    tmp->street = street;
    //printf("%s", tmp->street);
    tmp->building = building;
    tmp->name = name;
    tmp->next = (*head);
    (*head) = tmp;   
}

uint32_t get_hash(unsigned char* key, int len)
{
    uint32_t hash, i;
    for (hash = i = 0; i < len; ++i)
    {
        hash += key[i];
        hash += (hash << 10);
        hash ^= (hash >> 6);
    }
    hash += (hash << 3);
    hash ^= (hash >> 11);
    hash += (hash << 15);
    return hash;
}

int get_index(char* item) {
    int hash = get_hash(item, sizeof(item));
    int index = hash % 23;
    return index > 0 ? index : index*(-1);
}

void search(node *item, char* street_par, int building_par) {
    while (item->next) {
        //printf("%s\n", item->street);
        //printf("%s\n", item->name);
        //printf("%d\n", item->building);
        //printf("LOLOLO");
        printf("%sc\n", street_par);
        printf("%sc\n", item->street);
        printf("%d\n", street_par == item->street);

        if (item->street == street_par) {
            printf("Final %s", item->name);
        }
        item = item->next;
    }
}

int main()
{
     char * street_par = malloc(MAX_SZ);
     printf("Street: ");
     fgets(street_par, MAX_SZ, stdin);
     if ((strlen(street_par) > 0) && (street_par[strlen(street_par) - 1] == '\n'))
         street_par[strlen (street_par) - 1] = '';
     printf("\n");

     printf("Building: ");
     char *building = malloc(MAX_SZ);
     fgets(building, MAX_SZ, stdin);
     if ((strlen(building) > 0) && (building[strlen(building) - 1] == '\n'))
         building[strlen (building) - 1] = '\0';
     if (strlen(building) == 0) building = "0";
     int building_par = atoi(building);
     printf("\n");
    // printf("%s\n", street);
    // printf("%d", building=="");
    

    char buffer[256];
    FILE* fp = fopen("mock.txt", "r");
    int str_count = 0;

    node* arr[23];
    for (int i = 0; i < sizeof(arr)/sizeof(node); i++) arr[i] = NULL;

    while (fgets(buffer, sizeof(buffer), fp)) {
        str_count += 1;

        char * token = strtok(buffer, ";");

        char* name[3];
        int name_len = 0;
        char* address;
        int c = 0;
        while( token != NULL ) {
            if(c <= 2){
                //printf("%s\n", token);
                name[c] = token;
                name_len+=strlen(token);              
            }else if(c == 3) {
                address = token;
            }
            c+=1;
            token = strtok(NULL, ";");
        }
        char* street = strtok(address, ",");
        int building = atoi(strtok(NULL, ","));
        //printf("%s, %d\n", street, building);
        
        //printf("%s\n", name[2]);  
        char *full_name = (char *)malloc(name_len+1);
        snprintf( full_name, name_len+1, "%s%s%s", name[0], name[1], name[2]);
        /*printf("%s;%s\n",full_name, street);*/

        int item_index = get_index(street);
        /*printf*/("%s: %d\n", street, item_index);
        if (arr[item_index] == NULL) {
            node* head = NULL;
            arr[item_index] = head;
        }
        //printf("List push: ", street);
        list_push(&arr[item_index], street, building, full_name);
    }
    //printf(arr[21]->street);
    int ind = get_index(street_par);
    printf("INDEX %d\n", ind);
    
    search(arr[ind], street_par, building_par);
    fclose(fp);

    return 0;
}