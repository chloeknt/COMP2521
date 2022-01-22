// Program to test the Dictionary ADT

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "Dict.h"
#include "WFreq.h"


int main(void) {
	Dict d = DictNew();
	DictInsert(d, "a");
	assert(DictFind(d, "a") == 1);
	DictShow(d);
	DictInsert(d, "i");
	DictInsert(d, "i");
    assert(DictFind(d, "i") == 2);
        DictShow(d);
	DictInsert(d, "h");
    assert(DictFind(d, "h") == 1);
        DictShow(d);
	DictInsert(d, "d");
	DictInsert(d, "d");
	DictInsert(d, "d");
	DictInsert(d, "d");
	DictShow(d);
	DictInsert(d, "e");
	DictShow(d);
	DictInsert(d, "f");
	DictInsert(d, "f");
	DictShow(d);
	DictInsert(d, "g");
	DictShow(d);
	DictInsert(d, "c");
	DictInsert(d, "c");
	DictInsert(d, "c");
	DictShow(d);
	DictInsert(d, "b");
	assert(DictFind(d, "b") == 1);
	DictShow(d);
	// add more tests here
	WFreq *wfs = malloc(20 * sizeof(struct WFreq));
	int i = DictFindTopN(d, wfs, 20);
	printf("%d\n", i);
	DictFree(d);
}

