#ifndef GRAPHS_AVL_TREE_H
#define GRAPHS_AVL_TREE_H
#include <string.h>
#include <stdlib.h>
#include "avl_node.h"
#include <tom/string_ops.h>

typedef struct avl_tree_t {
    avl_node_t *root;
} avl_tree_t;

//API FUNCTIONS
avl_tree_t *make_avl_tree(void);
void avl_insert(avl_tree_t*, char*);
void avl_delete(avl_tree_t*, char*);
void print_avl_tree(avl_tree_t*);
int in_avl_tree(avl_tree_t*, char*);

//INTERNAL FUNCTIONS
void avl_balance_above(avl_tree_t*,avl_node_t*);
void avl_balance(avl_tree_t*,avl_node_t*);
void l_rotate(avl_tree_t*,avl_node_t*);
void r_rotate(avl_tree_t*,avl_node_t*);
void mini_l_rotate(avl_tree_t*, avl_node_t*);
void mini_r_rotate(avl_tree_t*, avl_node_t*);

avl_tree_t *make_avl_tree(void){
    avl_tree_t *tree = malloc(sizeof(avl_tree_t));
    if(tree==NULL){
        perror("out of memory in make_avl_tree");
        exit(0);
    }
    tree->root = NULL;
    return tree;
}

void avl_insert(avl_tree_t *tree, char *data){
    if(data == NULL) return; //no null strings allowed
    if(tree->root == NULL){
        tree->root = make_avl_node(data);
        return;
    }

    avl_node_t *new = make_avl_node(data);
    avl_node_t *temp = tree->root;

    while(1){
        int comp = strcmp(temp->s, new->s);
        if(comp==0) return; //exit without adding (no dupes)
        if(comp<0){
            if(temp->r == NULL){
                temp->r = new;
                new->parent = temp;
                break;
            }
            temp = temp->r;
        }
        else{
            if(temp->l == NULL) {
                temp->l = new;
                new->parent = temp;
                break;
            }
            temp = temp->l;
        }
    }
    avl_balance_above(tree, new);
}

void print_avl_tree(avl_tree_t *t){
    print_avl_node(t->root, 0);
}

int in_avl_tree(avl_tree_t *t, char *s){
    if(s==NULL) return 0; //no null values in tree
    avl_node_t *tmp = t->root;
    while(1){
        if(tmp == NULL) return 0;
        int comp = strcmp(tmp->s, s);
        if(!comp){
            return 1;
        }
        else if(comp<0){
            tmp = tmp->r;
        }
        else {
            tmp = tmp->l;
        }
    }
}

void avl_delete(avl_tree_t *t, char *str){
    avl_node_t *to_remove = t->root;
    while(1){
        if(to_remove == NULL) return;
        int cmp = strcmp(to_remove->s, str);
        if(!cmp){
            break;
        }
        to_remove = (cmp<0)?to_remove->r:to_remove->l;
    }

    avl_node_t *parent = to_remove->parent;
    if(is_leaf(to_remove)){ //no children
        if(parent!=NULL) {
            if (parent->l == to_remove) parent->l = NULL;
            else parent->r = NULL;
            free(to_remove);
        }
        else{
            free(to_remove); //removing root and it is a leaf
            t->root = NULL;
            return;
        }
    }
    else{   //one or more children
        if(to_remove->l == NULL || to_remove ->r ==NULL){
            avl_node_t *replacement = (to_remove->l == NULL)?to_remove->r:to_remove->l;
            if(parent!=NULL) {
                char side = (parent->l == to_remove) ? 'l' : 'r';
                switch (side) {
                    case 'l':
                        parent->l = replacement;
                        break;
                    case 'r':
                        parent->r = replacement;
                        break;
                    default:
                        printf("broke in avl_delete\n"); // should never reach here
                }
            }
            else{
                t->root = replacement;
            }
            replacement->parent = parent;
            free(to_remove->s);
            free(to_remove);
        }
        else{
            //two children
            avl_node_t *replacement = to_remove->l;
            while(replacement->r != NULL) replacement = replacement->r; //get largest value in left sub-tree

            free(to_remove->s);
            to_remove->s = replacement->s; //replacement now needs to be removed

            avl_tree_t *subtree = malloc(sizeof(avl_tree_t));
            subtree->root = to_remove->l;
            avl_delete(subtree, replacement->s);

        }
    }
    avl_balance_above(t, parent);
}

