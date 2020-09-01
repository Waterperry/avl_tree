# avl_tree

## Description
This is the C code for an AVL (self-balancing binary) Tree. The code is split into two header files and a test driver function (main.c).

## Topography

The two header files (avl_tree.h and avl_node.h) contain the code for the AVL Tree.

The avl_node.h header file is all internal code and does not contain any API functions.

The avl_tree.h header file contains some API functions and some internal functions (API functions are clearly
listed at the top).

## Installation

Simply copy the header files into the directory you wish to work in. You can copy the *main.c* file too if you
would like to test the code.
Check that you have the required dependencies.

## Dependencies

You will need the "string_ops.h" file too in a subdirectory called 'tom' unless you wish to implement your own
_append(char*,char)_ function.

## Usage

The code should be used as follows:
1. On create, assign an _avl_tree_t*_ pointer to the return value of make_avl_tree().
2. Use the operations _avl_insert(avl_tree_t*, char*)_, _avl_search(avl_tree_t*, char*)_, and _avl_delete(avl_tree_t*, char*)_.
