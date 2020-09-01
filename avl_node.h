#ifndef GRAPHS_AVL_NODE_H
#define GRAPHS_AVL_NODE_H
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <tom/string_ops.h>

//ALL INTERNAL

//typedef struct avl_node_t avl_node_t;
typedef struct avl_node_t {
    char *s;
    struct avl_node_t *l, *r, *parent;
    int balance, height;
} avl_node_t;

avl_node_t *make_avl_node(char*);
void print_avl_node(avl_node_t *node, int indent);
int is_leaf(avl_node_t*);
int is_balanced(avl_node_t*);

avl_node_t *make_avl_node(char *data){
    avl_node_t *node = malloc(sizeof(avl_node_t));
    node->s = malloc(sizeof(char) * (strlen(data) + 1));
    strcpy(node->s, data);
    node->balance = 0;
    node->height = 1;
    node->l = NULL;
    node->r = NULL;
    node->parent = NULL;

    if(node==NULL || node->s == NULL){
        perror("out of memory");
        exit(0);
    }
    return node;
}

void print_avl_node(avl_node_t *node, int indent){
    if(node==NULL){
        return;
    }
    char *str = malloc(sizeof(char));
    str[0] = 0;
    for(int i = 0; i < indent; i++){
        str = append(str, '\t');
    }
    //printf("%s%s - %d/%d (%s,%s,%s)\n",str,node->s,node->balance,node->height,(node->parent==NULL)?"null":node->parent->s,(node->l==NULL)?"null":node->l->s, (node->r==NULL)?"null":node->r->s);
    printf("%s%s\n",str,node->s);


    if(is_leaf(node)){
        return;
    }
    print_avl_node(node->l, indent + 1);
    print_avl_node(node->r, indent + 1);
}

int is_leaf(avl_node_t *node){
    return (node->l == NULL && node->r == NULL);
}

int is_balanced(avl_node_t *node){
    return (node->balance <= 1 && node->balance >= -1);
}

int avl_height(avl_node_t *node) {
    if(node == NULL) return 0;
    if(is_leaf(node)) return 1;

    int l = avl_height(node->l);
    int r = avl_height(node->r);
    return 1 + (l>r?l:r);
}

int avl_calc_balance(avl_node_t *node) {
    int l = avl_height(node->l);
    int r = avl_height(node->r);
    return r-l;
}

#endif //GRAPHS_AVL_NODE_H
