#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct tree {
    char* data;
    struct tree *l_tree;
    struct tree *r_tree;
}node;

node* new_node(char* value){
    node *tmp = malloc(sizeof(node));
    tmp -> data = value;
    tmp -> r_tree = NULL;
    tmp -> l_tree = NULL;
    return tmp;
}

node* insert(node *node, char* value){
    if (node == NULL) return new_node(value);
    //printf("%s, %s: %d\n", node->data, value, strcmp(node->data, value));
    if (strcmp(node->data, value) > 0) {
        //node *tmp = insert(node->l_tree, value);
        //node->l_tree = tmp;
        node->l_tree = insert(node->l_tree, value);
    }
    else if (strcmp(node->data, value) <= 0) {
        //node* tmp = insert(node->r_tree, value);
        //node->r_tree = tmp;
        node->r_tree = insert(node->r_tree, value);
    }
    return node;
}

int filter(char* s, int len, FILE* fp) {
    int actual_size = 0;
    int curr = 0;
    for (int i = 0; i < len; i++) {
        char tmp = fgetc(fp);
        if (tmp != '.' && tmp != ',' && tmp != '!' && tmp != '?') {
            s[curr] = tmp;
            actual_size += 1;
            curr += 1;
        }
    }
    return actual_size;
}

void print_tree_forward(node* node) {
    if (node != NULL) 
    {
        printf("%s\n", node->data);
        print_tree_forward(node->l_tree);
        print_tree_forward(node->r_tree);
    }
}

void print_tree_backward(node* node) {
    if (node != NULL)
    {
        print_tree_backward(node->l_tree);
        print_tree_backward(node->r_tree);
        printf("%s\n", node->data);
    }
}

void print_tree_central(node* node) {
    if (node != NULL)
    { 
        print_tree_central(node->l_tree);
        printf("%s\n", node->data);
        print_tree_central(node->r_tree);
        
    }
}

void search(node* node, char letter) {
    if (node != NULL)
    { 
        if((node->data)[0] == letter) printf("%s\n", node->data);
        search(node->l_tree, letter);
        search(node->r_tree, letter);
        
    }
}

void main(){
    char letter;
    printf("Enter letter: ");
    scanf("%c", &letter);
    printf("\n");

    bool is_tree_created = false;
    node* root = NULL;

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
        if (!is_tree_created) {
            root = insert(root, token);
            is_tree_created = true;
        }else insert(root, token);

        //printf("%s\n", token);
        token = strtok(NULL, " ");
    }

    printf("Search by letter %c:\n", letter);
    search(root, letter);
    printf("\n");
    printf("Forward:\n");
    print_tree_forward(root);
    printf("\n");
    printf("Backward:\n");
    print_tree_backward(root);
    printf("\n");
    printf("Central:\n");
    print_tree_central(root);
    free(s);
}
