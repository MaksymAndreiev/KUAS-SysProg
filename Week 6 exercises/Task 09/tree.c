#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#ifdef TEST_TREE // defined if we are compiling the unit tests
#define ELEMENT_T int
#endif

#ifndef ELEMENT_T // the client program forgot to say what the element type is
# error "Tree: ELEMENT_T is not defined"
#endif

struct Tree {
    ELEMENT_T    data;   // the element stored in this node
    struct Tree *left;   // pointer to left sub-tree, or 0 if none
    struct Tree *right;  // pointer to right sub-tree, or 0 if none
};

struct Tree *newTree(ELEMENT_T e, struct Tree *left, struct Tree *right)
{
    struct Tree *tree = malloc(sizeof(struct Tree));
    tree->data  = e;
    tree->left  = left;
    tree->right = right;
    return tree;
}

struct Tree *Tree_search(struct Tree *tree, ELEMENT_T target, int (*cmp)(ELEMENT_T a, ELEMENT_T b)){
    if(!tree){
        return 0;
    }
    if(cmp(target, tree->data) < 0){
        return Tree_search(tree->left, target, cmp);
    }
    if(cmp(target, tree->data) > 0){
        return Tree_search(tree->right, target, cmp);
    }
    return tree;
}

struct Tree *Tree_insert(struct Tree **treep, ELEMENT_T e, int (*cmp)(ELEMENT_T a, ELEMENT_T b)){
    struct Tree *tree = *treep;
    if(!tree){
        *treep = newTree(e, 0, 0);
        return *treep;
    }
    if(cmp(e, tree->data) < 0){
        return Tree_insert(&tree->left, e, cmp);
    }
    if(cmp(e, tree->data) > 0){
        return Tree_insert(&tree->right, e, cmp);
    }
    return tree;
}

void Tree_applyPreOrder(struct Tree *tree, void (*fn)(ELEMENT_T e))
{
    if (0 == tree) return;
    fn(tree->data);
    Tree_applyPreOrder(tree->left,  fn);
    Tree_applyPreOrder(tree->right, fn);
}

void Tree_applyPostOrder(struct Tree *tree, void (*fn)(ELEMENT_T e)){
    if (0 == tree) return;
    Tree_applyPostOrder(tree->left,  fn);
    Tree_applyPostOrder(tree->right, fn);
    fn(tree->data);
}

void Tree_applyInOrder(struct Tree *tree, void (*fn)(ELEMENT_T e)){
    if (0 == tree) return;
    Tree_applyInOrder(tree->left,  fn);
    fn(tree->data);
    Tree_applyInOrder(tree->right, fn);
}

int intcmp(int a, int b){
    return a - b;
}

#ifdef TEST_TREE

void printInt(int i)
{
    printf(" %i", i);
}

#endif