void avl_balance_above(avl_tree_t *t, avl_node_t *node) {
    avl_node_t *tmp = node;
    while(tmp != NULL){
        tmp->balance = avl_calc_balance(tmp);
        tmp->height = avl_height(tmp);
        if(!is_balanced(tmp)){
            avl_balance(t, tmp);
        }
        tmp = tmp->parent;
    }
}

void avl_balance(avl_tree_t *t, avl_node_t *node){
    if(node->balance > 1){
        if(node->r->balance <= -1){
            mini_r_rotate(t, node->r);
            l_rotate(t, node);
        }
        else{
            l_rotate(t,node);
        }
    }
    else if(node->balance < -1){
        if(node->l->balance >= 1){
            mini_l_rotate(t, node->l);
            r_rotate(t, node);
        }
        else{
            r_rotate(t,node);
        }
    }
}

void l_rotate(avl_tree_t *t, avl_node_t *n){
    if(n==t->root){
        avl_node_t *t1 = t->root, *t2 = n->r;
        t->root = t2;
        t1->r = t2->l;
        t2->l = t1;
        t1->parent = t2;
        t2->parent = NULL;

        t1->balance = avl_calc_balance(t1);
        t2->balance = avl_calc_balance(t2);
        t1->height = avl_height(t1);
        t2->height = avl_height(t2);
        if(t2->r != NULL) t2->r->height = avl_height(t2->r);
    }
    else {
        avl_node_t *t1 = n, *t2 = n->r;
        avl_node_t *p = t1->parent;
        p->r = t2;
        t1->r = t2->l;
        t2->l = t1;
        t1->parent = t2;
        t2->parent = p;

        t1->balance = avl_calc_balance(t1);
        t2->balance = avl_calc_balance(t2);
        t1->height = avl_height(t1);
        t2->height = avl_height(t2);
        if(t2->r != NULL) t2->r->height = avl_height(t2->r);
    }
}

void r_rotate(avl_tree_t *t, avl_node_t *n){
    if(n==t->root){
        avl_node_t *t1 = t->root, *t2 = n->l;
        t->root = t2;
        t1->l = t2->r;
        t2->r = t1;
        t1->parent = t2;
        t2->parent = NULL;

        t1->balance = avl_calc_balance(t1);
        t2->balance = avl_calc_balance(t2);
        t1->height = avl_height(t1);
        t2->height = avl_height(t2);
        if(t2->l != NULL) t2->l->height = avl_height(t2->l);
    }
    else{
        avl_node_t *t1 = n, *t2 = n->l;
        avl_node_t *p = t1->parent;
        p->l = t2;
        t1->l = t2->r;
        t2->r = t1;
        t1->parent = t2;
        t2->parent = p;

        t1->balance = avl_calc_balance(t1);
        t2->balance = avl_calc_balance(t2);
        t1->height = avl_height(t1);
        t2->height = avl_height(t2);
        if(t2->l != NULL) t2->l->height = avl_height(t2->l);
    }
}

void mini_l_rotate(avl_tree_t *t, avl_node_t *node){
    avl_node_t *t1 = node;
    avl_node_t *t2 = node->r;

    t1->parent->l = t2;
    t1->parent = t2;
    t2->l = t1;
    t1->r = NULL;
}
void mini_r_rotate(avl_tree_t *t, avl_node_t *node){
    avl_node_t *t1 = node;
    avl_node_t *t2 = node->l;

    t1->parent->r = t2;
    t2->parent = t1->parent;
    t1->parent = t2;
    t2->r = t1;
    t1->l = NULL;
}
#endif //GRAPHS_AVL_TREE_H