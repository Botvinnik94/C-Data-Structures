#include "gll-avl.h"

GLL_AVL* GLL_AVL_newTree(const int key_type) {

    GLL_AVL* new_tree = NULL;

    if(key_type == GLL_INT || key_type == GLL_CHAR) {
        new_tree = calloc(1, sizeof(GLL_AVL));
        new_tree->key_type = key_type;
    }

    return new_tree;
}

int GLL_AVL_destroyTree(GLL_AVL** tree) {

    if(GLL_AVL_Clear(*tree) == 0) {
        free(*tree);
        *tree = NULL;
        return 0;
    }

    return -1;
}

int GLL_AVL_Clear(GLL_AVL* tree) {
    
    if(tree != NULL){
        while(tree->root != NULL){
            GLL_AVL_Remove(tree, tree->root->key);
        }
        return 0;
    }

    return -1;
}

int GLL_AVL_Insert(GLL_AVL* tree, GLL_Key key, void *value) {

    if(tree != NULL){
        int balance_changed = 0;

        if(tree->key_type == GLL_INT || tree->key_type == GLL_CHAR){
            return ___gll_AVL_insert(&(tree->root), key, value, tree->key_type, &balance_changed);
        }
    }

    return -3;
}

int GLL_AVL_Remove(GLL_AVL* tree, GLL_Key key) {

    if(tree != NULL){
        int balance_changed = 0;

        if(tree->key_type == GLL_INT || tree->key_type == GLL_CHAR){
            return ___gll_AVL_remove(&(tree->root), key, tree->key_type, &balance_changed);
        }
    }

    return -3;
}

int GLL_AVL_Update(GLL_AVL* tree, GLL_Key key, void *value){

    if(tree != NULL){
        if(tree->key_type == GLL_INT || tree->key_type == GLL_CHAR){
            return ___gll_AVL_update(tree->root, key, value, tree->key_type);
        }
    }

    return -3;
}

int GLL_AVL_InsertOrUpdate(GLL_AVL* tree, GLL_Key key, void *value){

    if(tree != NULL){
        void *output;
        if(GLL_AVL_Find(tree, key, &output) == 0){
            return GLL_AVL_Update(tree, key, value);
        }
        else{
            return GLL_AVL_Insert(tree, key, value);
        }
    }

    return -3;
}

int GLL_AVL_Find(GLL_AVL* tree, GLL_Key key, void **output) {

    if(tree != NULL){
        if(tree->key_type == GLL_INT || tree->key_type == GLL_CHAR){
            struct gll_AVL_node* output_node = NULL;
            if(___gll_AVL_find(tree->root, key, &output_node, tree->key_type) == 0) {
                *output = output_node->value;
                return 0;
            }
            
            return -1;
        }
    }

    return -3;
}

int ___gll_AVL_insert(struct gll_AVL_node** root, GLL_Key key, void* value, int key_type, int *balance_changed){

    struct gll_AVL_node* new_node = NULL;

    if(*root == NULL) {
        new_node = ___gll_AVL_newNode(key, value);
        if(new_node != NULL) {
            *root = new_node;
            return 0;
        }
        return -2;
    }
    
    if(key_type == GLL_INT) {
        if(key.int_key < (*root)->key.int_key){
            if(___gll_AVL_insert(&((*root)->left), key, value, key_type, balance_changed) == 0){
                if(*balance_changed){
                    ___balance_left(root, balance_changed);
                }
                return 0;
            }
        }
        else if(key.int_key > (*root)->key.int_key){
            if(___gll_AVL_insert(&((*root)->right), key, value, key_type, balance_changed) == 0){
                if(*balance_changed){
                    ___balance_right(root, balance_changed);
                }
                return 0;
            }
        }
    }
    else if(key_type == GLL_CHAR) {
        if(strcmp(key.char_key, (*root)->key.char_key) < 0){
            if(___gll_AVL_insert(&((*root)->left), key, value, key_type, balance_changed) == 0){
                if(*balance_changed){
                    ___balance_left(root, balance_changed);
                }
                return 0;
            }
        }
        else if(strcmp(key.char_key, (*root)->key.char_key) > 0){
            if(___gll_AVL_insert(&((*root)->right), key, value, key_type, balance_changed) == 0){
                if(*balance_changed){
                    ___balance_right(root, balance_changed);
                }
                return 0;
            }
        }
    }

    return -1;
}

