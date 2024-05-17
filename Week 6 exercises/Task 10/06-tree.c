#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#ifdef TEST_TREE // defined if we are compiling the unit tests
# define ELEMENT_T int
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

void printTree(struct Tree *tree, int ){
    if(!tree){
        return;
    }


#ifdef TEST_TREE

void printInt(int i)
{
    printf(" %i", i);
}

int main(int argc, char **argv){
    struct Tree *t = newTree(4,
			     newTree(2,
                         newTree(1, 0, 0),
                         newTree(3, 0, 0)),
			     newTree(6,
                         newTree(5, 0, 0),
                         newTree(7, 0, 0))
                         );

    Tree_applyPreOrder(t, printInt);
    putchar('\n');

    assert(t != 0);
    assert(t->data == 4);
    assert(t->left != 0);
    assert(t->left->data == 2);
    assert(t->right != 0);
    assert(t->right->data == 6);
    assert(t->left->left->data == 1);
    assert(t->left->right->data == 3);

    Tree_applyPostOrder(t, printInt);
    putchar('\n');

    Tree_applyInOrder(t, printInt);
    putchar('\n');

    assert(Tree_search(t, 4, intcmp) == t);
    assert(Tree_search(t, 6, intcmp) == t->right);
    assert(Tree_search(t, 0, intcmp) == 0);
    assert(Tree_search(t, 10, intcmp) == 0);

    assert(Tree_insert(&t, 4, intcmp) == t);
    assert(Tree_insert(&t, 6, intcmp) == t->right);
    struct Tree *ta = Tree_insert(&t, 0, intcmp);
    assert(ta != 0);
    struct Tree *tb = Tree_insert(&t, 10, intcmp);
    assert(tb != 0);
    assert(Tree_insert(&t, 0, intcmp) == ta);
    assert(Tree_insert(&t, 10, intcmp) == tb);
    printf("All tests passed\n");

    struct Tree *t2 = 0;
    Tree_insert(&t2, 9, intcmp);
    Tree_insert(&t2, 33, intcmp);
    Tree_insert(&t2, 14, intcmp);
    Tree_insert(&t2, 82, intcmp);
    Tree_insert(&t2, 33, intcmp);
    Tree_insert(&t2, 12, intcmp);
    Tree_insert(&t2, 33, intcmp);
    Tree_insert(&t2, 40, intcmp);
    Tree_insert(&t2, 97, intcmp);
    Tree_insert(&t2, 40, intcmp);
    Tree_applyInOrder(t2, printInt);
    return 0;
}

#endif
