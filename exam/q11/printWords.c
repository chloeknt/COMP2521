// printWords.c ... implementation of printWords function

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Trie.h"

void printWords(Trie t) {
    // Empty 
    if (t == NULL) {
        return;
    }
    
    if (t->isEndOfWord) {
        printf("\n");
        return;
    }
    
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        if (t->children[i] != NULL) {
            char c = i + 'a';
            printf("%c", c);
            printWords(t->children[i]);
        }
    }

}