int ___gll_AVL_update(struct gll_AVL_node* root, GLL_Key key, void* value, int key_type){

    if(root == NULL) {
        return -1;
    }
    if(key_type == GLL_INT) {
        if(key.int_key < root->key.int_key){
            return ___gll_AVL_update(root->left, key, value, key_type);
        }
        else if(key.int_key > root->key.int_key){
            return ___gll_AVL_update(root->right, key, value, key_type);
        }
        else {
            root->value = value;
        }
    }
    else if(key_type == GLL_CHAR) {
        if(strcmp(key.char_key, root->key.char_key) < 0){
            return ___gll_AVL_update(root->left, key, value, key_type);
        }
        else if(strcmp(key.char_key, root->key.char_key) > 0){
            return ___gll_AVL_update(root->right, key, value, key_type);
        }
        else {
            root->value = value;
        }
    }

    return 0;
}

int ___gll_AVL_find(struct gll_AVL_node* root, GLL_Key key, struct gll_AVL_node** output, int key_type) {

    if(root == NULL) {
        return -1;
    }
    if(key_type == GLL_INT) {
        if(key.int_key < root->key.int_key){
            return ___gll_AVL_find(root->left, key, output, key_type);
        }
        else if(key.int_key > root->key.int_key){
            return ___gll_AVL_find(root->right, key, output, key_type);
        }
        else {
            *output = root;
        }
    }
    else if(key_type == GLL_CHAR) {
        if(strcmp(key.char_key, root->key.char_key) < 0){
            return ___gll_AVL_find(root->left, key, output, key_type);
        }
        else if(strcmp(key.char_key, root->key.char_key) > 0){
            return ___gll_AVL_find(root->right, key, output, key_type);
        }
        else {
            *output = root;
        }
    }

    return 0;
}

int ___gll_AVL_remove(struct gll_AVL_node** root, GLL_Key key, int key_type, int *balance_changed) {

    if(*root == NULL){
        return -1;
    }

    if(key_type == GLL_INT){
        if(key.int_key < (*root)->key.int_key){
            if(___gll_AVL_remove(&((*root)->left), key, key_type, balance_changed) == 0){
                if(*balance_changed){
                    ___balance_right(root, balance_changed);
                }
                return 0;
            }
        }
        else if(key.int_key > (*root)->key.int_key){
            if(___gll_AVL_remove(&((*root)->right), key, key_type, balance_changed) == 0){
                if(*balance_changed){
                    ___balance_left(root, balance_changed);
                }
                return 0;
            }
        }

        return -1;
    }
    else if(key_type == GLL_CHAR){
        if(strcmp(key.char_key, (*root)->key.char_key) < 0){
            if(___gll_AVL_remove(&((*root)->left), key, key_type, balance_changed) == 0){
                if(*balance_changed){
                    ___balance_right(root, balance_changed);
                }
                return 0;
            }
        }
        else if(strcmp(key.char_key, (*root)->key.char_key) > 0){
            if(___gll_AVL_remove(&((*root)->right), key, key_type, balance_changed) == 0){
                if(*balance_changed){
                    ___balance_left(root, balance_changed);
                }
                return 0;
            }
        }

        return -1;
    }

    struct gll_AVL_node** aux = root;
    if((*aux)->right == NULL){
        *root = (*aux)->left;
        ___gll_AVL_destroyNode(aux);
        *balance_changed = 1;
    }
    else if((*aux)->left == NULL){
        *root = (*aux)->right;
        ___gll_AVL_destroyNode(aux);
        *balance_changed = 1;
    }
    else{
        ___gll_AVL_2child_delete(root, &((*aux)->left), *aux, balance_changed);
        if(*balance_changed){
            ___balance_right(root, balance_changed);
        }
    }

    return 0;
}

