#include <stdio.h>
#include <stdlib.h>

#define MAX 100

struct TreeNode {
    int value;
    struct TreeNode *left;
    struct TreeNode *right;
};

struct TreeNode *newTreeNode(int value) {
    struct TreeNode *node = malloc(sizeof(struct TreeNode));
    node->value = value;
    node->left = 0;
    node->right = 0;
    return node;
}

struct TreeNode** createQueue(int *front, int *rear) {
    struct TreeNode **queue = malloc(sizeof(struct TreeNode *)*MAX);
    *front = *rear = 0;
    return queue;
}

void enQueue(struct TreeNode **queue, int *rear, struct TreeNode *new_node) {
    queue[*rear] = new_node;
    (*rear)++;
}

struct TreeNode *deQueue(struct TreeNode **queue, int *front) {
    (*front)++;
    return queue[*front - 1];
}

void BFSearch(struct TreeNode *node) {
    int front, rear;
    struct TreeNode **queue = createQueue(&front, &rear);
    struct TreeNode *temp_node = node;

    while (temp_node) {
        printf("%d ", temp_node->value);

        if (temp_node->left) {
            enQueue(queue, &rear, temp_node->left);
        }
        if (temp_node->right) {
            enQueue(queue, &rear, temp_node->right);
        }

        temp_node = deQueue(queue, &front);
    }
    free(queue);
}

void freeTree(struct TreeNode *node) {
    if (node) {
        freeTree(node->left);
        freeTree(node->right);
        free(node);
    }
}

//int BFSearch(struct TreeNode *root, int value) {
//    int queue[MAX];
//    int visited[MAX];
//    int front = 0;
//    int rear = 0;
//
//    for (int i = 0; i < root->value; i++) {
//        visited[i] = 0;
//    }
//
//    visited[root->value] = 1;
//    queue[rear++] = root->value;
//
//    while (front != rear) {
//        int current = queue[front++];
//        if (current == value) {
//            return 1;
//        }
//
//        struct TreeNode *node = root;
//        while (node) {
//            if (node->value == current) {
//                if (node->left && !visited[node->left->value]) {
//                    visited[node->left->value] = 1;
//                    queue[rear++] = node->left->value;
//                }
//                if (node->right && !visited[node->right->value]) {
//                    visited[node->right->value] = 1;
//                    queue[rear++] = node->right->value;
//                }
//            }
//            node = node->right;
//        }
//    }
//    return 0;
//
//}

int main(int argc, char **argv) {
    struct TreeNode *root = newTreeNode(1);
    root->left = newTreeNode(2);
    root->right = newTreeNode(3);
    root->left->left = newTreeNode(4);
    root->left->right = newTreeNode(5);
    BFSearch(root);
    freeTree(root);

    return 0;
}
