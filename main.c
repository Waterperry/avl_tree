#include "avl_tree.h"
#include <assert.h>

int main(void){
    printf("Testing creation.\n");
    avl_tree_t *t = make_avl_tree();
    assert(t->root == NULL);
    assert(t!=NULL);

    printf("Testing insertion.\n");
    avl_insert(t,"Foxtrot");
    assert(!strcmp(t->root->s, "Foxtrot"));
    avl_insert(t, "Golf");
    assert(!strcmp(t->root->r->s, "Golf"));
    avl_insert(t,"Echo");
    assert(!strcmp(t->root->l->s, "Echo"));

    printf("Testing search.\n");
    assert(!in_avl_tree(t, NULL));
    assert(in_avl_tree(t,"Foxtrot"));
    assert(in_avl_tree(t,"Golf"));
    assert(in_avl_tree(t, "Echo"));
    assert(!in_avl_tree(t, "Blah"));
    assert(!in_avl_tree(t, ""));
    assert(!in_avl_tree(t, "."));
    assert(!in_avl_tree(t, "asdfa]}{\\§sdfkjaerbflakw-+.;'§ef"));

    printf("Testing delete (no children).\n");
    avl_delete(t, "Golf");
    assert(!in_avl_tree(t,"Golf"));
    assert(t->root->r == NULL);
    assert(in_avl_tree(t,"Foxtrot"));
    assert(in_avl_tree(t,"Echo"));

    printf("Testing delete (1 child).\n");
    avl_delete(t,"Foxtrot");
    assert(!in_avl_tree(t,"Foxtrot"));
    assert(in_avl_tree(t, "Echo"));

    printf("Testing rotation (RL - RR).\n");
    avl_insert(t, "Golf");
    assert(!strcmp(t->root->r->s, "Golf"));
    avl_insert(t, "Foxtrot");
    assert(!strcmp(t->root->s, "Foxtrot"));

    printf("Testing delete (two children).\n");

    avl_delete(t, "Foxtrot");
    assert(!strcmp(t->root->s, "Echo"));
    avl_delete(t, "Echo");
    assert(!strcmp(t->root->s, "Golf"));
    avl_delete(t, "Golf");
    assert(t->root == NULL);

    printf("Testing rotation (LR - LL)\n");
    avl_insert(t, "Golf");
    assert(!strcmp(t->root->s, "Golf"));
    avl_insert(t, "Echo");
    assert(!strcmp(t->root->l->s, "Echo"));
    avl_insert(t, "Foxtrot");
    assert(!strcmp(t->root->s, "Foxtrot"));

}