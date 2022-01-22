// nodesNotBalanced.c ... implementation of nodesNotBalanced function

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "BSTree.h"

int max(int a, int b);
void traverse(BSTree t, int *num);
int height(BSTree t);

int nodesNotBalanced(BSTree t) {
    // Empty tree
    if (t == NULL) {
        return 0;
    } 
    
    // Check left
    int leftHeight = height(t->left);
    
    // Check right
    int rightHeight = height(t->right);
    
    int difference = leftHeight - rightHeight;
    
    // Balanced
    if (abs(difference) <= 1 && nodesNotBalanced(t->left) == 0
    && nodesNotBalanced(t->right) == 0) {
        return 0;
    }

    // Not balanced
    int num = 1;
    if (nodesNotBalanced(t->left)) {
        traverse(t->left, &num);
    } else if (nodesNotBalanced(t->right)) {
        traverse(t->right, &num);
    }

    return num;
}

// Return maximum of two integers
int max(int a, int b) {
    if (a > b) {
        return a;
    } else {
        return b;
    } 
}

void traverse(BSTree t, int *num) {
    if (t == NULL) {
        return;
    }
    *num = *num + 1;
    traverse(t->left, num);
    traverse(t->right, num);
}

int height(BSTree t) {
    if (t == NULL) {
        return 0;
    } 
    
    return 1 + max(height(t->left), height(t->right));
}
