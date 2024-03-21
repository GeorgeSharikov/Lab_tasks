#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct tree {
    char* data;
    struct tree *LTree;
    struct tree *RTree;
}node;

node* create(node *root, char* data){
    node *tmp = malloc(sizeof(node));
    tmp -> data = data;
    tmp -> RTree = NULL;
    tmp -> LTree = NULL;
    root = tmp;
    return root;
}

node* add(node *root, char* data){
    node *root2 = root, *root3 = NULL;
    node *tmp = malloc(sizeof(node));

    tmp -> data = data;
    while(root2 != NULL){
        root3 = root2;
        if (data < root2 -> data){
            root2 = root2 -> LTree;
        }    
        else root2 = root2 -> RTree; 
    }
    tmp -> LTree = NULL;
    tmp -> RTree = NULL;

}

void main(){


    FILE *fp;
    char path[30] = "./tests/examples.txt";
    fp = fopen(path, "r");

    fseek(fp, 0, SEEK_END);
    int len = ftell(fp);
    char* s = (char *)malloc(len);
    fseek(fp, 0, SEEK_SET);

    len = filter(s, len , fp);
    s = realloc(s, len);

    char * token = strtok(s, " ");
    while( token != NULL ) {
       printf("%s\n", token);
       token = strtok(NULL, " ");
    }



    free(s);
}

int filter(char* s, int len, FILE* fp){
    int actual_size = 0;
    int curr = 0;
    for(int i = 0; i < len; i++){
        char tmp = fgetc(fp);
        if (tmp != '.' && tmp != ',' && tmp != '!' && tmp != '?') {
            s[curr] = tmp;
            actual_size+=1;
            curr+=1;
        }
    }
    return actual_size;
}