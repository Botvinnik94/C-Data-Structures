#ifndef __GLL_AVL_H
#define __GLL_AVL_H

#include <stdlib.h>
#include <string.h>

#define GLL_INT     0
#define GLL_CHAR    1

typedef union GLL_Key
{
    int int_key;
    char *char_key;
} GLL_Key;

struct gll_AVL_node {
    GLL_Key key;
    void *value;
    char balance_factor;
    struct gll_AVL_node *left, *right;
};

struct gll_AVL_tree {
    int key_type;
    struct gll_AVL_node *root;
};

typedef struct gll_AVL_tree GLL_AVL;

GLL_AVL* GLL_AVL_newTree(int key_type);
int GLL_AVL_destroyTree(GLL_AVL** tree);
int GLL_AVL_Insert(GLL_AVL* tree, GLL_Key key, void *value);
int GLL_AVL_Update(GLL_AVL* tree, GLL_Key key, void *value);
int GLL_AVL_InsertOrUpdate(GLL_AVL* tree, GLL_Key key, void *value);
int GLL_AVL_Find(GLL_AVL* tree, GLL_Key key, void **output);
int GLL_AVL_Remove(GLL_AVL* tree, GLL_Key key);
int GLL_AVL_Clear(GLL_AVL* tree);

struct gll_AVL_node* ___gll_AVL_newNode(GLL_Key key, void* value);
void ___gll_AVL_destroyNode(struct gll_AVL_node** node);
int ___gll_AVL_insert(struct gll_AVL_node** root, GLL_Key key, void* value, int key_type, int *balance_changed);
int ___gll_AVL_update(struct gll_AVL_node* root, GLL_Key key, void* value, int key_type);
int ___gll_AVL_find(struct gll_AVL_node* root, GLL_Key key, struct gll_AVL_node** output, int key_type);
int ___gll_AVL_remove(struct gll_AVL_node** root, GLL_Key key, int key_type, int *balance_changed);
void ___gll_AVL_2child_delete(struct gll_AVL_node** root, struct gll_AVL_node** aux, struct gll_AVL_node* prev, int* balance_changed);

void ___balance_left(struct gll_AVL_node **node, int *balance_changed);
void ___balance_right(struct gll_AVL_node **node, int *balance_changed);

void ___left_left_rotation(struct gll_AVL_node **node, struct gll_AVL_node *node1);
void ___right_right_rotation(struct gll_AVL_node **node, struct gll_AVL_node *node1);
void ___left_right_rotation(struct gll_AVL_node **node, struct gll_AVL_node *node1, struct gll_AVL_node *node2);
void ___right_left_rotation(struct gll_AVL_node **node, struct gll_AVL_node *node1, struct gll_AVL_node *node2);

#endif