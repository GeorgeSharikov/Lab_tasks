#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define MAX_SZ 256

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
    int hash = get_hash(item, strlen(item));
    
    int index = hash % 23;
    return index > 0 ? index : index * (-1);
}

typedef struct node {
    char* name;
    char* street;
    int building;
    struct node *next;
} node;


void push(node** head, char* street, int building, char* name) {
    node* tmp = (node*)malloc(sizeof(node));
    tmp->street = street;
    tmp->building = building;
    tmp->name = name;
    tmp->next = (*head);
    (*head) = tmp;
}

void search(node *item, char* street_par, int building_par) {
    do {
        if (strcmp(item->street, street_par) == 0) {
            if (building_par == 0) {
                printf("%s\n", item->name);
            }
            else {
                if (building_par == item->building) {
                    printf("%s\n", item->name);
                }
            }
        }
        //printf("%s", street_par);
        //printf("%s\n", item->street);
        //printf("%d\n", strcmp(item->street, street_par));
        //printf("FINALLY\n");
        //printf("Street is %s\n", item->street);
        //printf("Build is %d\n", item->building);
        //printf("Name is %s\n", item->name);
        item = item->next;
    } while (item != NULL);
}

int main()
{
     char * street_par = malloc(MAX_SZ);
     printf("Street: ");
     fgets(street_par, MAX_SZ, stdin);
     if ((strlen(street_par) > 0) && (street_par[strlen(street_par) - 1] == '\n'))
         street_par[strlen (street_par) - 1] = '\0';
     char* street_par_n = malloc(strlen(street_par));
     sprintf(street_par_n, " %s", street_par);
     printf("\n");

     printf("Building: ");
     char *building = malloc(MAX_SZ);
     fgets(building, MAX_SZ, stdin);
     if ((strlen(building) > 0) && (building[strlen(building) - 1] == '\n'))
         building[strlen (building) - 1] = '\0';
     if (strlen(building) == 0) building = "0";
     int building_par = atoi(building);
     printf("\n");
   
    char buffer[256];
    FILE* fp = fopen("mock.txt", "r");
    int str_count = 0;

    node* arr[23];
    for (int i = 0; i < 23; i++)
    {
        arr[i] = NULL;
    }

    while (fgets(buffer, sizeof(buffer), fp)) {
        str_count += 1;

        char* token = strtok(buffer, ";");

        char* name[3];
        int name_len = 0;
        char* address;
        int c = 0;
        while (token != NULL) {
            if (c <= 2) {
                name[c] = token;
                name_len += strlen(token);
            }
            else if (c == 3) {
                address = token;
                
                break;
            }
            c += 1;
            token = strtok(NULL, ";");
        }
        
        char* old_street = strtok(address, ",");
        char* street = malloc(strlen(old_street) + 1);
        snprintf(street, strlen(old_street) + 1, "%s", old_street);
        int building = atoi(strtok(NULL, ","));

        char* full_name = malloc(name_len + 1);
        snprintf(full_name, name_len + 1, "%s%s%s", name[0], name[1], name[2]);

        int item_index = get_index(street);
        //printf("%s : %d\n", street, item_index);

        push(&arr[item_index], street, building, full_name);

    }
    //printf("%s : %s\n", arr[3]->name, arr[3]->street);
    //printf("%s : %s\n", arr[14]->name, arr[14]->street);
    //printf("%s : %s\n", arr[14]->next->name, arr[14]->next->street);
    //printf("%s : %s\n", arr[14]->next->next->name, arr[14]->next->next->street);
    //printf("%s : %s\n", arr[7]->name, arr[7]->street);
    //printf("%s : %s\n", arr[7]->next->name, arr[7]->next->street);
    //printf("%s : %s\n\n", arr[11]->name, arr[11]->street);

    int ind = get_index(street_par_n);
    
    search(arr[ind], street_par_n, building_par);
    fclose(fp);

    return 0;
}