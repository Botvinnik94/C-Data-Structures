#include "gll-avl.h"
#include <stdio.h>

void print_in_order(struct gll_AVL_node *root){

    if(root){
        print_in_order(root->left);
        printf("%d %d\n", root->key.int_key, *((int*)root->value));
        print_in_order(root->right);
        
    }
}

int main(int argc, char** argv) {

    GLL_AVL* tree = GLL_AVL_newTree(GLL_INT);
    int test_data[10] = {10, 2, 4, 3, 5, 7, 9, 6, 32, 1};
    int i;
    for(i = 0; i < 10; i++){
        GLL_Key key;
        key.int_key = test_data[i];
        GLL_AVL_Insert(tree, key, &test_data[i]);
    }

    print_in_order(tree->root);

    GLL_Key key;
    key.int_key = 10;

    int* output;

    GLL_AVL_Find(tree, key, &output);
    printf("\n%d\n", *((int*)output));

    key.int_key = 4;
    GLL_AVL_Find(tree, key, &output);
    printf("\n%d\n", *((int*)output));

    key.int_key = 98782;
    int out = GLL_AVL_Find(tree, key, &output);
    printf("\n%d - %d\n", out, *((int*)output));

    key.int_key = 9;
    GLL_AVL_Remove(tree, key);

    print_in_order(tree->root);

    return 0;
}