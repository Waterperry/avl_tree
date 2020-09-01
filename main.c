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
    assert(!avl_search(t, NULL));
    assert(avl_search(t, "Foxtrot"));
    assert(avl_search(t, "Golf"));
    assert(avl_search(t, "Echo"));
    assert(!avl_search(t, "Blah"));
    assert(!avl_search(t, ""));
    assert(!avl_search(t, "."));
    assert(!avl_search(t, "asdfa]}{\\§sdfkjaerbflakw-+.;'§ef"));

    printf("Testing delete (no children).\n");
    avl_delete(t, "Golf");
    assert(!avl_search(t, "Golf"));
    assert(t->root->r == NULL);
    assert(avl_search(t, "Foxtrot"));
    assert(avl_search(t, "Echo"));

    printf("Testing delete (1 child).\n");
    avl_delete(t,"Foxtrot");
    assert(!avl_search(t, "Foxtrot"));
    assert(avl_search(t, "Echo"));

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