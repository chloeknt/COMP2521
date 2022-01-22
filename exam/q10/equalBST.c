// equalBST.c ... implementation of equalBST function

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "BSTree.h"

int equalBST(BSTree t1, BSTree t2) {
    // Check for empty BST
    if (t1 == NULL && t2 == NULL) {
        return 1;
    }
    
    // Both BSTs not empty 
    if (t1 != NULL && t2 != NULL) {
        // Recursively check every node in trees
        return (t1->key == t2->key && equalBST(t1->left, t2->left) && 
        equalBST(t1->right, t2->right));
    }

    return 0;
}

