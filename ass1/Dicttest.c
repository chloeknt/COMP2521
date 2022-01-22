// COMP2521 21T2 Assignment 1
// Dict.c ... implementation of the Dictionary ADT

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Dict.h"
#include "WFreq.h"

#define MAXLINE 1000
#define MAXWORD 100

// you may define your own structs here

typedef struct DictRep *DictLink;

typedef struct DictRep {
	int frequency;
	char *word;
	DictLink left;  
	DictLink right;
} DictRep;


// add function prototypes for your helper functions here
static Dict newDictNode(char *word);
static void showDictNode(Dict d); 

// Creates a new Dictionary
Dict DictNew(void) {
	return NULL;
}

// Frees the given Dictionary
void DictFree(Dict d) {
    if (d == NULL) {
		return;
	}
	DictFree(d->left);
	DictFree(d->right);
	free(d);
}

//Creates a new node
DictLink newDictNode(char *word) {
    DictLink n = malloc(sizeof(DictRep));
    n->word = malloc(sizeof(strlen(word)));
	strcpy(n->word, word);
	n->frequency = 1;
	n->right = NULL;
	n->left = NULL;
	return n;
}

// Inserts an occurrence of the given word into the Dictionary 
// in the correct place
void DictInsert(Dict d, char *word) {
    if (d == NULL) {
        d = newDictNode(word);
        printf("%s\n", d->word);
	} else if (strcmp(word, d->word) < 0) {
	    //if (d->left == NULL) {
	    //d->left = newDictNode(word);
	    //} else {
		DictInsert(d->left, word);
		//}
	} else if (strcmp(word, d->word) > 0) {
	//if (d->left == NULL) {
	    //d->left = newDictNode(word);
	    //} else {
		//DictInsert(d->left, word);
		//}
		DictInsert(d->right, word);
	} else { // (word == d->word)
		d->frequency++;
	}
}


// Returns the occurrence count of the given word. Returns 0 if the word
// is not in the Dictionary.
int DictFind(Dict d, char *word) {
    if (d == NULL) {
		return 0;
    }
    if (strcmp(word, d->word) == 0) { 
        return d->frequency;
	} else if (d != NULL && strcmp(word, d->word) < 0) {
		DictFind(d->left, word);
	} else if (d != NULL && strcmp(word, d->word) > 0) {
		DictFind(d->right, word);
	}
	return 0; 
}

// Finds  the top `n` frequently occurring words in the given Dictionary
// and stores them in the given  `wfs`  array  in  decreasing  order  of
// frequency,  and then in increasing lexicographic order for words with
// the same frequency. Returns the number of WFreq's stored in the given
// array (this will be min(`n`, #words in the Dictionary)) in  case  the
// Dictionary  does  not  contain enough words to fill the entire array.
// Assumes that the `wfs` array has size `n`.
int DictFindTopN(Dict d, WFreq *wfs, int n) {
	return 0;
}

// Displays the given Dictionary. This is purely for debugging purposes,
// so  you  may  display the Dictionary in any format you want.  You may
// choose not to implement this.
void DictShow(Dict d) {
    if (d == NULL) {
        return;
    }
	DictShow(d->left);
	showDictNode(d);
	DictShow(d->right);
}

// Prints the value in the given node
static void showDictNode(Dict d) {
	if (d == NULL) {
	    return;
	}
	printf("%d %s\n", d->frequency, d->word);
}