void ___gll_AVL_2child_delete(struct gll_AVL_node** root, struct gll_AVL_node** aux, struct gll_AVL_node* prev, int* balance_changed){

    if((*aux)->right != NULL){
        ___gll_AVL_2child_delete(root, &((*aux)->right), *aux, balance_changed);
        if(*balance_changed){
            ___balance_left(aux, balance_changed);
        }
    }
    else{
        (*root)->key = (*aux)->key;
        (*root)->value = (*aux)->value;
        if(prev->left == *aux){
            prev->left = (*aux)->left;
        }
        else
        {
            prev->right = (*aux)->left;
        }
        ___gll_AVL_destroyNode(aux);
        *balance_changed = 1;
    }
}

struct gll_AVL_node* ___gll_AVL_newNode(GLL_Key key, void* value) {

    struct gll_AVL_node* new_node = calloc(1, sizeof(struct gll_AVL_node));
    if(new_node != NULL){
        new_node->key = key;
        new_node->value = value;
    }

    return new_node;
}

void ___gll_AVL_destroyNode(struct gll_AVL_node** node){
    free(*node);
    node = NULL;
}

void ___balance_left(struct gll_AVL_node **node, int *balance_changed){
    switch ((*node)->balance_factor)
    {
        case 0:
            (*node)->balance_factor = -1;
            break;
        case 1:
            (*node)->balance_factor = 0;
            *balance_changed = 0;
            break;
        case -1:
            if((*node)->left->balance_factor == -1){
                ___left_left_rotation(node, (*node)->left);
            }
            else{
                ___left_right_rotation(node, (*node)->left, (*node)->left->right);
            }
            *balance_changed = 0;
    }
}

void ___balance_right(struct gll_AVL_node **node, int *balance_changed){
    switch ((*node)->balance_factor)
    {
        case 0:
            (*node)->balance_factor = 1;
            break;
        case 1:
            if((*node)->right->balance_factor == 1){
                ___right_right_rotation(node, (*node)->right);
            }
            else{
                ___right_left_rotation(node, (*node)->right, (*node)->right->left);
            }
            *balance_changed = 0;
            break;
        case -1:
            (*node)->balance_factor = 0;
            *balance_changed = 0;
    }
}

void ___left_left_rotation(struct gll_AVL_node **node, struct gll_AVL_node *node1){
    (*node)->left = node1->right;
    node1->right = *node;
    (*node)->balance_factor = 0;
    node1->balance_factor = 0;
    *node = node1;
}

void ___right_right_rotation(struct gll_AVL_node **node, struct gll_AVL_node *node1){
    (*node)->right = node1->left;
    node1->left = *node;
    (*node)->balance_factor = 0;
    node1->balance_factor = 0;
    *node = node1;
}

void ___left_right_rotation(struct gll_AVL_node **node, struct gll_AVL_node *node1, struct gll_AVL_node *node2) {
    (*node)->left = node2->right;
    node2->right = *node;
    node1->right = node2->left;
    node2->left = node1;
    if(node2->balance_factor == -1){
        node1->balance_factor = 0;
        (*node)->balance_factor = 1;
    }
    else if(node2->balance_factor == 1){
        node1->balance_factor = -1;
        (*node)->balance_factor = 0;
    }
    else{
        node1->balance_factor = 0;
        (*node)->balance_factor = 0;
    }
    *node = node2;
    (*node)->balance_factor = 0;
}

void ___right_left_rotation(struct gll_AVL_node **node, struct gll_AVL_node *node1, struct gll_AVL_node *node2){
    (*node)->right = node2->left;
    node2->left = *node;
    node1->left = node2->right;
    node2->right = node1;
    if(node2->balance_factor == 1){
        node1->balance_factor = 0;
        (*node)->balance_factor = -1;
    }
    else if(node2->balance_factor == -1){
        node1->balance_factor = 1;
        (*node)->balance_factor = 0;
    }
    else{
        node1->balance_factor = 0;
        (*node)->balance_factor = 0;
    }
    *node = node2;
    (*node)->balance_factor = 0;
}